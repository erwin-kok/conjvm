package org.erwinkok.conjvm.tac.instructions

import org.erwinkok.conjvm.tac.TacLabel

class TacGotoInstruction(val label: TacLabel) : TacInstruction {
    override fun toString(): String {
        return "goto $label"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacGotoInstruction) {
            return false
        }
        return label == other.label
    }

    override fun hashCode(): Int {
        return label.hashCode()
    }
}
