package org.erwinkok.conjvm.tac

import org.erwinkok.conjvm.tac.values.TacTemp

class TacTempFactory {
    private var tempCounter = 0

    fun newTemp(): TacTemp {
        tempCounter++
        return TacTemp("$tempCounter")
    }

    fun clear() {
        tempCounter = 0
    }
}
