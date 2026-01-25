package org.erwinkok.conjvm.declarations

import org.erwinkok.conjvm.parser.SourceLocation
import java.util.UUID

enum class Linkage {
    NONE,
    INTERNAL,
    EXTERNAL,
}

sealed class Entity(
    val location: SourceLocation,
    val scope: Scope,
    val name: String?,
) {
    class Typedef(
        location: SourceLocation,
        scope: Scope,
        val declarationSpecifier: DeclarationSpecifier,
        val declarator: Declarator,
    ) : Entity(location, scope, declarator.name())

    class Variable(
        location: SourceLocation,
        scope: Scope,
        val declarationSpecifier: DeclarationSpecifier,
        val declarator: Declarator,
    ) : Entity(location, scope, declarator.name())

    class Function(
        location: SourceLocation,
        scope: Scope,
        val declarationSpecifier: DeclarationSpecifier,
        val declarator: Declarator,
        val parameters: List<Parameter>,
    ) : Entity(location, scope, declarator.name())

    class Enumerator(
        location: SourceLocation,
        scope: Scope,
        name: String,
    ) : Entity(location, scope, name)

    sealed class Tag(
        location: SourceLocation,
        scope: Scope,
        name: String?,
    ) : Entity(location, scope, name) {
        class Struct(
            location: SourceLocation,
            scope: Scope,
            name: String?,
            val memberScope: Scope,
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
