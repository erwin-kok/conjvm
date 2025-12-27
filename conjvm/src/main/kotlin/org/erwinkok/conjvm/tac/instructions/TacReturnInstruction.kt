package org.erwinkok.conjvm.tac.instructions

class TacReturnInstruction : TacInstruction {
    override fun toString(): String {
        return "return"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        return other is TacReturnInstruction
    }

    override fun hashCode(): Int {
        return javaClass.hashCode()
    }
}
