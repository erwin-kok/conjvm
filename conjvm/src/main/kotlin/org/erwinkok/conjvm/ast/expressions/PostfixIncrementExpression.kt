package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.parser.SourceLocation
import org.erwinkok.conjvm.types.QualType

class PostfixIncrementExpression(
    location: SourceLocation,
    val expression: Expression,
    type: QualType,
) : Expression(location, type) {
    override fun <R> accept(visitor: AstExpressionVisitor<R>): R = visitor.visitPostfixIncrement(this)

    override fun toString(): String {
        return "$expression++"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is PostfixIncrementExpression) {
            return false
        }
        if (expression != other.expression) return false
        if (type != other.type) return false
        return true
    }

    override fun hashCode(): Int {
        var result = expression.hashCode()
        result = 31 * result + type.hashCode()
        return result
    }
}
