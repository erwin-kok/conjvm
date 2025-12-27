package org.erwinkok.conjvm.tac.lvalues

import org.erwinkok.conjvm.tac.values.TacValue

data class ArrayLValue(val base: TacLValue, val index: TacValue) : TacLValue {
    override fun toString(): String {
        return "$base[$index]"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is ArrayLValue) {
            return false
        }

        if (base != other.base) return false
        if (index != other.index) return false

        return true
    }

    override fun hashCode(): Int {
        var result = base.hashCode()
        result = 31 * result + index.hashCode()
        return result
    }
}
