package org.erwinkok.conjvm.declarations

import org.erwinkok.conjvm.CParser
import org.erwinkok.conjvm.parser.SourceLocation
import java.util.UUID

data class InitDeclarator(
    val declarator: Declarator,
    val initializerCtx: CParser.Assignment_expressionContext?,
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
    val bitWidthCtx: CParser.Constant_expressionContext?,
)

data class Enumerator(
    val location: SourceLocation,
    val text: String,
    val valueCtx: CParser.Constant_expressionContext?,
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
        val initializerCtx: CParser.Assignment_expressionContext?,
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
        val id: UUID = UUID.randomUUID(),
    ) : Declaration(location, scope) {
        val isDefinition = structDeclarations.isNotEmpty()
    }

    class Enum(
        location: SourceLocation,
        scope: Scope,
        override val name: String?,
        val enumerators: List<Enumerator>,
        val id: UUID = UUID.randomUUID(),
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
