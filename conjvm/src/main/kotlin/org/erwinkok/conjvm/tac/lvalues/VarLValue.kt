package org.erwinkok.conjvm.tac.lvalues

data class VarLValue(val variable: TacIdentifier) : TacLValue {
    override fun toString(): String {
        return variable.id
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is VarLValue) {
            return false
        }

        if (variable != other.variable) return false

        return true
    }

    override fun hashCode(): Int {
        return variable.hashCode()
    }
}
