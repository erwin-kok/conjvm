package org.erwinkok.conjvm.tac.lvalues

data class FieldLValue(val base: TacLValue, val field: String) : TacLValue {
    override fun toString(): String {
        return "$base.$field"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is FieldLValue) {
            return false
        }

        if (base != other.base) return false
        if (field != other.field) return false

        return true
    }

    override fun hashCode(): Int {
        var result = base.hashCode()
        result = 31 * result + field.hashCode()
        return result
    }
}
