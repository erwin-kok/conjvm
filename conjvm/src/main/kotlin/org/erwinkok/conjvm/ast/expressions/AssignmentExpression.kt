package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.parser.SourceLocation

class AssignmentExpression(
    location: SourceLocation,
    val type: AssignmentExpressionType,
    val leftExpression: Expression,
    val rightExpression: Expression,
) : Expression(location) {
    override fun <R> accept(visitor: AstExpressionVisitor<R>): R = visitor.visitAssignment(this)

    override fun toString(): String {
        return "$leftExpression $type $rightExpression"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is AssignmentExpression) {
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
