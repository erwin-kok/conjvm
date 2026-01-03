package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.SourceLocation

class UnaryExpression(location: SourceLocation, val type: UnaryType, val operand: Expression) : Expression(location) {
    override fun <R, C> accept(visitor: AstExpressionVisitor<R, C>, ctx: C): R = visitor.visitUnary(this, ctx)

    override fun toString(): String {
        return "$type$operand"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is UnaryExpression) {
            return false
        }

        if (type != other.type) return false
        if (operand != other.operand) return false

        return true
    }

    override fun hashCode(): Int {
        var result = type.hashCode()
        result = 31 * result + operand.hashCode()
        return result
    }
}
