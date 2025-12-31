package org.erwinkok.conjvm.ast

data class Parameter(val type: String, val declarator: Declarator)

sealed class Declarator {
    data class IdentifierDeclarator(val name: String) : Declarator()
    data class PointerDeclarator(val pointee: Declarator, val depth: Int, val qualifiers: List<String>) : Declarator()
    data class FunctionDeclarator(val name: String, val parameters: List<Parameter>) : Declarator()
}
