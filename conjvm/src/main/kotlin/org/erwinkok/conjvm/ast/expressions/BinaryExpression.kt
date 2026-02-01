package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.parser.SourceLocation
import org.erwinkok.conjvm.types.QualType

class BinaryExpression(
    location: SourceLocation,
    val operator: BinaryOperator,
    val leftExpression: Expression,
    val rightExpression: Expression,
    type: QualType,
) : Expression(location, type) {
    override fun <R> accept(visitor: AstExpressionVisitor<R>): R = visitor.visitBinary(this)

    override fun toString(): String {
        return "$leftExpression $operator $rightExpression"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is BinaryExpression) {
            return false
        }

        if (operator != other.operator) return false
        if (leftExpression != other.leftExpression) return false
        if (rightExpression != other.rightExpression) return false

        return true
    }

    override fun hashCode(): Int {
        var result = operator.hashCode()
        result = 31 * result + leftExpression.hashCode()
        result = 31 * result + rightExpression.hashCode()
        return result
    }
}
