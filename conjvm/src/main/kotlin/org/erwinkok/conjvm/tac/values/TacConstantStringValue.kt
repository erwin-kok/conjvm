package org.erwinkok.conjvm.tac.values

data class TacConstantStringValue(val value: String) : TacValue {
    override fun toString(): String {
        return value
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacConstantStringValue) {
            return false
        }

        if (value != other.value) return false

        return true
    }

    override fun hashCode(): Int {
        return value.hashCode()
    }
}
