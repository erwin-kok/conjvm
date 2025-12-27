package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.SourceLocation

class BinaryExpression(location: SourceLocation, val type: BinaryExpressionType, val leftExpression: Expression, val rightExpression: Expression) : Expression(location) {
    override fun <R, C> accept(visitor: AstExpressionVisitor<R, C>, ctx: C): R = visitor.visitBinary(this, ctx)

    override fun toString(): String {
        return "$leftExpression $type $rightExpression"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is BinaryExpression) {
            return false
        }

        if (type != other.type) return false
        if (leftExpression != other.leftExpression) return false
        if (rightExpression != other.rightExpression) return false

        return true
    }

    override fun hashCode(): Int {
        var result = type.hashCode()
        result = 31 * result + leftExpression.hashCode()
        result = 31 * result + rightExpression.hashCode()
        return result
    }
}
