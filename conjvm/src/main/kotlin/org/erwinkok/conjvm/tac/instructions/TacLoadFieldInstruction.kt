package org.erwinkok.conjvm.tac.instructions

import org.erwinkok.conjvm.tac.values.TacTemp
import org.erwinkok.conjvm.tac.values.TacValue

class TacLoadFieldInstruction(val dst: TacTemp, val base: TacValue, val field: String) : TacInstruction {
    override fun toString(): String {
        return "$dst = LoadField($base, $field)"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacLoadFieldInstruction) {
            return false
        }

        if (dst != other.dst) return false
        if (base != other.base) return false
        if (field != other.field) return false

        return true
    }

    override fun hashCode(): Int {
        var result = dst.hashCode()
        result = 31 * result + base.hashCode()
        result = 31 * result + field.hashCode()
        return result
    }
}
