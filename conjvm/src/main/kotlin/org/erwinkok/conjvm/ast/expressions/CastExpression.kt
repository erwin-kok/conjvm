package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.SourceLocation
import org.erwinkok.conjvm.ast.VariableType

class CastExpression(location: SourceLocation, val type: VariableType, val expression: Expression) : Expression(location) {
    override fun <R, C> accept(visitor: AstExpressionVisitor<R, C>, ctx: C): R = visitor.visitCast(this, ctx)

    override fun toString(): String {
        return "($type)$expression"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is CastExpression) {
            return false
        }

        if (type != other.type) return false
        if (expression != other.expression) return false

        return true
    }

    override fun hashCode(): Int {
        var result = type.hashCode()
        result = 31 * result + expression.hashCode()
        return result
    }
}
