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

    private val typedefs = mutableMapOf<String, Entity.Typedef>()
    private val variables = mutableMapOf<String, Entity.Variable>()
    private val functions = mutableMapOf<String, Entity.Function>()
    private val structTags = mutableMapOf<String, Entity.StructTag>()
    private val enumTags = mutableMapOf<String, Entity.EnumTag>()

    // Namespaces
    private val ordinary = mutableSetOf<String>()
    private val tags = mutableSetOf<String>()

    var isSynthetic: Boolean = false
    val isEmpty: Boolean
        get() = ordinary.isEmpty() && tags.isEmpty()

    fun addTypedefDeclaration(name: String, typedef: Declaration.Typedef): Entity.Typedef {
        val entity = typedefs.getOrPut(name) { Entity.Typedef(this, name) }
        entity.declarations.add(typedef)
        ordinary.add(name)
        return entity
    }

    fun lookupTypedef(name: String): Entity.Typedef? {
        return typedefs[name] ?: parent?.lookupTypedef(name)
    }

    fun isTypedefName(name: String): Boolean {
        return lookupTypedef(name) != null
    }

    fun addVariableDeclaration(
        name: String,
        variable: Declaration.Variable,
    ): Entity.Variable {
        val entity = variables.getOrPut(name) { Entity.Variable(this, name) }
        if (entity.declarations.isNotEmpty()) {
            validateRedeclaration(entity.declarations.first(), variable)
        }
        if (entity.declarations.isEmpty()) {
            entity.linkage = determineLinkage(variable, kind)
        }
        entity.declarations.add(variable)
        ordinary.add(name)
        val hasExternStorage = variable.declarationSpecifier.storage.contains(StorageClass.EXTERN)
        when {
            variable.initializer != null || variable.isSyntheticZeroInit -> {
                entity.hasDefinition = true
                entity.isTentative = false
            }

            kind == ScopeKind.FILE && !hasExternStorage -> {
                // Only tentative if no extern and at file scope
                if (!entity.hasDefinition) {
                    entity.isTentative = true
                }
            }

            hasExternStorage -> {
                // extern declarations are never definitions
                // Keep existing state
            }
        }
        return entity
    }

    fun lookupVariable(name: String): Entity.Variable? {
        return variables[name] ?: parent?.lookupVariable(name)
    }

    fun addFunctionDeclaration(
        name: String,
        function: Declaration.Function,
    ): Entity.Function {
        val entity = functions.getOrPut(name) { Entity.Function(this, name) }
        entity.declarations.add(function)
        ordinary.add(name)
        return entity
    }

    fun lookupFunction(name: String): Entity.Function? {
        return functions[name] ?: parent?.lookupFunction(name)
    }

    fun defineTag(name: String) {
        tags.add(name)
    }

    fun lookupTag(name: String?): Boolean {
        if (name == null) {
            return false
        }
        if (tags.contains(name)) {
            return true
        }
        return parent?.lookupTag(name) ?: false
    }

    /**
     * Handles tentative definitions per C17 §6.9.2:
     * A declaration with external linkage and no initializer
     * is a tentative definition at file scope.
     */
    fun resolveTentativeDefinitions() {
        if (kind == ScopeKind.FILE) {
            variables.values.forEach { entity ->
                if (entity.isTentative && !entity.hasDefinition) {
                    entity.hasDefinition = true
                    entity.isTentative = false
                    val firstDecl = entity.declarations.firstOrNull()
                    if (firstDecl != null) {
                        val syntheticDecl = Declaration.Variable(
                            location = firstDecl.location,
                            scope = this,
                            declarationSpecifier = firstDecl.declarationSpecifier,
                            declarator = firstDecl.declarator,
                            initializer = null,
                            isSyntheticZeroInit = true,
                        )
                        entity.declarations.add(syntheticDecl)
                    }
                }
            }
        }
        children.forEach { it.resolveTentativeDefinitions() }
    }

    private fun determineLinkage(decl: Declaration.Variable, scopeKind: ScopeKind): Linkage {
        return when {
            decl.declarationSpecifier.storage.contains(StorageClass.EXTERN) -> Linkage.EXTERNAL
            decl.declarationSpecifier.storage.contains(StorageClass.STATIC) -> Linkage.INTERNAL
            scopeKind == ScopeKind.FILE -> Linkage.EXTERNAL
            else -> Linkage.NONE
        }
    }

    private fun validateRedeclaration(
        existing: Declaration.Variable,
        new: Declaration.Variable,
    ) {
        val existingStorage = existing.declarationSpecifier.storage
        val newStorage = new.declarationSpecifier.storage
        if (
            existingStorage.contains(StorageClass.STATIC) &&
            newStorage.contains(StorageClass.EXTERN)
        ) {
            // Error: conflicting storage classes
        }
    }

    override fun toString(): String {
        return "$kind(vars=${variables.size}, funcs=${functions.size}, typedefs=${typedefs.size})"
    }
}
