package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.parser.SourceLocation
import org.erwinkok.conjvm.types.QualType

class UnaryExpression(
    location: SourceLocation,
    val operator: UnaryOperator,
    val operand: Expression,
    type: QualType,
) : Expression(location, type) {
    override fun <R> accept(visitor: AstExpressionVisitor<R>): R = visitor.visitUnary(this)

    override fun toString(): String {
        return "$operator$operand"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is UnaryExpression) {
            return false
        }

        if (operator != other.operator) return false
        if (operand != other.operand) return false

        return true
    }

    override fun hashCode(): Int {
        var result = operator.hashCode()
        result = 31 * result + operand.hashCode()
        return result
    }
}
