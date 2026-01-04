package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.SourceLocation

class ConstantLongExpression(location: SourceLocation, val value: Long) : ConstantExpression(location) {
    override fun <R> accept(visitor: AstExpressionVisitor<R>): R = visitor.visitConstantLong(this)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is ConstantLongExpression) {
            return false
        }

        if (value != other.value) return false

        return true
    }

    override fun hashCode(): Int {
        return value.hashCode()
    }

    override fun toString(): String {
        return "$value"
    }
}
