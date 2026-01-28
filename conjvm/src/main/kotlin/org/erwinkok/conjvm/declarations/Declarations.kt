package org.erwinkok.conjvm.declarations

import org.erwinkok.conjvm.CParser
import org.erwinkok.conjvm.parser.SourceLocation

data class InitDeclarator(
    val declarator: Declarator,
    val initializer: CParser.InitializerContext? = null,
)

data class StructDeclaration(
    val location: SourceLocation,
    val declarationSpecifier: DeclarationSpecifier,
    val declarators: List<StructDeclarator>?,
) {
    val isAnonymous = declarators.isNullOrEmpty()
}

data class StructDeclarator(
    val declarator: Declarator?,
    val bitWidth: CParser.Constant_expressionContext?,
)

data class Enumerator(
    val location: SourceLocation,
    val text: String,
    val value: CParser.Constant_expressionContext?,
)

sealed class Declaration(
    val location: SourceLocation,
    val scope: Scope,
) {
    abstract val name: String?

    class Typedef(
        location: SourceLocation,
        scope: Scope,
        val declarationSpecifier: DeclarationSpecifier,
        val declarator: Declarator,
    ) : Declaration(location, scope) {
        override val name = declarator.name()
    }

    class Variable(
        location: SourceLocation,
        scope: Scope,
        val declarationSpecifier: DeclarationSpecifier,
        val declarator: Declarator,
        val initializer: CParser.InitializerContext?,
        val isSyntheticZeroInit: Boolean = false,
    ) : Declaration(location, scope) {
        override val name = declarator.name()
    }

    class Function(
        location: SourceLocation,
        scope: Scope,
        val declarationSpecifier: DeclarationSpecifier,
        val declarator: Declarator,
        val parameters: List<Parameter>,
    ) : Declaration(location, scope) {
        override val name = declarator.name()
    }

    class Struct(
        location: SourceLocation,
        scope: Scope,
        override val name: String?,
        val structDeclarations: List<StructDeclaration>,
    ) : Declaration(location, scope) {
        val isDefinition = structDeclarations.isNotEmpty()
    }

    class Enum(
        location: SourceLocation,
        scope: Scope,
        override val name: String?,
        val enumerators: List<Enumerator>,
    ) : Declaration(location, scope) {
        val isDefinition = enumerators.isNotEmpty()
    }

    class Label(
        location: SourceLocation,
        scope: Scope,
        override val name: String,
        val isDefined: Boolean, // true for label:, false for goto
    ) : Declaration(location, scope)
}
