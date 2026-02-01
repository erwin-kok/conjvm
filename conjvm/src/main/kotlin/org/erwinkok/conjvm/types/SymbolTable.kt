package org.erwinkok.conjvm.types

import org.antlr.v4.runtime.ParserRuleContext
import org.erwinkok.conjvm.declarations.Linkage

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

    fun getAllTypedefs(): Collection<TypedefSymbol> = typedefs.values
    fun getAllVariables(): Collection<VariableSymbol> = variables.values
    fun getAllFunctions(): Collection<FunctionSymbol> = functions.values
    fun getAllStructs(): Collection<StructSymbol> = structTags.values
    fun getAllEnums(): Collection<EnumSymbol> = enumTags.values

    fun resolve(name: String): String? {
        // TODO
        return null
    }

    fun defineTypedef(name: String, type: QualType) {
//        TODO("Not yet implemented")
    }
}
