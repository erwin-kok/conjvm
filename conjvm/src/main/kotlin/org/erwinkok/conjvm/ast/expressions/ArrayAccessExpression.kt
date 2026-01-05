package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.parser.SourceLocation

class ArrayAccessExpression(location: SourceLocation, val base: Expression, val index: Expression) : Expression(location) {
    override fun <R> accept(visitor: AstExpressionVisitor<R>): R = visitor.visitArrayAccess(this)

    override fun toString(): String {
        return "$base[$index]"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is ArrayAccessExpression) {
            return false
        }

        if (base != other.base) return false
        if (index != other.index) return false

        return true
    }

    override fun hashCode(): Int {
        var result = base.hashCode()
        result = 31 * result + index.hashCode()
        return result
    }
}
