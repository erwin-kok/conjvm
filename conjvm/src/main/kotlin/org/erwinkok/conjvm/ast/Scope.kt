package org.erwinkok.conjvm.ast

class Symbol(val name: String, val type: Type)

class Scope private constructor(val parent: Scope? = null) {
    private val symbols = mutableMapOf<String, Symbol>()

    fun define(symbol: Symbol) {
        symbols[symbol.name] = symbol
    }

    fun lookup(name: String): Symbol? {
        return symbols[name] ?: parent?.lookup(name)
    }

    companion object {
        private var scope = Scope()

        val current: Scope
            get() = scope

        fun enter() {
            scope = Scope(scope)
        }

        fun leave() {
            val parent = scope.parent
            requireNotNull(parent)
            scope = parent
        }
    }
}
