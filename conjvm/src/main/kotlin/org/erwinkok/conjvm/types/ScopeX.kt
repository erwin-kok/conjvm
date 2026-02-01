package org.erwinkok.conjvm.types

import org.erwinkok.conjvm.declarations.StorageClass

data class VariableSymbolX(
    val name: String,
    val type: QualType,
    val storage: Set<StorageClass>,
)

data class FunctionSymbolX(
    val name: String,
    val type: QualType,
    val storage: Set<StorageClass>,
)

class ScopeX(val parent: ScopeX? = null) {
    private val variableSymbols = mutableMapOf<String, VariableSymbolX>()
    private val functionSymbols = mutableMapOf<String, FunctionSymbolX>()

    fun resolveVariable(name: String): VariableSymbolX? {
        return variableSymbols[name] ?: parent?.resolveVariable(name)
    }

    fun resolveFunction(name: String): FunctionSymbolX? {
        return functionSymbols[name] ?: parent?.resolveFunction(name)
    }

    fun defineVariable(name: String?, type: QualType, storage: Set<StorageClass>) {
        if (name != null) {
            val variableSymbol = VariableSymbolX(name, type, storage)
            val oldSym = resolveVariable(variableSymbol.name)
            if (oldSym != null && oldSym != variableSymbol) {
                throw TypeException("variable re-definition of ${oldSym.name} is different from ${variableSymbol.name}")
            }
            variableSymbols[name] = variableSymbol
        }
    }

    fun defineFunction(name: String?, type: QualType, storage: Set<StorageClass>) {
        if (name != null) {
            val functionSymbol = FunctionSymbolX(name, type, storage)
            val oldSym = resolveFunction(functionSymbol.name)
            if (oldSym != null && oldSym != functionSymbol) {
                throw TypeException("function re-definition of ${oldSym.name} is different from ${functionSymbol.name}")
            }
            functionSymbols[name] = functionSymbol
        }
    }
}
