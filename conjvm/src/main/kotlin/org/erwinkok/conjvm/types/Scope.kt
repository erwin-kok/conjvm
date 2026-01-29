package org.erwinkok.conjvm.types

import org.erwinkok.conjvm.declarations.StorageClass

class Scope(val parent: Scope? = null) {
    private val variableSymbols = mutableMapOf<String, VariableSymbol>()
    private val functionSymbols = mutableMapOf<String, FunctionSymbol>()

    fun resolveVariable(name: String): VariableSymbol? {
        return variableSymbols[name] ?: parent?.resolveVariable(name)
    }

    fun resolveFunction(name: String): FunctionSymbol? {
        return functionSymbols[name] ?: parent?.resolveFunction(name)
    }

    fun defineVariable(name: String?, type: QualType, storage: Set<StorageClass>) {
        if (name != null) {
            val variableSymbol = VariableSymbol(name, type, storage)
            val oldSym = resolveVariable(variableSymbol.name)
            if (oldSym != null && oldSym != variableSymbol) {
                throw TypeException("variable re-definition of ${oldSym.name} is different from ${variableSymbol.name}")
            }
            variableSymbols[name] = variableSymbol
        }
    }

    fun defineFunction(name: String?, type: QualType, storage: Set<StorageClass>) {
        if (name != null) {
            val functionSymbol = FunctionSymbol(name, type, storage)
            val oldSym = resolveFunction(functionSymbol.name)
            if (oldSym != null && oldSym != functionSymbol) {
                throw TypeException("function re-definition of ${oldSym.name} is different from ${functionSymbol.name}")
            }
            functionSymbols[name] = functionSymbol
        }
    }
}
