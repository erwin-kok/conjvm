package org.erwinkok.conjvm.types

import org.erwinkok.conjvm.declarations.DeclarationSpecifier
import org.erwinkok.conjvm.declarations.Declarator
import org.erwinkok.conjvm.declarations.Entity
import org.erwinkok.conjvm.declarations.EntityTable
import org.erwinkok.conjvm.declarations.Scope
import org.erwinkok.conjvm.declarations.TypeSpec
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.SourceFile
import org.erwinkok.conjvm.parser.UnknownLocation
import org.erwinkok.conjvm.utils.ParserReporting
import java.util.UUID

class TypeResolver(
    override val reporter: ErrorReporter,
    override val source: SourceFile,
    private val entityTable: EntityTable,
    private val rootScope: Scope,
) : ParserReporting {
    // Cache for recursive struct types
    private val structCache = mutableMapOf<UUID, Entity.Struct>()
    private val constantEvaluator = ConstantExpressionEvaluator(
        reporter = reporter,
        source = source,
        scope = rootScope,
    )

    fun resolveTypedef(entity: Entity.Typedef) {
        val declaration = entity.declarations.first()
        val baseType = buildBaseType(declaration.declarationSpecifier, entity.scope)
        val qualType = applyDeclarator(baseType, declaration.declarator, entity.scope)
        entity.type = qualType
    }

    fun resolveVariable(entity: Entity.Variable) {
        val declaration = entity.definition ?: entity.declarations.first()
        val baseType = buildBaseType(declaration.declarationSpecifier, entity.scope)
        val qualType = applyDeclarator(baseType, declaration.declarator, entity.scope)
        entity.type = qualType
    }

    fun resolveFunction(entity: Entity.Function) {
        val declaration = entity.definition ?: entity.declarations.first()
        val baseType = buildBaseType(declaration.declarationSpecifier, entity.scope)
        val declarator = declaration.declarator as? Declarator.FunctionDeclarator
            ?: error("Function must have function declarator")
        val returnType = applyDeclarator(baseType, declarator.declarator, entity.scope)
        val parameterTypes = declaration.parameters.map { param ->
            val paramBaseType = buildBaseType(param.declarationSpecifier, entity.scope)
            applyDeclarator(paramBaseType, param.declarator, entity.scope)
        }
        entity.returnType = returnType
        entity.parameterTypes = parameterTypes
    }

    fun resolveStruct(entity: Entity.Struct) {
        // Check cache for recursive types
        if (entity.id in structCache) {
            return
        }

        structCache[entity.id] = entity

        val definition = entity.definition ?: entity.declarations.first()

        if (!definition.isDefinition) {
            // Incomplete type - leave members as null
            return
        }

        // Resolve members
        val members = mutableListOf<StructMember>()
        var currentOffset = 0L
        var maxAlignment = 1L

        definition.structDeclarations.forEach { structDecl ->
            val baseType = buildBaseType(structDecl.declarationSpecifier, entity.scope)
            structDecl.declarators?.forEach { structDeclarator ->
                val memberType = structDeclarator.declarator?.let {
                    applyDeclarator(baseType, it, entity.scope)
                } ?: baseType
                val bitFieldWidth = structDeclarator.bitWidth?.let { ctx ->
                    constantEvaluator.visit(ctx)?.toInt()
                }
                val memberAlignment = computeTypeAlignment(memberType)
                maxAlignment = maxOf(maxAlignment, memberAlignment)
                val alignedOffset = alignTo(currentOffset, memberAlignment)
                val member = StructMember(
                    name = structDeclarator.declarator?.name(),
                    type = memberType,
                    offset = alignedOffset,
                    bitFieldWidth = bitFieldWidth,
                )
                members.add(member)
                if (bitFieldWidth != null) {
                    currentOffset = alignedOffset + ((bitFieldWidth + 7) / 8)
                } else {
                    currentOffset = alignedOffset + computeTypeSize(memberType)
                }
            }
        }

        val totalSize = alignTo(currentOffset, maxAlignment)
        entity.members = members
        entity.size = totalSize
        entity.alignment = maxAlignment
    }

    fun resolveEnum(entity: Entity.Enum) {
        val definition = entity.definition ?: entity.declarations.first()
        if (!definition.isDefinition) {
            return
        }
        val constants = mutableMapOf<String, Long>()
        var currentValue = 0L
        definition.enumerators.forEach { enumerator ->
            val value = if (enumerator.value != null) {
                constantEvaluator.visit(enumerator.value) ?: currentValue
            } else {
                currentValue
            }
            constants[enumerator.text] = value
            currentValue = value + 1
        }
        entity.constants = constants
        entity.underlyingType = QualType(Type.Int(signed = true))
    }

    fun buildType(declarationSpecifier: DeclarationSpecifier, declarator: Declarator, scope: Scope): QualType {
        val paramBaseType = buildBaseType(declarationSpecifier, scope)
        return applyDeclarator(paramBaseType, declarator, scope)
    }

    private fun buildBaseType(declSpec: DeclarationSpecifier, scope: Scope): QualType {
        val typeSpecs = declSpec.typeSpecs

        // Check for struct/enum/typedef
        typeSpecs.forEach { typeSpec ->
            when (typeSpec) {
                is TypeSpec.TypedefName -> {
                    // Look up typedef
                    val typedef = scope.lookupTypedefEntity(typeSpec.name)
                    if (typedef == null) {
                        reporter.reportError(
                            UnknownLocation,
                            "undefined type '${typeSpec.name}'",
                        )
                        return QualType(Type.Error)
                    }
                    val type = typedef.type
                    if (type == null) {
                        reporter.reportError(
                            UnknownLocation,
                            "typedef '${typedef.name}' should have a type",
                        )
                        return QualType(Type.Error)
                    }
                    // Return typedef's type with additional qualifiers
                    return type.withQualifiers(declSpec.qualifiers)
                }

                is TypeSpec.Struct -> {
                    // Look up struct
                    val structTag = typeSpec.name
                    if (structTag == null) {
                        reporter.reportError(UnknownLocation, "anonymous struct in type name")
                        return QualType(Type.Error)
                    }
                    val structEntity = scope.lookupStructTag(structTag)
                    if (structEntity == null) {
                        reporter.reportError(UnknownLocation, "undefined struct '$structTag'")
                        return QualType(Type.Error)
                    }
                    val structType = Type.Struct(
                        id = structEntity.id,
                        tag = structEntity.name,
                        members = structEntity.members,
                    )
                    return QualType(structType, declSpec.qualifiers)
                }

                is TypeSpec.Enum -> {
                    // Look up enum
                    val enumTag = typeSpec.name
                    if (enumTag == null) {
                        reporter.reportError(UnknownLocation, "anonymous enum in type name")
                        return QualType(Type.Error)
                    }
                    val enumEntity = scope.lookupEnumTag(enumTag)
                    if (enumEntity == null) {
                        reporter.reportError(UnknownLocation, "undefined enum '$enumTag'")
                        return QualType(Type.Error)
                    }
                    val structType = Type.Enum(
                        id = enumEntity.id,
                        tag = enumEntity.name,
                        constants = enumEntity.constants,
                    )
                    return QualType(structType, declSpec.qualifiers)
                }

                else -> Unit // Handled below
            }
        }
        val primitiveType = buildPrimitiveType(typeSpecs)
        return QualType(primitiveType, declSpec.qualifiers)
    }

    private fun buildPrimitiveType(typeSpecs: List<TypeSpec>): Type {
        // Determine signed/unsigned
        val hasUnsigned = typeSpecs.contains(TypeSpec.UNSIGNED)
        val hasSigned = typeSpecs.contains(TypeSpec.SIGNED)
        val signed = hasSigned || !hasUnsigned

        // Count integer modifiers
        val longCount = typeSpecs.count { it == TypeSpec.LONG }
        val shortCount = typeSpecs.count { it == TypeSpec.SHORT }

        val baseType = when {
            typeSpecs.contains(TypeSpec.VOID) -> {
                if (typeSpecs.size > 1) {
                    throw TypeException("invalid type specifier: void cannot be combined")
                }
                Type.Void
            }

            typeSpecs.contains(TypeSpec.BOOL) -> {
                if (typeSpecs.any { it == TypeSpec.SIGNED || it == TypeSpec.UNSIGNED }) {
                    throw TypeException("invalid type specifier: _Bool cannot be signed/unsigned")
                }
                Type.Bool
            }

            typeSpecs.contains(TypeSpec.FLOAT) -> {
                if (typeSpecs.any { it == TypeSpec.SIGNED || it == TypeSpec.UNSIGNED }) {
                    throw TypeException("invalid type specifier: float cannot be signed/unsigned")
                }
                Type.Float
            }

            typeSpecs.contains(TypeSpec.DOUBLE) -> {
                if (typeSpecs.any { it == TypeSpec.SIGNED || it == TypeSpec.UNSIGNED }) {
                    throw TypeException("invalid type specifier: double cannot be signed/unsigned")
                }
                when (longCount) {
                    0 -> Type.Double
                    1 -> Type.LongDouble
                    else -> throw TypeException("invalid type specifier: too many long specifiers")
                }
            }

            typeSpecs.contains(TypeSpec.CHAR) -> {
                if (longCount > 0 || shortCount > 0) {
                    throw TypeException("invalid type specifier: char cannot be long/short")
                }
                Type.Char(signed)
            }

            shortCount > 0 -> {
                if (longCount > 0) {
                    throw TypeException("invalid type specifier: short and long together")
                }
                if (shortCount > 1) {
                    throw TypeException("invalid type specifier: duplicate short")
                }
                Type.Short(signed)
            }

            longCount == 1 -> Type.Long(signed)
            longCount == 2 -> Type.LongLong(signed)
            longCount > 2 -> throw TypeException("invalid type specifier: too many long specifiers")

            typeSpecs.isEmpty() -> {
                Type.Int(signed)
            }

            else -> Type.Int(signed)
        }
        return baseType
    }

    private fun applyDeclarator(baseType: QualType, declarator: Declarator, scope: Scope): QualType {
        return when (declarator) {
            is Declarator.IdentifierDeclarator -> {
                baseType
            }

            is Declarator.AnonymousDeclarator -> {
                baseType
            }

            is Declarator.PointerDeclarator -> {
                val pointeeType = applyDeclarator(baseType, declarator.pointee, scope)
                QualType(Type.Pointer(pointeeType), declarator.qualifiers)
            }

            is Declarator.ArrayDeclarator -> {
                val elementType = applyDeclarator(baseType, declarator.elementType, scope)
                val size = declarator.sizeCtx?.let {
                    constantEvaluator.visit(it)
                }

                if (size != null && size <= 0) {
                    reporter.reportError(
                        declarator.location,
                        "array size must be positive, got $size",
                    )
                }

                QualType(Type.Array(elementType, size))
            }

            is Declarator.FunctionDeclarator -> {
                val returnType = applyDeclarator(baseType, declarator.declarator, scope)

                // Apply array-to-pointer and function-to-pointer decay for parameters
                val params = declarator.parameters.map { p ->
                    val paramBaseType = buildBaseType(p.declarationSpecifier, scope)
                    val paramType = applyDeclarator(paramBaseType, p.declarator, scope)

                    // Parameter type adjustments per C standard
                    when (val type = paramType.type) {
                        is Type.Array -> {
                            // Array parameters decay to pointers
                            QualType(Type.Pointer(type.elementType), paramType.qualifiers)
                        }

                        is Type.Function -> {
                            // Function parameters become function pointers
                            QualType(Type.Pointer(paramType), emptySet())
                        }

                        else -> paramType
                    }
                }

                QualType(Type.Function(returnType, params))
            }

            is Declarator.BitFieldDeclarator -> {
                // Bit-fields must be integral types
                if (baseType.type !is Type.Int &&
                    baseType.type !is Type.Char &&
                    baseType.type !is Type.Short &&
                    baseType.type !is Type.Long &&
                    baseType.type !is Type.LongLong &&
                    baseType.type !is Type.Bool
                ) {
                    reporter.reportError(
                        declarator.location,
                        "bit-field must have integral type",
                    )
                }

                QualType(Type.BitField(baseType, declarator.width))
            }
        }
    }

    private fun computeTypeSize(type: QualType): Long {
        return when (val canonical = type.canonical.type) {
            // Primitive types
            is Type.Void -> 1
            is Type.Bool -> 1
            is Type.Char -> 1
            is Type.Short -> 2
            is Type.Int -> 4
            is Type.Long -> 8
            is Type.LongLong -> 8
            is Type.Float -> 4
            is Type.Double -> 8
            is Type.LongDouble -> 16
            is Type.Pointer -> 8

            // Composite types
            is Type.Array -> {
                if (canonical.size == null) {
                    reporter.reportError(UnknownLocation, "cannot compute size of incomplete array type")
                    return 0
                }
                val elementSize = computeTypeSize(canonical.elementType)
                canonical.size * elementSize
            }

            is Type.BitField -> {
                // Bit-fields don't have a size on their own - they're part of structs
                // But if we need to compute it, use the size of the underlying type
                computeTypeSize(canonical.base)
            }

            is Type.Enum -> {
                // Enums have the same size as int in C
                4 // sizeof(int)
            }

            is Type.Struct -> {
                if (canonical.members == null) {
                    reporter.reportError(UnknownLocation, "cannot compute size of incomplete struct type '${canonical.tag ?: "<anonymous>"}'")
                    return 0
                }
                // The size should have been computed during struct resolution
                // Find the struct symbol to get its computed size
                val structEntity = canonical.tag?.let { rootScope.lookupStructTag(it) }
                structEntity?.size ?: run {
                    // Fallback: compute it manually
                    computeStructSize(canonical)
                }
            }

            is Type.Typedef -> {
                error("Typedef should not appear in canonical type")
            }

            is Type.Function -> {
                reporter.reportError(UnknownLocation, "cannot compute size of function type")
                0
            }

            is Type.Error -> 0
        }
    }

    private fun computeStructSize(struct: Type.Struct): Long {
        val members = struct.members ?: return 0

        var currentOffset = 0L
        var maxAlignment = 1L

        members.forEach { member ->
            val memberType = member.type
            val memberSize = computeTypeSize(memberType)
            val memberAlignment = computeTypeAlignment(memberType)

            maxAlignment = maxOf(maxAlignment, memberAlignment)

            // Align current offset to member's alignment
            currentOffset = alignTo(currentOffset, memberAlignment)

            // Add member's size
            val bitFieldWidth = member.bitFieldWidth
            if (bitFieldWidth != null) {
                // Bit-field handling (simplified)
                val bitFieldBytes = (bitFieldWidth + 7) / 8
                currentOffset += bitFieldBytes
            } else {
                currentOffset += memberSize
            }
        }

        // Final struct size must be aligned to its own alignment
        return alignTo(currentOffset, maxAlignment)
    }

    private fun computeTypeAlignment(type: QualType): Long {
        return when (val canonical = type.canonical.type) {
            is Type.Void -> 1
            is Type.Bool -> 1
            is Type.Char -> 1
            is Type.Short -> 2
            is Type.Int -> 4
            is Type.Long -> 8
            is Type.LongLong -> 8
            is Type.Float -> 4
            is Type.Double -> 8
            is Type.LongDouble -> 16
            is Type.Pointer -> 8

            is Type.Array -> computeTypeAlignment(canonical.elementType)

            is Type.BitField -> computeTypeAlignment(canonical.base)

            is Type.Enum -> 4 // Same as int

            is Type.Struct -> {
                if (canonical.members == null) return 1

                // Struct alignment is the maximum of all member alignments
                canonical.members.maxOfOrNull { member ->
                    computeTypeAlignment(member.type)
                } ?: 1
            }

            is Type.Typedef -> error("Typedef in canonical type")
            is Type.Function -> 1
            is Type.Error -> 1
        }
    }

    private fun alignTo(offset: Long, alignment: Long): Long {
        return ((offset + alignment - 1) / alignment) * alignment
    }
}
