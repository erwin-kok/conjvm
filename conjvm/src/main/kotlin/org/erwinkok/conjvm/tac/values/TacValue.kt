package org.erwinkok.conjvm.tac.values

sealed interface TacValue {
    override fun equals(other: Any?): Boolean
    override fun hashCode(): Int
}
