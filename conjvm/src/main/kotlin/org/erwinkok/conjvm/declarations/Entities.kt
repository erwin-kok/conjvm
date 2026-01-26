package org.erwinkok.conjvm.declarations

enum class Linkage {
    NONE,
    INTERNAL,
    EXTERNAL,
}

sealed class Entity(
    val scope: Scope,
    val name: String?,
) {
    class Typedef(
        scope: Scope,
        name: String,
    ) : Entity(scope, name) {
        val declarations = mutableListOf<Declaration.Typedef>()
    }

    class Variable(
        scope: Scope,
        name: String,
    ) : Entity(scope, name) {
        val declarations = mutableListOf<Declaration.Variable>()
        var definition: Declaration.Variable? = null
        var linkage = Linkage.NONE
    }

    class Function(
        scope: Scope,
        name: String,
    ) : Entity(scope, name) {
        val declarations = mutableListOf<Declaration.Function>()
        var definition: Declaration.Function? = null
        var linkage = Linkage.EXTERNAL
    }

    class Struct(
        scope: Scope,
        name: String?,
    ) : Entity(scope, name) {
        val declarations = mutableListOf<Declaration.Struct>()
        var definition: Declaration.Struct? = null
    }

    class Enum(
        scope: Scope,
        name: String?,
    ) : Entity(scope, name) {
        val declarations = mutableListOf<Declaration.Enum>()
    }

    class Label(
        scope: Scope,
        name: String?,
    ) : Entity(scope, name) {
        val declarations = mutableListOf<Declaration.Label>()
    }
}
