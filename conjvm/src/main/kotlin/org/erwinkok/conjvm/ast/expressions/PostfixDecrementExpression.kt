package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.SourceLocation

class PostfixDecrementExpression(location: SourceLocation, val expression: Expression) : Expression(location) {
    override fun <R> accept(visitor: AstExpressionVisitor<R>): R = visitor.visitPostfixDecrement(this)

    override fun toString(): String {
        return "$expression--"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is PostfixDecrementExpression) {
            return false
        }

        return expression == other.expression
    }

    override fun hashCode(): Int {
        return expression.hashCode()
    }
}
