package org.erwinkok.conjvm.tac.instructions

import org.erwinkok.conjvm.tac.values.TacTemp
import org.erwinkok.conjvm.tac.values.TacValue

class TacLoadArrayInstruction(val dst: TacTemp, val base: TacValue, val index: TacValue) : TacInstruction {
    override fun toString(): String {
        return "$dst = LoadArray($base, $index)"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacLoadArrayInstruction) {
            return false
        }

        if (dst != other.dst) return false
        if (base != other.base) return false
        if (index != other.index) return false

        return true
    }

    override fun hashCode(): Int {
        var result = dst.hashCode()
        result = 31 * result + base.hashCode()
        result = 31 * result + index.hashCode()
        return result
    }
}
