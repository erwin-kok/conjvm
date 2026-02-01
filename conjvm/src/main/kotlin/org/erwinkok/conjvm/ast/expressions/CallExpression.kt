package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.parser.SourceLocation

class CallExpression(
    location: SourceLocation,
    val function: Expression,
    val arguments: List<Expression>,
) : Expression(location) {
    override fun <R> accept(visitor: AstExpressionVisitor<R>): R = visitor.visitCall(this)

    override fun toString(): String {
        return "$function(${arguments.joinToString(", ")})"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is CallExpression) {
            return false
        }

        if (function != other.function) return false
        if (arguments != other.arguments) return false

        return true
    }

    override fun hashCode(): Int {
        var result = function.hashCode()
        result = 31 * result + arguments.hashCode()
        return result
    }
}
