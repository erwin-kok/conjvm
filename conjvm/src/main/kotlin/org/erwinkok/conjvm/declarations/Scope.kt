package org.erwinkok.conjvm.declarations

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
    override fun toString(): String {
        return "$kind"
    }
}
