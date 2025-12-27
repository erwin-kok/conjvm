package org.erwinkok.conjvm.tac.instructions

import org.erwinkok.conjvm.tac.values.TacValue

class TacStoreIndirectInstruction(val address: TacValue, val value: TacValue) : TacInstruction {
    override fun toString(): String {
        return "StoreIndirect($address) = $value"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacStoreIndirectInstruction) {
            return false
        }

        if (address != other.address) return false
        if (value != other.value) return false

        return true
    }

    override fun hashCode(): Int {
        var result = address.hashCode()
        result = 31 * result + value.hashCode()
        return result
    }
}
