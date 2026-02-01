package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.parser.SourceLocation
import org.erwinkok.conjvm.types.QualType

class ConditionalExpression(
    location: SourceLocation,
    val condition: Expression,
    val thenExpression: Expression,
    val elseExpression: Expression,
    type: QualType,
) : Expression(location, type) {
    override fun <R> accept(visitor: AstExpressionVisitor<R>): R = visitor.visitConditional(this)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is ConditionalExpression) {
            return false
        }

        if (condition != other.condition) return false
        if (thenExpression != other.thenExpression) return false
        if (elseExpression != other.elseExpression) return false

        return true
    }

    override fun hashCode(): Int {
        var result = condition.hashCode()
        result = 31 * result + thenExpression.hashCode()
        result = 31 * result + elseExpression.hashCode()
        return result
    }
}
