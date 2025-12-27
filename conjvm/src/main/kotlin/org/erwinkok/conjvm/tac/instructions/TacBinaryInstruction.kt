package org.erwinkok.conjvm.tac.instructions

import org.erwinkok.conjvm.ast.expressions.BinaryExpressionType
import org.erwinkok.conjvm.tac.values.TacTemp
import org.erwinkok.conjvm.tac.values.TacValue

class TacBinaryInstruction(val dst: TacTemp, val type: BinaryExpressionType, val leftValue: TacValue, val rightValue: TacValue) : TacInstruction {
    override fun toString(): String {
        return "$dst = $leftValue $type $rightValue"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacBinaryInstruction) {
            return false
        }

        if (dst != other.dst) return false
        if (type != other.type) return false
        if (leftValue != other.leftValue) return false
        if (rightValue != other.rightValue) return false

        return true
    }

    override fun hashCode(): Int {
        var result = dst.hashCode()
        result = 31 * result + type.hashCode()
        result = 31 * result + leftValue.hashCode()
        result = 31 * result + rightValue.hashCode()
        return result
    }
}
