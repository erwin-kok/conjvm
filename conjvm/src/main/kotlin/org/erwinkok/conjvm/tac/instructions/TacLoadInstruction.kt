package org.erwinkok.conjvm.tac.instructions

import org.erwinkok.conjvm.tac.lvalues.TacIdentifier
import org.erwinkok.conjvm.tac.values.TacTemp

class TacLoadInstruction(val dst: TacTemp, val address: TacIdentifier) : TacInstruction {
    override fun toString(): String {
        return "$dst = LoadVar($address)"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacLoadInstruction) {
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
