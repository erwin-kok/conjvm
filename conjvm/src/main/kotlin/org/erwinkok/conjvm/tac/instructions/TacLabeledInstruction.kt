package org.erwinkok.conjvm.tac.instructions

import org.erwinkok.conjvm.tac.TacLabel

class TacLabeledInstruction(val label: TacLabel) : TacInstruction {
    override fun toString(): String {
        return "$label:"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacLabeledInstruction) {
            return false
        }

        if (label != other.label) return false

        return true
    }

    override fun hashCode(): Int {
        return label.hashCode()
    }
}
