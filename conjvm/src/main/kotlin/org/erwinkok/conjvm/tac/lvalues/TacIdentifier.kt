package org.erwinkok.conjvm.tac.lvalues

data class TacIdentifier(val id: String) {
    override fun toString(): String {
        return id
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacIdentifier) {
            return false
        }

        return id == other.id
    }

    override fun hashCode(): Int {
        return id.hashCode()
    }
}
