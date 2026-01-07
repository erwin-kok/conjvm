package org.erwinkok.conjvm.ast.types

data class ExpressionType(val type: QualType, val isLValue: Boolean) {
    val isError: Boolean = this.type.isError

    fun toRValue(): ExpressionType {
        val decayedType = TypeSystem.decay(this.type)
        return ExpressionType(decayedType, false)
    }
}
