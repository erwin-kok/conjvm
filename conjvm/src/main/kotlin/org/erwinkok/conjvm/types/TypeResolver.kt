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

    // ========================================================================
    // PUBLIC API - Resolve entities and populate their type fields
    // ========================================================================

    fun resolveTypedef(entity: Entity.Typedef) {
        // Check if already resolved
        if (entity.type != null) {
            return
        }
        val declaration = entity.declarations.first()
        val baseType = buildTypeFromDeclaration(declaration.declarationSpecifier, entity.scope)
        val qualType = applyDeclarator(baseType, declaration.declarator, entity.scope)

        // Store resolved type in entity
        entity.type = qualType
    }

    fun resolveVariable(entity: Entity.Variable) {
        if (entity.type != null) {
            return
        }
        val declaration = entity.definition ?: entity.declarations.first()
        val baseType = buildTypeFromDeclaration(declaration.declarationSpecifier, entity.scope)
        val qualType = applyDeclarator(baseType, declaration.declarator, entity.scope)

        // Store resolved type in entity
        entity.type = qualType
    }

    fun resolveFunction(entity: Entity.Function) {
        if (entity.returnType != null) {
            return
        }
        val declaration = entity.definition ?: entity.declarations.first()
        val baseType = buildTypeFromDeclaration(declaration.declarationSpecifier, entity.scope)
        val declarator = declaration.declarator as? Declarator.FunctionDeclarator
            ?: error("Function must have function declarator")

        val returnType = applyDeclarator(baseType, declarator.declarator, entity.scope)

        // Build parameter types
        val parameterTypes = declaration.parameters.map { param ->
            val paramBaseType = buildTypeFromDeclaration(param.declarationSpecifier, entity.scope)
            applyDeclarator(paramBaseType, param.declarator, entity.scope)
        }

        // Store resolved types in entity
        entity.returnType = returnType
        entity.parameterTypes = parameterTypes
    }

    fun resolveStruct(entity: Entity.Struct) {
        if (entity.members != null) {
            return
        }
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
            // Build member type from declaration
            val baseType = buildTypeFromDeclaration(
                structDecl.declarationSpecifier,
                entity.scope,
            )

            structDecl.declarators?.forEach { structDeclarator ->
                val memberType = structDeclarator.declarator?.let {
                    applyDeclarator(baseType, it, entity.scope)
                } ?: baseType

                val bitFieldWidth = structDeclarator.bitWidthCtx?.let { ctx ->
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

        // Store resolved information in entity
        entity.members = members
        entity.size = totalSize
        entity.alignment = maxAlignment
    }

    fun resolveEnum(entity: Entity.Enum) {
        if (entity.constants != null) {
            return
        }

        val definition = entity.definition ?: entity.declarations.first()

        if (!definition.isDefinition) {
            return
        }

        val constants = mutableMapOf<String, Long>()
        var currentValue = 0L

        definition.enumerators.forEach { enumerator ->
            val value = if (enumerator.valueCtx != null) {
                constantEvaluator.visit(enumerator.valueCtx) ?: currentValue
            } else {
                currentValue
            }

            constants[enumerator.text] = value
            currentValue = value + 1
        }

        // Store resolved information in entity
        entity.constants = constants
        entity.underlyingType = QualType(Type.Int(signed = true))
    }

    fun buildType(declarationSpecifier: DeclarationSpecifier, declarator: Declarator, scope: Scope): QualType {
        val paramBaseType = buildTypeFromDeclaration(declarationSpecifier, scope)
        return applyDeclarator(paramBaseType, declarator, scope)
    }

    // ========================================================================
    // BUILD TYPE FROM DECLARATION (used during type resolution)
    // ========================================================================

    /**
     * Build a type from a declaration specifier.
     * This is used DURING type resolution, so it doesn't look up typedef types
     * (they might not be resolved yet).
     *
     * For typedefs: looks up the typedef entity and recursively builds its type.
     * For structs/enums: looks up the entity and uses its resolved type info.
     */
    private fun buildTypeFromDeclaration(declSpec: DeclarationSpecifier, scope: Scope): QualType {
        val typeSpecs = declSpec.typeSpecs
        val typedefSpec = typeSpecs.filterIsInstance<TypeSpec.TypedefName>().singleOrNull()
        val structSpec = typeSpecs.filterIsInstance<TypeSpec.Struct>().singleOrNull()
        val enumSpec = typeSpecs.filterIsInstance<TypeSpec.Enum>().singleOrNull()
        val namedTypes = listOfNotNull(typedefSpec, structSpec, enumSpec)
        if (namedTypes.size > 1) {
            reporter.reportError(UnknownLocation, "conflicting type specifiers")
            return QualType(Type.Error)
        }
        return when {
            typedefSpec != null -> {
                val typedefEntity = scope.lookupTypedefEntity(typedefSpec.name)
                if (typedefEntity == null) {
                    reporter.reportError(UnknownLocation, "undefined type '${typedefSpec.name}'")
                    return QualType(Type.Error)
                }

                // Check if already resolved
                val resolvedType = typedefEntity.type
                if (resolvedType != null) {
                    // Already resolved - use it
                    return resolvedType.withQualifiers(declSpec.qualifiers)
                }

                // Not yet resolved - resolve it now
                resolveTypedef(typedefEntity)

                // Get the resolved type (should be set now, or Error if circular)
                val finalType = typedefEntity.type ?: QualType(Type.Error) // Shouldn't happen, but safety

                // Return with additional qualifiers
                finalType.withQualifiers(declSpec.qualifiers)
            }

            structSpec != null -> {
                val structTag = structSpec.name
                if (structTag == null) {
                    reporter.reportError(UnknownLocation, "anonymous struct in type specifier")
                    return QualType(Type.Error)
                }

                val structEntity = scope.lookupStructTag(structTag)
                if (structEntity == null) {
                    reporter.reportError(UnknownLocation, "undefined struct '$structTag'")
                    return QualType(Type.Error)
                }

                // Build struct type
                // Members might be null if incomplete or not yet resolved
                val structType = Type.Struct(
                    id = structEntity.id,
                    tag = structEntity.name,
                    members = structEntity.members, // Might be null
                )

                QualType(structType, declSpec.qualifiers)
            }

            enumSpec != null -> {
                val tag = enumSpec.name
                    ?: run {
                        reporter.reportError(UnknownLocation, "anonymous enum in type specifier")
                        return QualType(Type.Error)
                    }

                val entity = scope.lookupEnumTag(tag)
                    ?: run {
                        reporter.reportError(
                            UnknownLocation,
                            "undefined enum '$tag'",
                        )
                        return QualType(Type.Error)
                    }

                QualType(
                    Type.Enum(
                        id = entity.id,
                        tag = entity.name,
                        constants = entity.constants,
                    ),
                    declSpec.qualifiers,
                )
            }

            else -> {
                // Build primitive type
                val primitiveType = buildPrimitiveType(typeSpecs)
                QualType(primitiveType, declSpec.qualifiers)
            }
        }
    }

    /**
     * Build a primitive type from type specifiers.
     */
    private fun buildPrimitiveType(typeSpecs: List<TypeSpec>): Type {
        // Determine signed/unsigned
        val hasUnsigned = typeSpecs.contains(TypeSpec.UNSIGNED)
        val hasSigned = typeSpecs.contains(TypeSpec.SIGNED)
        val signed = hasSigned || !hasUnsigned

        // Count integer modifiers
        val longCount = typeSpecs.count { it == TypeSpec.LONG }
        val shortCount = typeSpecs.count { it == TypeSpec.SHORT }

        return when {
            typeSpecs.contains(TypeSpec.VOID) -> {
                if (typeSpecs.size > 1) {
                    reporter.reportError(
                        UnknownLocation,
                        "void cannot be combined with other type specifiers",
                    )
                }
                Type.Void
            }

            typeSpecs.contains(TypeSpec.BOOL) -> {
                if (hasUnsigned || hasSigned) {
                    reporter.reportError(
                        UnknownLocation,
                        "_Bool cannot be signed or unsigned",
                    )
                }
                Type.Bool
            }

            typeSpecs.contains(TypeSpec.FLOAT) -> {
                if (hasUnsigned || hasSigned) {
                    reporter.reportError(
                        UnknownLocation,
                        "float cannot be signed or unsigned",
                    )
                }
                Type.Float
            }

            typeSpecs.contains(TypeSpec.DOUBLE) -> {
                if (hasUnsigned || hasSigned) {
                    reporter.reportError(
                        UnknownLocation,
                        "double cannot be signed or unsigned",
                    )
                }
                when (longCount) {
                    0 -> Type.Double
                    1 -> Type.LongDouble
                    else -> {
                        reporter.reportError(
                            UnknownLocation,
                            "too many 'long' specifiers",
                        )
                        Type.Double
                    }
                }
            }

            typeSpecs.contains(TypeSpec.CHAR) -> {
                if (longCount > 0 || shortCount > 0) {
                    reporter.reportError(
                        UnknownLocation,
                        "char cannot be long or short",
                    )
                }
                Type.Char(signed)
            }

            shortCount > 0 -> {
                if (longCount > 0) {
                    reporter.reportError(
                        UnknownLocation,
                        "cannot combine short and long",
                    )
                }
                if (shortCount > 1) {
                    reporter.reportError(
                        UnknownLocation,
                        "duplicate 'short'",
                    )
                }
                Type.Short(signed)
            }

            longCount == 1 -> Type.Long(signed)
            longCount == 2 -> Type.LongLong(signed)
            longCount > 2 -> {
                reporter.reportError(
                    UnknownLocation,
                    "too many 'long' specifiers",
                )
                Type.LongLong(signed)
            }

            typeSpecs.isEmpty() -> {
                // Implicit int (deprecated in C99)
                reporter.reportWarning(
                    UnknownLocation,
                    "type specifier missing, defaults to 'int'",
                )
                Type.Int(signed)
            }

            else -> Type.Int(signed)
        }
    }

    /**
     * Apply a declarator to a base type.
     */
    private fun applyDeclarator(baseType: QualType, declarator: Declarator, scope: Scope): QualType {
        return when (declarator) {
            is Declarator.IdentifierDeclarator -> baseType
            is Declarator.AnonymousDeclarator -> baseType

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

                // Apply parameter type adjustments (array/function decay)
                val params = declarator.parameters.map { p ->
                    val paramBaseType = buildTypeFromDeclaration(
                        p.declarationSpecifier,
                        scope,
                    )
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
                // Validate bit-field type
                val canonicalType = baseType.canonical.type
                if (canonicalType !is Type.Int &&
                    canonicalType !is Type.Char &&
                    canonicalType !is Type.Short &&
                    canonicalType !is Type.Long &&
                    canonicalType !is Type.LongLong &&
                    canonicalType !is Type.Bool
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

    // ========================================================================
    // SIZE AND ALIGNMENT COMPUTATION
    // ========================================================================

    private fun computeTypeSize(type: QualType): Long {
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

            is Type.Array -> {
                if (canonical.size == null) {
                    reporter.reportError(
                        UnknownLocation,
                        "cannot compute size of incomplete array type",
                    )
                    return 0
                }
                val elementSize = computeTypeSize(canonical.elementType)
                canonical.size * elementSize
            }

            is Type.BitField -> {
                // Bit-fields are part of structs, use underlying type size
                computeTypeSize(canonical.base)
            }

            is Type.Enum -> 4 // sizeof(int)

            is Type.Struct -> {
                if (canonical.members == null) {
                    reporter.reportError(
                        UnknownLocation,
                        "cannot compute size of incomplete struct '${canonical.tag ?: "<anonymous>"}'",
                    )
                    return 0
                }

                // Use pre-computed size from struct entity
                val structEntity = canonical.tag?.let { rootScope.lookupStructTag(it) }
                structEntity?.size ?: computeStructSize(canonical)
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
            val memberAlignment = computeTypeAlignment(member.type)
            maxAlignment = maxOf(maxAlignment, memberAlignment)

            currentOffset = alignTo(currentOffset, memberAlignment)

            if (member.bitFieldWidth != null) {
                val bitFieldBytes = (member.bitFieldWidth + 7) / 8
                currentOffset += bitFieldBytes
            } else {
                currentOffset += computeTypeSize(member.type)
            }
        }

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
            is Type.Enum -> 4

            is Type.Struct -> {
                if (canonical.members == null) return 1
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
