package org.erwinkok.conjvm.ast.types

class Scope(val parent: Scope? = null) {
    private val symbols = mutableMapOf<String, Symbol>()

    fun define(symbol: Symbol) {
        if (symbols.containsKey(symbol.name)) {
            throw TypeException("symbol '${symbol.name}' already defined in this scope")
        }
        symbols[symbol.name] = symbol
    }

    fun resolve(name: String): Symbol? {
        return symbols[name] ?: parent?.resolve(name)
    }

    fun allSymbols(): Collection<Symbol> = symbols.values
}
