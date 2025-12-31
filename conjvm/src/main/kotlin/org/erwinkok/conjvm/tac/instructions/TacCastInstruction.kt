package org.erwinkok.conjvm.tac.instructions

import org.erwinkok.conjvm.ast.types.VariableType
import org.erwinkok.conjvm.tac.values.TacTemp
import org.erwinkok.conjvm.tac.values.TacValue

class TacCastInstruction(val dst: TacTemp, val type: VariableType, val value: TacValue) : TacInstruction {
    override fun toString(): String {
        return "$dst = ($type)$value"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacCastInstruction) {
            return false
        }

        if (dst != other.dst) return false
        if (type != other.type) return false
        if (value != other.value) return false

        return true
    }

    override fun hashCode(): Int {
        var result = dst.hashCode()
        result = 31 * result + type.hashCode()
        result = 31 * result + value.hashCode()
        return result
    }
}
