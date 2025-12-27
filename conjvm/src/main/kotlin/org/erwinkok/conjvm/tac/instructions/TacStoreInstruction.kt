package org.erwinkok.conjvm.tac.instructions

import org.erwinkok.conjvm.tac.lvalues.TacIdentifier
import org.erwinkok.conjvm.tac.values.TacValue

class TacStoreInstruction(val address: TacIdentifier, val value: TacValue) : TacInstruction {
    override fun toString(): String {
        return "StoreVar($address) = $value"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacStoreInstruction) {
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
