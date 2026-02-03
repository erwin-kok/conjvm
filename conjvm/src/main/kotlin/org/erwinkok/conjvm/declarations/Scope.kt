package org.erwinkok.conjvm.declarations

import org.erwinkok.conjvm.types.QualType
import java.util.UUID

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

    // Entities in this scope
    private val typedefs = mutableMapOf<String, Entity.Typedef>()
    private val variables = mutableMapOf<String, Entity.Variable>()
    private val functions = mutableMapOf<String, Entity.Function>()
    private val structs = mutableMapOf<String, Entity.Struct>()
    private val enums = mutableMapOf<String, Entity.Enum>()
    private val labels = mutableMapOf<String, Entity.Label>()

    // Enum constants (in ordinary namespace)
    private val enumConstants = mutableMapOf<String, EnumConstant>()

    // Namespaces
    private val ordinaryNamespace = mutableSetOf<String>()
    private val tagNamespace = mutableSetOf<String>()
    private val labelNamespace = mutableSetOf<String>()

    private var isSynthetic: Boolean = false
    private var isFrozen: Boolean = false

    val isEmpty: Boolean
        get() = ordinaryNamespace.isEmpty() && tagNamespace.isEmpty() && labelNamespace.isEmpty()

    fun markAsSynthetic() {
        require(isEmpty) { "Cannot mark non-empty scope as synthetic" }
        isSynthetic = true
    }

    fun markAsFrozen() {
        isFrozen = true
        children.forEach { it.markAsFrozen() }
    }

    fun createChild(childKind: ScopeKind): Scope {
        require(!isFrozen)
        val child = Scope(childKind, this)
        children.add(child)
        return child
    }

    // ========================================================================
    // COLLECTION QUERIES
    // ========================================================================

    val localTypedefs: Collection<Entity.Typedef>
        get() = typedefs.values

    val localVariables: Collection<Entity.Variable>
        get() = variables.values

    val localFunctions: Collection<Entity.Function>
        get() = functions.values

    val localStructs: Collection<Entity.Struct>
        get() = structs.values

    val localEnums: Collection<Entity.Enum>
        get() = enums.values

    val localLabels: Collection<Entity.Label>
        get() = labels.values

    // ========================================================================
    // GET OR CREATE ENTITIES (only in current scope)
    // ========================================================================
    fun getOrCreateTypedefEntity(name: String): Entity.Typedef {
        require(!isFrozen)
        val entity = typedefs.getOrPut(name) { Entity.Typedef(this, name) }
        ordinaryNamespace.add(name)
        return entity
    }

    fun getOrCreateVariableEntity(name: String): Entity.Variable {
        require(!isFrozen)
        val entity = variables.getOrPut(name) { Entity.Variable(this, name) }
        ordinaryNamespace.add(name)
        return entity
    }

    fun getOrCreateFunctionEntity(name: String): Entity.Function {
        require(!isFrozen)
        val entity = functions.getOrPut(name) { Entity.Function(this, name) }
        ordinaryNamespace.add(name)
        return entity
    }

    fun getOrCreateStructEntity(name: String?): Entity.Struct {
        require(!isFrozen)
        return if (name == null) {
            // Anonymous struct - create new entity each time
            Entity.Struct(this, name, UUID.randomUUID())
        } else {
            val entity = structs.getOrPut(name) { Entity.Struct(this, name, UUID.randomUUID()) }
            tagNamespace.add(name)
            entity
        }
    }

    fun getOrCreateEnumEntity(name: String?): Entity.Enum {
        require(!isFrozen)
        return if (name == null) {
            // Anonymous enum - create new entity each time
            Entity.Enum(this, name, UUID.randomUUID())
        } else {
            val entity = enums.getOrPut(name) { Entity.Enum(this, name, UUID.randomUUID()) }
            tagNamespace.add(name)
            entity
        }
    }

    fun getOrCreateLabelEntity(name: String): Entity.Label {
        require(!isFrozen)
        val entity = labels.getOrPut(name) { Entity.Label(this, name) }
        labelNamespace.add(name)
        return entity
    }

    fun registerEnumConstants(enumEntity: Entity.Enum) {
        require(!isFrozen)
        enumEntity.constants?.forEach { (constantName, value) ->
            enumConstants[constantName] = EnumConstant(
                name = constantName,
                value = value,
                enumEntity = enumEntity,
            )
        }
    }

    // ========================================================================
    // LOOKUP ENTITIES (search up the scope chain)
    // ========================================================================

    fun lookupTypedef(name: String): QualType? {
        return typedefs[name]?.type ?: parent?.lookupTypedef(name)
    }

    fun lookupTypedefEntity(name: String): Entity.Typedef? {
        return typedefs[name] ?: parent?.lookupTypedefEntity(name)
    }

    fun lookupVariable(name: String): Entity.Variable? {
        return variables[name] ?: parent?.lookupVariable(name)
    }

    fun lookupFunction(name: String): Entity.Function? {
        return functions[name] ?: parent?.lookupFunction(name)
    }

    fun lookupStructTag(name: String): Entity.Struct? {
        return structs[name] ?: parent?.lookupStructTag(name)
    }

    fun lookupEnumTag(name: String): Entity.Enum? {
        return enums[name] ?: parent?.lookupEnumTag(name)
    }

    fun lookupEnumConstant(name: String): Long? {
        return enumConstants[name]?.value ?: parent?.lookupEnumConstant(name)
    }

    fun lookupEnumConstantEntity(name: String): EnumConstant? {
        return enumConstants[name] ?: parent?.lookupEnumConstantEntity(name)
    }

    fun lookupLabel(name: String): Entity.Label? {
        // Labels are function-scoped only, don't search parent scopes
        return labels[name]
    }

    // ========================================================================
    // HELPER QUERIES
    // ========================================================================

    fun isTypedefName(name: String): Boolean {
        return lookupTypedefEntity(name) != null
    }

    fun isDeclaredLocally(name: String): Boolean {
        return name in ordinaryNamespace
    }

    fun isTagDeclaredLocally(name: String): Boolean {
        return name in tagNamespace
    }

    /**
     * Get all external variables (for linking).
     */
    fun getExternalVariables(): List<Entity.Variable> {
        return if (kind != ScopeKind.FILE) {
            parent?.getExternalVariables() ?: emptyList()
        } else {
            localVariables.filter { it.linkage == Linkage.EXTERNAL }
        }
    }

    /**
     * Get all external functions (for linking).
     */
    fun getExternalFunctions(): List<Entity.Function> {
        return if (kind != ScopeKind.FILE) {
            parent?.getExternalFunctions() ?: emptyList()
        } else {
            localFunctions.filter { it.linkage == Linkage.EXTERNAL }
        }
    }

    override fun toString(): String {
        return "$kind(vars=${variables.size}, funcs=${functions.size}, typedefs=${typedefs.size})"
    }
}
