package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.SourceLocation

class AssignmentExpression(location: SourceLocation, val op: String, val leftExpression: Expression, val rightExpression: Expression) : Expression(location) {
    override fun <R, C> accept(visitor: AstExpressionVisitor<R, C>, ctx: C): R = visitor.visitAssignment(this, ctx)

    override fun toString(): String {
        return "$leftExpression $op $rightExpression"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is AssignmentExpression) {
            return false
        }

        if (op != other.op) return false
        if (leftExpression != other.leftExpression) return false
        if (rightExpression != other.rightExpression) return false

        return true
    }

    override fun hashCode(): Int {
        var result = op.hashCode()
        result = 31 * result + leftExpression.hashCode()
        result = 31 * result + rightExpression.hashCode()
        return result
    }
}
