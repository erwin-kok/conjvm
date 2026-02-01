Here's a comprehensive and precise review with extensions:

## Symbol Definitions

```kotlin
/**
 * Symbol for a typedef declaration.
 * Represents a type alias that can be used in place of the underlying type.
 */
data class TypedefSymbol(
    val name: String,
    val type: QualType,  // ADD: The underlying type this typedef refers to
    val scope: Scope,    // ADD: Scope where typedef is defined
    val entity: Entity.Typedef,  // ADD: Back-reference to entity
)

/**
 * Symbol for a variable declaration.
 * Represents a variable with storage class and linkage.
 */
data class VariableSymbol(
    val name: String,
    val type: QualType,
    val storage: Set<StorageClass>,
    val linkage: Linkage,  // ADD: External, internal, or none
    val scope: Scope,      // ADD: Scope where variable is defined
    val entity: Entity.Variable,
) {
    val isDefinition: Boolean
        get() = entity.definition != null
    
    val isExtern: Boolean
        get() = storage.contains(StorageClass.EXTERN)
    
    val isStatic: Boolean
        get() = storage.contains(StorageClass.STATIC)
}

/**
 * Symbol for a function declaration.
 * Represents a function with return type and parameter types.
 */
data class FunctionSymbol(
    val name: String,
    val returnType: QualType,
    val parameterTypes: List<QualType>,
    val storage: Set<StorageClass>,
    val linkage: Linkage,  // ADD: External or internal
    val scope: Scope,      // ADD: Scope where function is defined
    val entity: Entity.Function,
    val isVariadic: Boolean = false,  // ADD: For functions like printf(const char*, ...)
) {
    val isDefinition: Boolean
        get() = entity.definition != null
    
    val isInline: Boolean
        get() = entity.declarations.any { 
            it.declarationSpecifier.functionSpecs.contains(FunctionSpec.INLINE) 
        }
}

/**
 * Symbol for a struct type.
 * Represents a structure with named members and their types.
 */
data class StructSymbol(
    val name: String?,  // FIX: Can be null for anonymous structs
    val members: List<StructMember>,  // ADD: The struct's members
    val isComplete: Boolean,  // ADD: Whether this is a complete type (has definition)
    val scope: Scope,  // ADD: Scope where struct is defined
    val entity: Entity.Struct,  // ADD: Back-reference to entity
    val size: Long?,  // ADD: Size in bytes (null if incomplete)
    val alignment: Long?,  // ADD: Alignment requirement (null if incomplete)
) {
    val isAnonymous: Boolean
        get() = name == null
}

/**
 * Represents a member of a struct.
 */
data class StructMember(
    val name: String?,  // Can be null for anonymous members (C11 feature)
    val type: QualType,
    val offset: Long,  // Byte offset from start of struct
    val bitFieldWidth: Int?,  // Bit width if this is a bit-field, null otherwise
)

/**
 * Symbol for an enum type.
 * Represents an enumeration with named integer constants.
 */
data class EnumSymbol(
    val name: String?,  // FIX: Can be null for anonymous enums
    val constants: Map<String, Long>,  // ADD: Name -> value mapping for enum constants
    val underlyingType: QualType,  // ADD: Usually int, but implementation-defined
    val scope: Scope,  // ADD: Scope where enum is defined
    val entity: Entity.Enum,  // ADD: Back-reference to entity
) {
    val isAnonymous: Boolean
        get() = name == null
}
```

## SymbolTable Implementation

```kotlin
class SymbolTable {
    // Maps for looking up symbols by name within a translation unit
    private val typedefs = mutableMapOf<String, TypedefSymbol>()
    private val variables = mutableMapOf<String, VariableSymbol>()
    private val functions = mutableMapOf<String, FunctionSymbol>()
    private val structTags = mutableMapOf<String, StructSymbol>()
    private val enumTags = mutableMapOf<String, EnumSymbol>()
    
    // Map parse tree contexts to symbols (for AST construction)
    private val typedefContextMap = mutableMapOf<ParserRuleContext, TypedefSymbol>()
    private val variableContextMap = mutableMapOf<ParserRuleContext, VariableSymbol>()
    private val functionContextMap = mutableMapOf<ParserRuleContext, FunctionSymbol>()
    private val structContextMap = mutableMapOf<ParserRuleContext, StructSymbol>()
    private val enumContextMap = mutableMapOf<ParserRuleContext, EnumSymbol>()
    
    // Enum constants are in the ordinary namespace, not tag namespace
    private val enumConstants = mutableMapOf<String, EnumConstant>()
    
    // ADD: Track all external symbols for linking phase
    private val _externalVariables = mutableListOf<VariableSymbol>()
    private val _externalFunctions = mutableListOf<FunctionSymbol>()
    
    val externalVariables: List<VariableSymbol>
        get() = _externalVariables.toList()
    
    val externalFunctions: List<FunctionSymbol>
        get() = _externalFunctions.toList()
    
    fun addTypedef(ctx: ParserRuleContext, symbol: TypedefSymbol) {
        typedefs[symbol.name] = symbol
        typedefContextMap[ctx] = symbol
    }
    
    fun addVariable(ctx: ParserRuleContext, symbol: VariableSymbol) {
        variables[symbol.name] = symbol
        variableContextMap[ctx] = symbol
        
        // Track external variables for linking
        if (symbol.linkage == Linkage.EXTERNAL) {
            _externalVariables.add(symbol)
        }
    }
    
    fun addFunction(ctx: ParserRuleContext, symbol: FunctionSymbol) {
        functions[symbol.name] = symbol
        functionContextMap[ctx] = symbol
        
        // Track external functions for linking
        if (symbol.linkage == Linkage.EXTERNAL) {
            _externalFunctions.add(symbol)
        }
    }
    
    fun addStruct(ctx: ParserRuleContext, symbol: StructSymbol) {
        if (symbol.name != null) {
            structTags[symbol.name] = symbol
        }
        structContextMap[ctx] = symbol
    }
    
    fun addEnum(ctx: ParserRuleContext, symbol: EnumSymbol) {
        if (symbol.name != null) {
            enumTags[symbol.name] = symbol
        }
        enumContextMap[ctx] = symbol
        
        // Register all enum constants in the ordinary namespace
        symbol.constants.forEach { (constantName, value) ->
            enumConstants[constantName] = EnumConstant(
                name = constantName,
                value = value,
                enumSymbol = symbol,
            )
        }
    }
    
    // Lookup methods by name
    fun lookupTypedef(name: String): QualType? {
        return typedefs[name]?.type
    }
    
    fun lookupTypedefSymbol(name: String): TypedefSymbol? {
        return typedefs[name]
    }
    
    fun lookupVariable(name: String): VariableSymbol? {
        return variables[name]
    }
    
    fun lookupFunction(name: String): FunctionSymbol? {
        return functions[name]
    }
    
    fun lookupStructTag(name: String): StructSymbol? {
        return structTags[name]
    }
    
    fun lookupEnumTag(name: String): EnumSymbol? {
        return enumTags[name]
    }
    
    fun lookupEnumConstant(name: String): Long? {
        return enumConstants[name]?.value
    }
    
    fun lookupEnumConstantSymbol(name: String): EnumConstant? {
        return enumConstants[name]
    }
    
    // Lookup methods by context (for AST construction)
    fun getTypedef(ctx: ParserRuleContext): TypedefSymbol? {
        return typedefContextMap[ctx]
    }
    
    fun getVariable(ctx: ParserRuleContext): VariableSymbol? {
        return variableContextMap[ctx]
    }
    
    fun getFunction(ctx: ParserRuleContext): FunctionSymbol? {
        return functionContextMap[ctx]
    }
    
    fun getStruct(ctx: ParserRuleContext): StructSymbol? {
        return structContextMap[ctx]
    }
    
    fun getEnum(ctx: ParserRuleContext): EnumSymbol? {
        return enumContextMap[ctx]
    }
    
    // Get all symbols (for iteration)
    fun getAllTypedefs(): Collection<TypedefSymbol> = typedefs.values
    fun getAllVariables(): Collection<VariableSymbol> = variables.values
    fun getAllFunctions(): Collection<FunctionSymbol> = functions.values
    fun getAllStructs(): Collection<StructSymbol> = structTags.values
    fun getAllEnums(): Collection<EnumSymbol> = enumTags.values
}

/**
 * Represents an enum constant (enumerator).
 */
data class EnumConstant(
    val name: String,
    val value: Long,
    val enumSymbol: EnumSymbol,  // Back-reference to the enum it belongs to
)
```

## EntityTable Extensions

You need to add methods to look up entities by name:

```kotlin
class EntityTable {
    // ... existing maps ...
    
    // ADD: Name-based lookup maps (for type resolution)
    private val typedefsByName = mutableMapOf<String, Entity.Typedef>()
    private val structsByName = mutableMapOf<String, Entity.Struct>()
    private val enumsByName = mutableMapOf<String, Entity.Enum>()
    
    fun registerTypedef(ctx: ParserRuleContext, entity: Entity.Typedef) {
        typedefMap[ctx] = entity
        if (entity.name != null) {
            typedefsByName[entity.name] = entity
        }
    }
    
    fun registerStruct(ctx: ParserRuleContext, entity: Entity.Struct) {
        structMap[ctx] = entity
        if (entity.name != null) {
            structsByName[entity.name] = entity
        }
    }
    
    fun registerEnum(ctx: ParserRuleContext, entity: Entity.Enum) {
        enumMap[ctx] = entity
        if (entity.name != null) {
            enumsByName[entity.name] = entity
        }
    }
    
    // ADD: Lookup by name
    fun getStructByName(name: String): Entity.Struct {
        return structsByName[name] 
            ?: throw TypeException("Undefined struct: $name")
    }
    
    fun getEnumByName(name: String): Entity.Enum {
        return enumsByName[name] 
            ?: throw TypeException("Undefined enum: $name")
    }
    
    fun getTypedefByName(name: String): Entity.Typedef? {
        return typedefsByName[name]
    }
    
    // ... existing methods ...
}
```

## TypeResolver Improvements

```kotlin
class TypeResolver(
    override val reporter: ErrorReporter,
    override val source: SourceFile,
    private val entityTable: EntityTable,
    private val symbolTable: SymbolTable,
) : ParserReporting {
    private val constantEvaluator = ConstantExpressionEvaluator(
        reporter = reporter,
        source = source,
        symbolTable = symbolTable,
    )
    
    // Cache for recursive struct types
    private val structCache = mutableMapOf<Entity.Struct, StructSymbol>()

    fun resolveTypedef(entity: Entity.Typedef): TypedefSymbol {
        val declaration = entity.declarations.first()
        val baseType = buildBaseType(declaration.declarationSpecifier)
        val qualType = applyDeclarator(baseType, declaration.declarator)
        
        return TypedefSymbol(
            name = entity.name,
            type = qualType,
            scope = entity.scope,
            entity = entity,
        )
    }

    fun resolveVariable(entity: Entity.Variable): VariableSymbol {
        val declaration = entity.definition ?: entity.declarations.first()
        val baseType = buildBaseType(declaration.declarationSpecifier)
        val qualType = applyDeclarator(baseType, declaration.declarator)
        
        return VariableSymbol(
            name = entity.name,
            type = qualType,
            storage = declaration.declarationSpecifier.storage,
            linkage = entity.linkage,
            scope = entity.scope,
            entity = entity,
        )
    }

    fun resolveFunction(entity: Entity.Function): FunctionSymbol {
        val declaration = entity.definition ?: entity.declarations.first()
        val baseType = buildBaseType(declaration.declarationSpecifier)
        val declarator = declaration.declarator as? Declarator.FunctionDeclarator 
            ?: error("Function must have function declarator")
        
        val returnType = applyDeclarator(baseType, declarator.declarator)
        val parameterTypes = declaration.parameters.map { param ->
            val paramBaseType = buildBaseType(param.declarationSpecifier)
            applyDeclarator(paramBaseType, param.declarator)
        }
        
        return FunctionSymbol(
            name = entity.name,
            returnType = returnType,
            storage = declaration.declarationSpecifier.storage,
            linkage = entity.linkage,
            parameterTypes = parameterTypes,
            scope = entity.scope,
            entity = entity,
        )
    }

    fun resolveStruct(entity: Entity.Struct): StructSymbol {
        // Check cache for recursive types
        structCache[entity]?.let { return it }
        
        val definition = entity.definition ?: entity.declarations.first()
        
        if (!definition.isDefinition) {
            // Forward declaration - incomplete type
            val incomplete = StructSymbol(
                name = definition.name,
                members = emptyList(),
                isComplete = false,
                scope = entity.scope,
                entity = entity,
                size = null,
                alignment = null,
            )
            structCache[entity] = incomplete
            return incomplete
        }
        
        // Create placeholder for recursive references
        val placeholder = StructSymbol(
            name = definition.name,
            members = emptyList(),
            isComplete = false,
            scope = entity.scope,
            entity = entity,
            size = null,
            alignment = null,
        )
        structCache[entity] = placeholder
        
        // Resolve members
        val members = mutableListOf<StructMember>()
        var currentOffset = 0L
        var maxAlignment = 1L
        
        definition.structDeclarations.forEach { structDecl ->
            val baseType = buildBaseType(structDecl.declarationSpecifier)
            
            structDecl.declarators.forEach { structDeclarator ->
                val memberType = structDeclarator.declarator?.let { 
                    applyDeclarator(baseType, it) 
                } ?: baseType
                
                val bitFieldWidth = structDeclarator.bitWidth?.let { ctx ->
                    constantEvaluator.visit(ctx)?.toInt()
                }
                
                // Calculate alignment and offset
                val memberAlignment = getAlignment(memberType)
                maxAlignment = maxOf(maxAlignment, memberAlignment)
                
                // Align current offset
                val alignedOffset = alignTo(currentOffset, memberAlignment)
                
                val member = StructMember(
                    name = structDeclarator.declarator?.name(),
                    type = memberType,
                    offset = alignedOffset,
                    bitFieldWidth = bitFieldWidth,
                )
                
                members.add(member)
                
                // Update offset for next member
                if (bitFieldWidth != null) {
                    // Bit-field handling is complex, simplified here
                    currentOffset = alignedOffset + ((bitFieldWidth + 7) / 8)
                } else {
                    currentOffset = alignedOffset + getSizeOf(memberType)
                }
            }
        }
        
        // Final struct size is aligned to its alignment requirement
        val totalSize = alignTo(currentOffset, maxAlignment)
        
        val complete = StructSymbol(
            name = definition.name,
            members = members,
            isComplete = true,
            scope = entity.scope,
            entity = entity,
            size = totalSize,
            alignment = maxAlignment,
        )
        
        structCache[entity] = complete
        return complete
    }

    fun resolveEnum(entity: Entity.Enum): EnumSymbol {
        val definition = entity.definition ?: entity.declarations.first()
        
        if (!definition.isDefinition) {
            // Forward declaration (not valid in C, but handle gracefully)
            reporter.reportError(
                definition.location,
                "enum forward declarations are not allowed"
            )
            return EnumSymbol(
                name = definition.name,
                constants = emptyMap(),
                underlyingType = QualType(Type.Int(signed = true)),
                scope = entity.scope,
                entity = entity,
            )
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
        
        return EnumSymbol(
            name = definition.name,
            constants = constants,
            underlyingType = QualType(Type.Int(signed = true)),  // C standard: int
            scope = entity.scope,
            entity = entity,
        )
    }

    private fun buildBaseType(declSpec: DeclarationSpecifier): QualType {
        val typeSpecs = declSpec.typeSpecs

        // Check for struct/enum/typedef
        typeSpecs.forEach { typeSpec ->
            when (typeSpec) {
                is TypeSpec.Struct -> {
                    val name = typeSpec.name
                    val entity = if (name != null) {
                        entityTable.getStructByName(name)
                    } else {
                        // Anonymous struct - should have been registered with entity table
                        // This is tricky - you need the context to find the entity
                        throw TypeException("Cannot resolve anonymous struct in this context")
                    }
                    val structSymbol = resolveStruct(entity)
                    return QualType(Type.Struct(structSymbol), declSpec.qualifiers)
                }

                is TypeSpec.Enum -> {
                    val name = typeSpec.name
                    val entity = if (name != null) {
                        entityTable.getEnumByName(name)
                    } else {
                        throw TypeException("Cannot resolve anonymous enum in this context")
                    }
                    val enumSymbol = resolveEnum(entity)
                    return QualType(Type.Enum(enumSymbol), declSpec.qualifiers)
                }

                is TypeSpec.TypedefName -> {
                    return symbolTable.lookupTypedef(typeSpec.name)
                        ?: throw TypeException("Undefined typedef: ${typeSpec.name}")
                }

                else -> Unit // Handled below
            }
        }

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
                // Implicit int (deprecated in C99, error in C23)
                reporter.reportWarning(
                    SourceLocation.UNKNOWN,
                    "type specifier missing, defaults to 'int'"
                )
                Type.Int(signed)
            }

            else -> Type.Int(signed) // "unsigned" by itself, "signed" by itself
        }
        
        return QualType(baseType, declSpec.qualifiers)
    }

    private fun applyDeclarator(baseType: QualType, declarator: Declarator): QualType {
        return when (declarator) {
            is Declarator.IdentifierDeclarator -> {
                baseType
            }

            is Declarator.AnonymousDeclarator -> {
                baseType
            }

            is Declarator.PointerDeclarator -> {
                val pointeeType = applyDeclarator(baseType, declarator.pointee)
                QualType(Type.Pointer(pointeeType), declarator.qualifiers)
            }

            is Declarator.ArrayDeclarator -> {
                val elementType = applyDeclarator(baseType, declarator.elementType)
                val size = declarator.sizeCtx?.let { 
                    constantEvaluator.visit(it)
                }
                
                if (size != null && size <= 0) {
                    reporter.reportError(
                        declarator.location, 
                        "array size must be positive, got $size"
                    )
                }
                
                QualType(Type.Array(elementType, size))
            }

            is Declarator.FunctionDeclarator -> {
                val returnType = applyDeclarator(baseType, declarator.declarator)
                
                // Apply array-to-pointer and function-to-pointer decay for parameters
                val params = declarator.parameters.map { p ->
                    val paramBaseType = buildBaseType(p.declarationSpecifier)
                    val paramType = applyDeclarator(paramBaseType, p.declarator)
                    
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
                    baseType.type !is Type.Bool) {
                    reporter.reportError(
                        declarator.location,
                        "bit-field must have integral type"
                    )
                }
                
                QualType(Type.BitField(baseType, declarator.width))
            }
        }
    }
    
    private fun getSizeOf(qualType: QualType): Long {
        return when (val type = qualType.type) {
            is Type.Void -> 1  // GCC extension
            is Type.Bool -> 1
            is Type.Char -> 1
            is Type.Short -> 2
            is Type.Int -> 4
            is Type.Long -> 8  // Assuming 64-bit platform
            is Type.LongLong -> 8
            is Type.Float -> 4
            is Type.Double -> 8
            is Type.LongDouble -> 16
            is Type.Pointer -> 8  // Assuming 64-bit platform
            is Type.Array -> {
                if (type.size == null) {
                    throw TypeException("Cannot compute size of incomplete array")
                }
                type.size * getSizeOf(type.elementType)
            }
            is Type.Struct -> {
                type.symbol.size ?: throw TypeException("Cannot compute size of incomplete struct")
            }
            is Type.Enum -> 4  // enum is int-sized
            is Type.Function -> throw TypeException("Cannot compute size of function type")
            is Type.BitField -> {
                // Bit-field size depends on the underlying type
                getSizeOf(type.baseType)
            }
        }
    }
    
    private fun getAlignment(qualType: QualType): Long {
        return when (val type = qualType.type) {
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
            is Type.Array -> getAlignment(type.elementType)
            is Type.Struct -> {
                type.symbol.alignment ?: 1
            }
            is Type.Enum -> 4
            is Type.Function -> 1
            is Type.BitField -> getAlignment(type.baseType)
        }
    }
    
    private fun alignTo(offset: Long, alignment: Long): Long {
        return ((offset + alignment - 1) / alignment) * alignment
    }
}
```

## Updated Type System

```kotlin
data class QualType(
    val type: Type,
    val qualifiers: Set<TypeQualifier> = emptySet(),
) {
    val isConst: Boolean
        get() = qualifiers.contains(TypeQualifier.CONST)
    
    val isVolatile: Boolean
        get() = qualifiers.contains(TypeQualifier.VOLATILE)
    
    val isRestrict: Boolean
        get() = qualifiers.contains(TypeQualifier.RESTRICT)
}

sealed class Type {
    object Void : Type()
    object Bool : Type()
    data class Char(val signed: Boolean) : Type()
    data class Short(val signed: Boolean) : Type()
    data class Int(val signed: Boolean) : Type()
    data class Long(val signed: Boolean) : Type()
    data class LongLong(val signed: Boolean) : Type()
    object Float : Type()
    object Double : Type()
    object LongDouble : Type()
    
    data class Pointer(val pointeeType: QualType) : Type()
    data class Array(val elementType: QualType, val size: Long?) : Type()
    data class Function(val returnType: QualType, val parameterTypes: List<QualType>) : Type()
    data class Struct(val symbol: StructSymbol) : Type()
    data class Enum(val symbol: EnumSymbol) : Type()
    data class BitField(val baseType: QualType, val width: Int) : Type()
}
```

------

Excellent question! The presence of `Type.Error` and `Type.Typedef` reveals some important architectural decisions. Let me provide a comprehensive analysis and recommendation.

## Architectural Analysis

### Current Design Issues

1. **Type.Typedef in the type system** - This mixes type aliases with actual types
2. **Type.Error** - Mixing error handling with type representation
3. **Canonical types** - Your typedef equality check hints at needing canonical types
4. **Tag names in Struct** - Mixing structural vs nominal typing

## Recommended Architecture: Separate Concerns

### Option 1: Canonical Type System (Recommended)

Separate **surface types** (what the user wrote) from **canonical types** (what they actually mean):

```kotlin
/**
 * Canonical types - the "real" types after all typedefs are resolved.
 * These are used for type checking and comparisons.
 */
sealed class CanonicalType {
    object Void : CanonicalType()
    object Bool : CanonicalType()
    
    // Floating point
    object Float : CanonicalType()
    object Double : CanonicalType()
    object LongDouble : CanonicalType()
    
    // Integer types
    data class Char(val signed: Boolean) : CanonicalType()
    data class Short(val signed: Boolean) : CanonicalType()
    data class Int(val signed: Boolean) : CanonicalType()
    data class Long(val signed: Boolean) : CanonicalType()
    data class LongLong(val signed: Boolean) : CanonicalType()
    
    // Composite types
    data class Pointer(val pointee: QualType) : CanonicalType()
    data class Array(val elementType: QualType, val size: Long?) : CanonicalType()
    data class Function(val returnType: QualType, val parameters: List<QualType>) : CanonicalType()
    data class BitField(val base: QualType, val width: Int) : CanonicalType()
    
    // Nominal types (identified by symbol, not structure)
    data class Struct(val symbol: StructSymbol) : CanonicalType() {
        override fun equals(other: Any?): Boolean {
            if (this === other) return true
            if (other !is Struct) return false
            // Struct equality is based on identity (same definition)
            return this.symbol === other.symbol
        }
        
        override fun hashCode(): Int = System.identityHashCode(symbol)
    }
    
    data class Enum(val symbol: EnumSymbol) : CanonicalType() {
        override fun equals(other: Any?): Boolean {
            if (this === other) return true
            if (other !is Enum) return false
            return this.symbol === other.symbol
        }
        
        override fun hashCode(): Int = System.identityHashCode(symbol)
    }
}

/**
 * Qualified type with canonical and surface representation.
 */
data class QualType(
    val canonical: CanonicalType,           // The actual type for type checking
    val qualifiers: Set<TypeQualifier> = emptySet(),
    val surface: SurfaceType? = null,       // Optional: what the user wrote (for diagnostics)
) {
    val isConst: Boolean get() = qualifiers.contains(TypeQualifier.CONST)
    val isVolatile: Boolean get() = qualifiers.contains(TypeQualifier.VOLATILE)
    val isRestrict: Boolean get() = qualifiers.contains(TypeQualifier.RESTRICT)
    
    /**
     * Get the underlying type, stripping qualifiers.
     */
    fun unqualified(): QualType = QualType(canonical, emptySet(), surface)
    
    /**
     * Add qualifiers to this type.
     */
    fun withQualifiers(newQualifiers: Set<TypeQualifier>): QualType {
        return QualType(canonical, qualifiers + newQualifiers, surface)
    }
    
    override fun toString(): String {
        return surface?.toString() ?: canonical.toString()
    }
}

/**
 * Surface types - what the user actually wrote.
 * Used for diagnostics and error messages.
 */
sealed class SurfaceType {
    data class Typedef(val name: String, val underlying: QualType) : SurfaceType() {
        override fun toString(): String = name
    }
    
    data class Canonical(val type: CanonicalType) : SurfaceType() {
        override fun toString(): String = type.toString()
    }
}
```

**Usage:**

```kotlin
// When resolving a typedef
fun resolveTypedef(entity: Entity.Typedef): QualType {
    val underlyingType = /* resolve the underlying type */
    
    return QualType(
        canonical = underlyingType.canonical,  // Same canonical type
        qualifiers = underlyingType.qualifiers,
        surface = SurfaceType.Typedef(entity.name, underlyingType)  // But preserve typedef in surface
    )
}

// Type checking - always use canonical
fun areTypesCompatible(t1: QualType, t2: QualType): Boolean {
    return t1.canonical == t2.canonical  // Typedefs don't matter!
}

// Error messages - use surface
fun reportTypeMismatch(expected: QualType, actual: QualType) {
    reporter.reportError(
        location,
        "expected type '$expected', got '$actual'"  // Shows typedefs to user
    )
}
```

## Handling Type.Error

### Recommended: Result Type Pattern

Instead of `Type.Error`, use a result type that can represent success or failure:

```kotlin
/**
 * Result of type resolution.
 */
sealed class TypeResult {
    data class Success(val type: QualType) : TypeResult()
    data class Error(val message: String, val location: SourceLocation) : TypeResult()
    
    fun getOrNull(): QualType? = when (this) {
        is Success -> type
        is Error -> null
    }
    
    fun getOrError(reporter: ErrorReporter): QualType? {
        return when (this) {
            is Success -> type
            is Error -> {
                reporter.reportError(location, message)
                null
            }
        }
    }
}
```

**Or: Error recovery with a special error type**

If you want to continue compilation after type errors:

```kotlin
sealed class CanonicalType {
    // ... existing types ...
    
    /**
     * Sentinel type for error recovery.
     * Used to continue compilation after type errors.
     */
    object Error : CanonicalType() {
        override fun toString(): String = "<error-type>"
    }
}

// In type resolver
fun resolveVariable(entity: Entity.Variable): VariableSymbol {
    val type = try {
        val baseType = buildBaseType(declaration.declarationSpecifier)
        applyDeclarator(baseType, declaration.declarator)
    } catch (e: TypeException) {
        reporter.reportError(declaration.location, e.message ?: "Type error")
        QualType(CanonicalType.Error)  // Continue with error type
    }
    
    return VariableSymbol(name = entity.name, type = type, ...)
}

// In type checking
fun checkAssignment(lhs: QualType, rhs: QualType): Boolean {
    // Error types are compatible with everything (to avoid cascading errors)
    if (lhs.canonical is CanonicalType.Error || rhs.canonical is CanonicalType.Error) {
        return true
    }
    
    return areTypesCompatible(lhs, rhs)
}
```

## My Complete Recommendation

```kotlin
// ============================================================================
// CANONICAL TYPE SYSTEM - Used for type checking
// ============================================================================

sealed class CanonicalType {
    object Error : CanonicalType()  // For error recovery
    object Void : CanonicalType()
    object Bool : CanonicalType()
    
    // Floating point
    object Float : CanonicalType()
    object Double : CanonicalType()
    object LongDouble : CanonicalType()
    
    // Integer types
    data class Char(val signed: Boolean) : CanonicalType()
    data class Short(val signed: Boolean) : CanonicalType()
    data class Int(val signed: Boolean) : CanonicalType()
    data class Long(val signed: Boolean) : CanonicalType()
    data class LongLong(val signed: Boolean) : CanonicalType()
    
    // Composite types
    data class Pointer(val pointee: QualType) : CanonicalType()
    data class Array(val elementType: QualType, val size: Long?) : CanonicalType()
    data class Function(val returnType: QualType, val parameters: List<QualType>) : CanonicalType()
    data class BitField(val base: QualType, val width: Int) : CanonicalType()
    
    // Nominal types
    data class Struct(val symbol: StructSymbol) : CanonicalType() {
        override fun equals(other: Any?): Boolean = 
            other is Struct && this.symbol === other.symbol
        override fun hashCode(): Int = System.identityHashCode(symbol)
    }
    
    data class Enum(val symbol: EnumSymbol) : CanonicalType() {
        override fun equals(other: Any?): Boolean = 
            other is Enum && this.symbol === other.symbol
        override fun hashCode(): Int = System.identityHashCode(symbol)
    }
    
    override fun toString(): String = when (this) {
        is Error -> "<error-type>"
        is Void -> "void"
        is Bool -> "_Bool"
        is Char -> if (signed) "signed char" else "unsigned char"
        is Short -> if (signed) "short" else "unsigned short"
        is Int -> if (signed) "int" else "unsigned int"
        is Long -> if (signed) "long" else "unsigned long"
        is LongLong -> if (signed) "long long" else "unsigned long long"
        is Float -> "float"
        is Double -> "double"
        is LongDouble -> "long double"
        is Pointer -> "${pointee}*"
        is Array -> "${elementType}[${size?.toString() ?: ""}]"
        is Function -> {
            val params = parameters.joinToString(", ")
            "${returnType}($params)"
        }
        is BitField -> "${base}:${width}"
        is Struct -> symbol.name?.let { "struct $it" } ?: "<anonymous struct>"
        is Enum -> symbol.name?.let { "enum $it" } ?: "<anonymous enum>"
    }
}

// ============================================================================
// QUALIFIED TYPE - Canonical type + qualifiers + optional surface type
// ============================================================================

data class QualType(
    val canonical: CanonicalType,
    val qualifiers: Set<TypeQualifier> = emptySet(),
    private val typedefName: String? = null,  // For diagnostics
) {
    val isConst: Boolean get() = TypeQualifier.CONST in qualifiers
    val isVolatile: Boolean get() = TypeQualifier.VOLATILE in qualifiers
    val isRestrict: Boolean get() = TypeQualifier.RESTRICT in qualifiers
    
    val isError: Boolean get() = canonical is CanonicalType.Error
    
    fun unqualified(): QualType = copy(qualifiers = emptySet())
    
    fun withQualifiers(newQualifiers: Set<TypeQualifier>): QualType {
        return copy(qualifiers = qualifiers + newQualifiers)
    }
    
    fun withTypedefName(name: String): QualType {
        return copy(typedefName = name)
    }
    
    /**
     * Type equality for type checking.
     * Ignores qualifiers and typedef names.
     */
    fun isEquivalentTo(other: QualType): Boolean {
        return canonical == other.canonical
    }
    
    /**
     * Type compatibility including qualifiers.
     */
    fun isCompatibleWith(other: QualType): Boolean {
        // Error types are compatible with everything
        if (isError || other.isError) return true
        
        // Check canonical type equality
        if (canonical != other.canonical) return false
        
        // Check qualifier compatibility (for assignments)
        // lhs must have at least the qualifiers of rhs
        return other.qualifiers.all { it in qualifiers }
    }
    
    override fun toString(): String {
        val base = typedefName ?: canonical.toString()
        return if (qualifiers.isEmpty()) {
            base
        } else {
            qualifiers.joinToString(" ", postfix = " ") + base
        }
    }
}

// ============================================================================
// TYPE RESOLVER UPDATES
// ============================================================================

class TypeResolver(...) {
    fun resolveTypedef(entity: Entity.Typedef): TypedefSymbol {
        val declaration = entity.declarations.first()
        val baseType = buildBaseType(declaration.declarationSpecifier)
        val qualType = applyDeclarator(baseType, declaration.declarator)
        
        // The typedef symbol stores the canonical type
        // but we mark it with the typedef name for diagnostics
        val typedefType = qualType.withTypedefName(entity.name)
        
        return TypedefSymbol(
            name = entity.name,
            type = typedefType,
            scope = entity.scope,
            entity = entity,
        )
    }
    
    private fun buildBaseType(declSpec: DeclarationSpecifier): QualType {
        // Check for typedef first
        declSpec.typeSpecs.forEach { typeSpec ->
            if (typeSpec is TypeSpec.TypedefName) {
                // Look up the typedef and return its type
                val typedefSymbol = symbolTable.lookupTypedefSymbol(typeSpec.name)
                if (typedefSymbol == null) {
                    reporter.reportError(
                        SourceLocation.UNKNOWN,
                        "undefined type '${typeSpec.name}'"
                    )
                    return QualType(CanonicalType.Error)
                }
                
                // Return the typedef's underlying type, preserving the typedef name
                return typedefSymbol.type.withQualifiers(declSpec.qualifiers)
            }
        }
        
        // ... rest of type resolution
        val canonicalType = /* build canonical type */
        return QualType(canonicalType, declSpec.qualifiers)
    }
    
    // Error recovery helper
    private fun errorType(location: SourceLocation, message: String): QualType {
        reporter.reportError(location, message)
        return QualType(CanonicalType.Error)
    }
}

// ============================================================================
// USAGE EXAMPLES
// ============================================================================

// Type checking
fun checkAssignment(lhs: QualType, rhs: QualType): Boolean {
    // Error types are always compatible (avoid cascading errors)
    if (lhs.isError || rhs.isError) return true
    
    return lhs.isCompatibleWith(rhs)
}

// Type equality
fun areTypesEqual(t1: QualType, t2: QualType): Boolean {
    return t1.canonical == t2.canonical
}

// Diagnostic messages preserve typedef names
fun reportTypeMismatch(expected: QualType, actual: QualType) {
    reporter.reportError(
        location,
        "type mismatch: expected '$expected', got '$actual'"
        // If typedef, shows "MyInt" instead of "int"
    )
}

// Canonical type comparison
fun isSameType(t1: QualType, t2: QualType): Boolean {
    // Two types are the same if they have the same canonical type
    return t1.canonical == t2.canonical
}
```

## Summary: Architectural Decisions

### 1. **Typedef Handling**
- ✅ **Store canonical type** in `QualType.canonical`
- ✅ **Preserve typedef name** in `QualType.typedefName` for diagnostics
- ✅ **Type equality ignores typedefs** - based on canonical types
- ❌ Don't use `Type.Typedef` - it complicates the type system

### 2. **Error Handling**
- ✅ **Keep `CanonicalType.Error`** for error recovery
- ✅ **Error types are compatible with everything** (avoids cascading errors)
- ✅ **Report error immediately** when creating error type
- ❌ Don't propagate errors through `Result` types (adds complexity)

### 3. **Struct/Enum Identity**
- ✅ **Use symbol identity** for struct/enum equality
- ✅ **Override equals/hashCode** to use `identityHashCode`
- ✅ **Each struct definition is unique** even if structurally identical

### 4. **Type Comparisons**
- `t1.canonical == t2.canonical` - Type equivalence (ignores typedefs)
- `t1.isCompatibleWith(t2)` - Assignment compatibility (checks qualifiers)
- `t1.isEquivalentTo(t2)` - Same as canonical equality (clearer name)

This architecture is clean, efficient, and matches how production compilers (Clang, GCC) handle types!