package org.erwinkok.conjvm.ast.types

import org.erwinkok.conjvm.ast.expressions.Expression
import org.erwinkok.conjvm.parser.SourceLocation

data class TypeName(val declarationSpecifier: DeclarationSpecifier, val abstractDeclarator: Declarator)

data class Parameter(val declarationSpecifier: DeclarationSpecifier, val declarator: Declarator)

sealed class Declarator {
    fun name(): String? = when (this) {
        is IdentifierDeclarator -> this.name
        is AnonymousDeclarator -> null
        is PointerDeclarator -> this.pointee.name()
        is ArrayDeclarator -> this.elementType.name()
        is FunctionDeclarator -> this.declarator.name()
        is BitFieldDeclarator -> this.name
    }

    data class IdentifierDeclarator(val location: SourceLocation, val name: String) : Declarator()
    data class AnonymousDeclarator(val location: SourceLocation) : Declarator()
    data class PointerDeclarator(val location: SourceLocation, val qualifiers: Set<TypeQualifier>, val pointee: Declarator) : Declarator()
    data class FunctionDeclarator(val location: SourceLocation, val declarator: Declarator, val parameters: List<Parameter>) : Declarator()
    data class ArrayDeclarator(val location: SourceLocation, val elementType: Declarator, val size: Expression?) : Declarator()
    data class BitFieldDeclarator(val location: SourceLocation, val name: String, val width: Int) : Declarator()
}
