package org.erwinkok.conjvm.tac.instructions

import org.erwinkok.conjvm.tac.values.TacValue

class TacStoreFieldInstruction(val base: TacValue, val field: String, val value: TacValue) : TacInstruction {
    override fun toString(): String {
        return "StoreField($base, $field) = $value"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacStoreFieldInstruction) {
            return false
        }

        if (base != other.base) return false
        if (field != other.field) return false
        if (value != other.value) return false

        return true
    }

    override fun hashCode(): Int {
        var result = base.hashCode()
        result = 31 * result + field.hashCode()
        result = 31 * result + value.hashCode()
        return result
    }
}
