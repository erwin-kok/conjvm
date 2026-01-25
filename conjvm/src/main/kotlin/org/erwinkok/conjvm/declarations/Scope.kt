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
    val children: MutableList<Scope> = mutableListOf(),
) {
    // Namespaces
    private val ordinary = mutableListOf<DeclStub>()
    private val tags = mutableListOf<DeclTagStub>()

    private val typedefs = mutableMapOf<String, MutableList<DeclStub.Typedef>>()
    private val ordinaryMap = mutableMapOf<String, MutableList<DeclStub>>()
    private val tagMap = mutableMapOf<String, MutableList<DeclTagStub>>()

    var isSynthetic: Boolean = false
    val isEmpty: Boolean
        get() = ordinary.isEmpty() && tags.isEmpty() && typedefs.isEmpty() && ordinaryMap.isEmpty() && tagMap.isEmpty()

    fun defineTypedef(location: SourceLocation, declarationSpecifier: DeclarationSpecifier, declarator: Declarator): DeclStub.Typedef {
        val stub = DeclStub.Typedef(location, this, declarationSpecifier, declarator)
        ordinary.add(stub)
        val name = declarator.name()
        typedefs.addToMapList(name, stub)
        return stub
    }

    fun defineFunction(location: SourceLocation, declarationSpecifier: DeclarationSpecifier, declarator: Declarator, parameters: List<Parameter>): DeclStub.Function {
        val stub = DeclStub.Function(location, this, declarationSpecifier, declarator, parameters)
        ordinary.add(stub)
        val name = declarator.name()
        ordinaryMap.addToMapList(name, stub)
        return stub
    }

    fun defineVariable(location: SourceLocation, declarationSpecifier: DeclarationSpecifier, declarator: Declarator): DeclStub.Variable {
        val stub = DeclStub.Variable(location, this, declarationSpecifier, declarator)
        ordinary.add(stub)
        val name = declarator.name()
        ordinaryMap.addToMapList(name, stub)
        return stub
    }

    fun defineStructTag(location: SourceLocation, tag: String?, memberScope: Scope): DeclTagStub.Struct {
        val stub = DeclTagStub.Struct(location, this, tag, memberScope)
        tags.add(stub)
        tagMap.addToMapList(tag, stub)
        return stub
    }

    fun defineEnumTag(location: SourceLocation, tag: String?): DeclTagStub.Enum {
        val stub = DeclTagStub.Enum(location, this, tag)
        tags.add(stub)
        tagMap.addToMapList(tag, stub)
        return stub
    }

    fun defineEnumerator(location: SourceLocation, name: String): DeclStub.Enumerator {
        val enumeratorDecl = DeclStub.Enumerator(location, this, name)
        ordinary.add(enumeratorDecl)
        ordinaryMap.addToMapList(name, enumeratorDecl)
        return enumeratorDecl
    }

    fun lookupTypedef(name: String): List<DeclStub.Typedef> {
        return typedefs[name] ?: parent?.lookupTypedef(name) ?: emptyList()
    }

    fun lookupOrdinary(name: String): List<DeclStub> {
        return ordinaryMap[name] ?: parent?.lookupOrdinary(name) ?: emptyList()
    }

    fun lookupTag(name: String): List<DeclTagStub> {
        return tagMap[name] ?: parent?.lookupTag(name) ?: emptyList()
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
