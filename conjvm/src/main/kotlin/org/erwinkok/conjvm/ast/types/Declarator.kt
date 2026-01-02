package org.erwinkok.conjvm.ast.types

import org.erwinkok.conjvm.ast.SourceLocation
import org.erwinkok.conjvm.ast.expressions.Expression

data class TypeName(val declarationSpecifier: DeclarationSpecifier, val abstractDeclarator: Declarator?)

data class Parameter(val declarationSpecifier: DeclarationSpecifier, val declarator: Declarator)

sealed class Declarator {
    fun name(): String = when (this) {
        is IdentifierDeclarator -> this.name
        is PointerDeclarator -> this.pointee.name()
        is ArrayDeclarator -> this.elementType.name()
        is FunctionDeclarator -> this.declarator.name()
    }

    data class IdentifierDeclarator(val location: SourceLocation, val name: String) : Declarator()
    data class PointerDeclarator(val location: SourceLocation, val qualifiers: List<TypeQualifier>, val pointee: Declarator) : Declarator()
    data class FunctionDeclarator(val location: SourceLocation, val declarator: Declarator, val parameters: List<Parameter>) : Declarator()
    data class ArrayDeclarator(val location: SourceLocation, val size: Expression?, val elementType: Declarator) : Declarator()
}
