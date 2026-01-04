package org.erwinkok.conjvm.ast.types

data class ExpressionType(val type: QualType, val isLValue: Boolean) {
    fun isError(): Boolean = this.type.isError()

    fun assertNotError(): ExpressionType {
        require(!isError()) { "attempted to analyze ErrorType expression" }
        return this
    }
}
