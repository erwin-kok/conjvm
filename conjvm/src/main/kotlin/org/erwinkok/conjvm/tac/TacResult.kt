package org.erwinkok.conjvm.tac

import org.erwinkok.conjvm.tac.instructions.TacInstruction
import org.erwinkok.conjvm.tac.values.TacValue

data class TacResult(
    val statements: List<TacInstruction>,
    val tacValue: TacValue?,
)
