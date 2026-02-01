package org.erwinkok.conjvm.tac.values

data class TacConstantCharacterValue(val value: Char) : TacValue {
    override fun toString(): String {
        return value.toString()
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacConstantCharacterValue) {
            return false
        }

        if (value != other.value) return false

        return true
    }

    override fun hashCode(): Int {
        return value.hashCode()
    }
}
