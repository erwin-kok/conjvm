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
        var hasDefinition = false
        var isTentative = false
        var linkage: Linkage = Linkage.NONE
    }

    class Function(
        scope: Scope,
        name: String,
    ) : Entity(scope, name) {
        val declarations = mutableListOf<Declaration.Function>()
        var definition: Declaration.Function? = null
        var linkage: Linkage = Linkage.EXTERNAL
    }

    class StructTag(
        scope: Scope,
        name: String?,
    ) : Entity(scope, name) {
        val declarations = mutableListOf<Declaration.Struct>()
        var definition: Declaration.Struct? = null
    }

    class EnumTag(
        scope: Scope,
        name: String?,
    ) : Entity(scope, name) {
        val declarations = mutableListOf<Declaration.Enum>()
        var definition: Declaration.Enum? = null
    }
}
