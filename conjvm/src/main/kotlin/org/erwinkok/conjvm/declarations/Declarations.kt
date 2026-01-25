package org.erwinkok.conjvm.declarations

import org.erwinkok.conjvm.CParser
import org.erwinkok.conjvm.parser.SourceLocation
import java.util.UUID

data class InitDeclarator(val declarator: Declarator, val initializer: CParser.InitializerContext? = null)
class StructDeclaration(val location: SourceLocation, val declarationSpecifier: DeclarationSpecifier, val declarators: List<StructDeclarator>?)
class StructDeclarator(val declarator: Declarator?, val bitWidth: Long?)

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
        val isDefinition: Boolean,
        val parameters: List<Parameter>,
    ) : Declaration(location, scope) {
        override val name = declarator.name()
    }

    class Enumerator(
        location: SourceLocation,
        scope: Scope,
        override val name: String,
        val valueExpression: CParser.Constant_expressionContext? = null,
    ) : Declaration(location, scope)

    class StructMember(
        location: SourceLocation,
        scope: Scope,
        val declarationSpecifier: DeclarationSpecifier,
        val declarator: Declarator?, // null for anonymous bit-fields
        val bitWidth: CParser.Constant_expressionContext?,
    ) : Declaration(location, scope) {
        override val name = declarator?.name()
    }

    class Label(
        location: SourceLocation,
        scope: Scope,
        override val name: String,
        val isDefined: Boolean, // true for label:, false for goto
    ) : Declaration(location, scope)

    sealed class Tag(
        location: SourceLocation,
        scope: Scope,
        override val name: String?,
    ) : Declaration(location, scope) {
        class Struct(
            location: SourceLocation,
            scope: Scope,
            name: String?,
            val memberScope: Scope?,
        ) : Tag(location, scope, name) {
            val uuid = UUID.randomUUID()
        }

        class Enum(
            location: SourceLocation,
            scope: Scope,
            name: String?,
        ) : Tag(location, scope, name) {
            val uuid = UUID.randomUUID()
        }
    }
}
