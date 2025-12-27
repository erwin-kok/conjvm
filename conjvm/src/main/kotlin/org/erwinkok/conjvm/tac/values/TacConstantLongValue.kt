package org.erwinkok.conjvm.tac.values

data class TacConstantLongValue(val value: Long) : TacValue {
    override fun toString(): String {
        return if (value < 10) {
            value.toString()
        } else {
            value.toHexString(format)
        }
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TacConstantLongValue) {
            return false
        }

        if (value != other.value) return false

        return true
    }

    override fun hashCode(): Int {
        return value.hashCode()
    }

    companion object {
        private val format = HexFormat {
            upperCase = false
            bytes {
                bytesPerLine = 2
                byteSeparator = " "
                bytePrefix = "0x"
                number.removeLeadingZeros = true
                number.prefix = "0x"
            }
        }
    }
}
