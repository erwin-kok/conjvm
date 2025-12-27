package org.erwinkok.conjvm.tac.instructions

import org.erwinkok.conjvm.tac.TacLabel
import org.erwinkok.conjvm.tac.values.TacValue

class TacIfGotoInstruction(val value: TacValue, val label: TacLabel) : TacInstruction {
    override fun toString(): String {
        return "if ($value) goto $label"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacIfGotoInstruction) {
            return false
        }
        if (value != other.value) return false
        if (label != other.label) return false

        return true
    }

    override fun hashCode(): Int {
        return label.hashCode()
    }
}
