package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.parser.SourceLocation

class ConstantIntExpression(
    location: SourceLocation,
    val value: Int,
) : ConstantExpression(location) {
    override fun <R> accept(visitor: AstExpressionVisitor<R>): R = visitor.visitConstantInt(this)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is ConstantIntExpression) {
            return false
        }

        return value == other.value
    }

    override fun hashCode(): Int {
        return value
    }

    override fun toString(): String {
        return "$value"
    }
}
