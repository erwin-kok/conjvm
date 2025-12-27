package org.erwinkok.conjvm.tac.lvalues

import org.erwinkok.conjvm.tac.values.TacValue

data class IndirectLValue(val ptr: TacValue) : TacLValue {
    override fun toString(): String {
        return "indirect_of($ptr)"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is IndirectLValue) {
            return false
        }

        if (ptr != other.ptr) return false

        return true
    }

    override fun hashCode(): Int {
        return ptr.hashCode()
    }
}
