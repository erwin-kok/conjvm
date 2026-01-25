package org.erwinkok.conjvm.declarations

import org.erwinkok.conjvm.parser.SourceLocation

enum class ScopeKind {
    FILE,
    FUNCTION,
    BLOCK,
    STRUCT,
    FOR,
}

class Scope(
    val kind: ScopeKind,
    val parent: Scope? = null,
) {
    val children: MutableList<Scope> = mutableListOf()

    // Namespaces
    private val ordinary = mutableListOf<Entity>()
    private val tags = mutableListOf<Entity.Tag>()

    private val typedefs = mutableMapOf<String, MutableList<Entity.Typedef>>()
    private val ordinaryMap = mutableMapOf<String, MutableList<Entity>>()
    private val tagMap = mutableMapOf<String, MutableList<Entity.Tag>>()

    var isSynthetic: Boolean = false
    val isEmpty: Boolean
        get() = ordinary.isEmpty() && tags.isEmpty() && typedefs.isEmpty() && ordinaryMap.isEmpty() && tagMap.isEmpty()

    fun defineTypedef(location: SourceLocation, declarationSpecifier: DeclarationSpecifier, declarator: Declarator): Entity.Typedef {
        val stub = Entity.Typedef(location, this, declarationSpecifier, declarator)
        ordinary.add(stub)
        val name = declarator.name()
        typedefs.addToMapList(name, stub)
        return stub
    }

    fun defineFunction(location: SourceLocation, declarationSpecifier: DeclarationSpecifier, declarator: Declarator, parameters: List<Parameter>): Entity.Function {
        val stub = Entity.Function(location, this, declarationSpecifier, declarator, parameters)
        ordinary.add(stub)
        val name = declarator.name()
        ordinaryMap.addToMapList(name, stub)
        return stub
    }

    fun defineVariable(location: SourceLocation, declarationSpecifier: DeclarationSpecifier, declarator: Declarator): Entity.Variable {
        val stub = Entity.Variable(location, this, declarationSpecifier, declarator)
        ordinary.add(stub)
        val name = declarator.name()
        ordinaryMap.addToMapList(name, stub)
        return stub
    }

    fun defineStructTag(location: SourceLocation, tag: String?, memberScope: Scope): Entity.Tag.Struct {
        val stub = Entity.Tag.Struct(location, this, tag, memberScope)
        tags.add(stub)
        tagMap.addToMapList(tag, stub)
        return stub
    }

    fun defineEnumTag(location: SourceLocation, tag: String?): Entity.Tag.Enum {
        val stub = Entity.Tag.Enum(location, this, tag)
        tags.add(stub)
        tagMap.addToMapList(tag, stub)
        return stub
    }

    fun defineEnumerator(location: SourceLocation, name: String): Entity.Enumerator {
        val enumeratorDecl = Entity.Enumerator(location, this, name)
        ordinary.add(enumeratorDecl)
        ordinaryMap.addToMapList(name, enumeratorDecl)
        return enumeratorDecl
    }

    fun lookupTypedef(name: String): List<Entity.Typedef> {
        return typedefs[name] ?: parent?.lookupTypedef(name) ?: emptyList()
    }

    fun lookupOrdinary(name: String): List<Entity> {
        return ordinaryMap[name] ?: parent?.lookupOrdinary(name) ?: emptyList()
    }

    fun lookupTag(name: String): List<Entity.Tag> {
        return tagMap[name] ?: parent?.lookupTag(name) ?: emptyList()
    }

    fun isTypedefName(name: String): Boolean {
        return lookupTypedef(name).isNotEmpty()
    }

    fun resolveTentativeDefinitions() {
        children.forEach { it.resolveTentativeDefinitions() }
    }

    override fun toString(): String {
        return "$kind"
    }

    private fun <V> MutableMap<String, MutableList<V>>.addToMapList(name: String?, element: V) {
        if (name != null) {
            computeIfAbsent(name) { mutableListOf() }.add(element)
        }
    }
}
