package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.SourceLocation

class ParenthesizedExpression(location: SourceLocation, val expression: Expression) : Expression(location) {
    override fun <R> accept(visitor: AstExpressionVisitor<R>): R = visitor.visitParenthesized(this)

    override fun toString(): String {
        return "($expression)"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is ParenthesizedExpression) {
            return false
        }

        return expression == other.expression
    }

    override fun hashCode(): Int {
        return expression.hashCode()
    }
}
