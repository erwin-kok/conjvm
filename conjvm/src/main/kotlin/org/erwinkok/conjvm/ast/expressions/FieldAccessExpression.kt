package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.SourceLocation

class FieldAccessExpression(location: SourceLocation, val base: Expression, val field: String) : Expression(location) {
    override fun <R, C> accept(visitor: AstExpressionVisitor<R, C>, ctx: C): R = visitor.visitFieldAccess(this, ctx)

    override fun toString(): String {
        return "$base.$field"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is FieldAccessExpression) {
            return false
        }

        if (base != other.base) return false
        if (field != other.field) return false

        return true
    }

    override fun hashCode(): Int {
        var result = base.hashCode()
        result = 31 * result + field.hashCode()
        return result
    }
}
