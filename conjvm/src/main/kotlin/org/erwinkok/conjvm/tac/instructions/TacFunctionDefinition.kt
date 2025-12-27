package org.erwinkok.conjvm.tac.instructions

class TacFunctionDefinition(val name: String, val instructions: List<TacInstruction>) : TacInstruction {
    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacFunctionDefinition) {
            return false
        }
        return name == other.name &&
            instructions == other.instructions
    }

    override fun hashCode(): Int {
        var result = name.hashCode()
        result = 31 * result + instructions.hashCode()
        return result
    }

    override fun toString(): String {
        return name
    }
}
