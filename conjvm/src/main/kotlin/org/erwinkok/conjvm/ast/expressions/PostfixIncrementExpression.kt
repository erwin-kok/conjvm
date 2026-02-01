package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.parser.SourceLocation

class PostfixIncrementExpression(
    location: SourceLocation,
    val expression: Expression,
) : Expression(location) {
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

        return expression == other.expression
    }

    override fun hashCode(): Int {
        return expression.hashCode()
    }
}
