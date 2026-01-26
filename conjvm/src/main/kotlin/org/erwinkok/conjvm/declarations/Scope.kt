package org.erwinkok.conjvm.declarations

enum class ScopeKind {
    FILE,
    FUNCTION,
    BLOCK,
    FOR,
}

class Scope(
    val kind: ScopeKind,
    val parent: Scope? = null,
) {
    val children: MutableList<Scope> = mutableListOf()

    private val _typedefs = mutableMapOf<String, Entity.Typedef>()
    private val _variables = mutableMapOf<String, Entity.Variable>()
    private val _functions = mutableMapOf<String, Entity.Function>()
    private val _structs = mutableMapOf<String, Entity.Struct>()
    private val _enums = mutableMapOf<String, Entity.Enum>()
    private val _labels = mutableMapOf<String, Entity.Label>()

    // Namespaces
    private val ordinaryNamespace = mutableSetOf<String>()
    private val tagNamespace = mutableSetOf<String>()
    private val labelNamespace = mutableSetOf<String>()

    var isSynthetic: Boolean = false
    val typedefs: List<Entity.Typedef>
        get() = _typedefs.values.toList()
    val variables: List<Entity.Variable>
        get() = _variables.values.toList()
    val functions: List<Entity.Function>
        get() = _functions.values.toList()
    val structs: List<Entity.Struct>
        get() = _structs.values.toList()
    val enums: List<Entity.Enum>
        get() = _enums.values.toList()
    val labels: List<Entity.Label>
        get() = _labels.values.toList()
    val isEmpty: Boolean
        get() = ordinaryNamespace.isEmpty() && tagNamespace.isEmpty() && labelNamespace.isEmpty()

    fun getOrCreateTypedefEntity(name: String): Entity.Typedef {
        val entity = _typedefs.getOrPut(name) { Entity.Typedef(this, name) }
        ordinaryNamespace.add(name)
        return entity
    }

    fun lookupTypedefEntity(name: String): Entity.Typedef? {
        return _typedefs[name] ?: parent?.lookupTypedefEntity(name)
    }

    fun isTypedefName(name: String): Boolean {
        return lookupTypedefEntity(name) != null
    }

    fun getOrCreateVariableEntity(name: String): Entity.Variable {
        val entity = _variables.getOrPut(name) { Entity.Variable(this, name) }
        ordinaryNamespace.add(name)
        return entity
    }

    fun lookupVariableEntity(name: String): Entity.Variable? {
        return _variables[name] ?: parent?.lookupVariableEntity(name)
    }

    fun getOrCreateFunctionEntity(name: String): Entity.Function {
        val entity = _functions.getOrPut(name) { Entity.Function(this, name) }
        ordinaryNamespace.add(name)
        return entity
    }

    fun lookupFunctionEntity(name: String): Entity.Function? {
        return _functions[name] ?: parent?.lookupFunctionEntity(name)
    }

    fun getOrCreateStructEntity(name: String?): Entity.Struct {
        return if (name == null) {
            Entity.Struct(this, name)
        } else {
            val entity = _structs.getOrPut(name) { Entity.Struct(this, name) }
            tagNamespace.add(name)
            entity
        }
    }

    fun lookupStructEntity(name: String?): Entity.Struct? {
        if (name == null) {
            return null
        }
        return _structs[name] ?: parent?.lookupStructEntity(name)
    }

    fun getOrCreateEnumEntity(name: String?): Entity.Enum {
        return if (name == null) {
            Entity.Enum(this, name)
        } else {
            val entity = _enums.getOrPut(name) { Entity.Enum(this, name) }
            tagNamespace.add(name)
            entity
        }
    }

    fun lookupEnumEntity(name: String?): Entity.Enum? {
        if (name == null) {
            return null
        }
        return _enums[name] ?: parent?.lookupEnumEntity(name)
    }

    fun lookupOrdinary(name: String): Boolean {
        if (ordinaryNamespace.contains(name)) {
            return true
        }
        return parent?.lookupOrdinary(name) ?: false
    }

    fun lookupTag(name: String?): Boolean {
        if (name == null) {
            return false
        }
        if (tagNamespace.contains(name)) {
            return true
        }
        return parent?.lookupTag(name) ?: false
    }

    fun getOrCreateLabelEntity(name: String): Entity.Label {
        val entity = _labels.getOrPut(name) { Entity.Label(this, name) }
        labelNamespace.add(name)
        return entity
    }

    fun lookupLabel(name: String): Entity.Label? {
        // Labels are function-scoped only, don't search parent
        return _labels[name]
    }

    override fun toString(): String {
        return "$kind(vars=${_variables.size}, funcs=${_functions.size}, typedefs=${_typedefs.size})"
    }
}
