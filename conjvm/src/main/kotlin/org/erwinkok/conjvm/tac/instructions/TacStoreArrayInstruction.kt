package org.erwinkok.conjvm.tac.instructions

import org.erwinkok.conjvm.tac.values.TacValue

class TacStoreArrayInstruction(val base: TacValue, val index: TacValue, val value: TacValue) : TacInstruction {
    override fun toString(): String {
        return "StoreArray($base, $index) = $value"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacStoreArrayInstruction) {
            return false
        }

        if (base != other.base) return false
        if (index != other.index) return false
        if (value != other.value) return false

        return true
    }

    override fun hashCode(): Int {
        var result = base.hashCode()
        result = 31 * result + index.hashCode()
        result = 31 * result + value.hashCode()
        return result
    }
}
