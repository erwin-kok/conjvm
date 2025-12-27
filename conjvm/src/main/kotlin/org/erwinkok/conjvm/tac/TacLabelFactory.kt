package org.erwinkok.conjvm.tac

data class TacLabel(val id: String) {
    override fun toString(): String {
        return "L$id"
    }
}

class TacLabelFactory {
    private var labelCounter = 0

    fun new(): TacLabel {
        labelCounter++
        return TacLabel("$labelCounter")
    }

    fun clear() {
        labelCounter = 0
    }
}
