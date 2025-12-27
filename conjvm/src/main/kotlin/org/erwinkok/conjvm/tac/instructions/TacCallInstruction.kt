package org.erwinkok.conjvm.tac.instructions

import org.erwinkok.conjvm.tac.values.TacTemp
import org.erwinkok.conjvm.tac.values.TacValue

class TacCallInstruction(val dst: TacTemp, val name: String, val arguments: List<TacValue>) : TacInstruction {
    override fun toString(): String {
        return "$dst = $name(${arguments.joinToString(", ")})"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacCallInstruction) {
            return false
        }

        if (dst != other.dst) return false
        if (name != other.name) return false
        if (arguments != other.arguments) return false

        return true
    }

    override fun hashCode(): Int {
        var result = dst.hashCode()
        result = 31 * result + name.hashCode()
        result = 31 * result + arguments.hashCode()
        return result
    }
}
