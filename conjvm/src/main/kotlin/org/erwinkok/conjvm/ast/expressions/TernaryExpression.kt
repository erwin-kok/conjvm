package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.SourceLocation

class TernaryExpression(location: SourceLocation, val testExpression: Expression, val thenExpression: Expression, val elseExpression: Expression) : Expression(location) {
    override fun <R, C> accept(visitor: AstExpressionVisitor<R, C>, ctx: C): R = visitor.visitTernary(this, ctx)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is TernaryExpression) {
            return false
        }

        if (testExpression != other.testExpression) return false
        if (thenExpression != other.thenExpression) return false
        if (elseExpression != other.elseExpression) return false

        return true
    }

    override fun hashCode(): Int {
        var result = testExpression.hashCode()
        result = 31 * result + thenExpression.hashCode()
        result = 31 * result + elseExpression.hashCode()
        return result
    }
}
