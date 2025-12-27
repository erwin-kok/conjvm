package org.erwinkok.conjvm.tac.lvalues

sealed interface TacLValue {
    override fun equals(other: Any?): Boolean
    override fun hashCode(): Int
}
