package org.erwinkok.conjvm.tac.instructions

import org.erwinkok.conjvm.tac.values.TacTemp
import org.erwinkok.conjvm.tac.values.TacValue

class TacLoadIndirectInstruction(val dst: TacTemp, val address: TacValue) : TacInstruction {
    override fun toString(): String {
        return "$dst = LoadIndirect($address)"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacLoadIndirectInstruction) {
            return false
        }

        if (dst != other.dst) return false
        if (address != other.address) return false

        return true
    }

    override fun hashCode(): Int {
        var result = dst.hashCode()
        result = 31 * result + address.hashCode()
        return result
    }
}
