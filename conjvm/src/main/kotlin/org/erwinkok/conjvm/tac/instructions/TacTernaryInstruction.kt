package org.erwinkok.conjvm.tac.instructions

import org.erwinkok.conjvm.tac.values.TacTemp
import org.erwinkok.conjvm.tac.values.TacValue

class TacTernaryInstruction(val dst: TacTemp, val testValue: TacValue, val thenValue: TacValue, val elseValue: TacValue) : TacInstruction {
    override fun toString(): String {
        return "$dst = $testValue ? $thenValue : $elseValue"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacTernaryInstruction) {
            return false
        }

        if (dst != other.dst) return false
        if (testValue != other.testValue) return false
        if (thenValue != other.thenValue) return false
        if (elseValue != other.elseValue) return false

        return true
    }

    override fun hashCode(): Int {
        var result = dst.hashCode()
        result = 31 * result + testValue.hashCode()
        result = 31 * result + thenValue.hashCode()
        result = 31 * result + elseValue.hashCode()
        return result
    }
}
