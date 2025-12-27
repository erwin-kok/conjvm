package org.erwinkok.conjvm.tac.instructions

import org.erwinkok.conjvm.tac.lvalues.TacLValue
import org.erwinkok.conjvm.tac.values.TacTemp

class TacAddressOfInstruction(val dst: TacTemp, val id: TacLValue) : TacInstruction {
    override fun toString(): String {
        return "$dst = AddressOf($id)"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacAddressOfInstruction) {
            return false
        }

        if (dst != other.dst) return false
        if (id != other.id) return false

        return true
    }

    override fun hashCode(): Int {
        var result = dst.hashCode()
        result = 31 * result + id.hashCode()
        return result
    }
}
