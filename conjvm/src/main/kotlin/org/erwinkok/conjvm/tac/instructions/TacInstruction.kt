package org.erwinkok.conjvm.tac.instructions

sealed interface TacInstruction {
    override fun equals(other: Any?): Boolean
    override fun hashCode(): Int
}
