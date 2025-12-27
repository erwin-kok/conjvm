package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.SourceLocation

class ArrayAccessExpression(location: SourceLocation, val base: Expression, val expression: Expression) : Expression(location) {
    override fun <R, C> accept(visitor: AstExpressionVisitor<R, C>, ctx: C): R = visitor.visitArrayAccess(this, ctx)

    override fun toString(): String {
        return "$base[$expression]"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is ArrayAccessExpression) {
            return false
        }

        if (base != other.base) return false
        if (expression != other.expression) return false

        return true
    }

    override fun hashCode(): Int {
        var result = base.hashCode()
        result = 31 * result + expression.hashCode()
        return result
    }
}
