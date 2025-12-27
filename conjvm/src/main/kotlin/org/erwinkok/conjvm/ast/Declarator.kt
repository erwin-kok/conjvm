package org.erwinkok.conjvm.ast

class Declarator(val location: SourceLocation, val pointer: Boolean, val name: String) {
    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is Declarator) {
            return false
        }
        if (pointer != other.pointer) return false
        if (name != other.name) return false

        return true
    }

    override fun hashCode(): Int {
        var result = pointer.hashCode()
        result = 31 * result + name.hashCode()
        return result
    }
}
