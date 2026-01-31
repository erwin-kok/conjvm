package org.erwinkok.conjvm.declarations

enum class Linkage {
    NONE,
    INTERNAL,
    EXTERNAL,
}

sealed interface Entity {
    val scope: Scope
    val name: String?

    class Typedef(
        override val scope: Scope,
        override val name: String,
    ) : Entity {
        val declarations = mutableListOf<Declaration.Typedef>()
    }

    class Variable(
        override val scope: Scope,
        override val name: String,
    ) : Entity {
        val declarations = mutableListOf<Declaration.Variable>()
        var definition: Declaration.Variable? = null
        var linkage = Linkage.NONE
    }

    class Function(
        override val scope: Scope,
        override val name: String,
    ) : Entity {
        val declarations = mutableListOf<Declaration.Function>()
        var definition: Declaration.Function? = null
        var linkage = Linkage.EXTERNAL
    }

    class Struct(
        override val scope: Scope,
        override val name: String?,
    ) : Entity {
        val declarations = mutableListOf<Declaration.Struct>()
        var definition: Declaration.Struct? = null
    }

    class Enum(
        override val scope: Scope,
        override val name: String?,
    ) : Entity {
        val declarations = mutableListOf<Declaration.Enum>()
        var definition: Declaration.Enum? = null
    }

    class Label(
        override val scope: Scope,
        override val name: String?,
    ) : Entity {
        val declarations = mutableListOf<Declaration.Label>()
    }
}
