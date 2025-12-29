package org.erwinkok.conjvm.ast

import org.erwinkok.conjvm.ast.expressions.Identifier

class Scope private constructor(val parent: Scope? = null) {
    private val symbols = mutableMapOf<String, Identifier>()

    fun define(identifier: Identifier) {
        symbols[identifier.name] = identifier
    }

    fun lookup(name: String): Identifier? {
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
