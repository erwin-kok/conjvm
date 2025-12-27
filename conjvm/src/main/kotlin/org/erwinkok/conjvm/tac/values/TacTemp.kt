package org.erwinkok.conjvm.tac.values

data class TacTemp(private val id: String) : TacValue {
    override fun toString(): String {
        return "_tmp_$id"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacTemp) {
            return false
        }

        return id == other.id
    }

    override fun hashCode(): Int {
        return id.hashCode()
    }
}
