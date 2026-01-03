package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.SourceLocation
import org.erwinkok.conjvm.ast.types.TypeName

class CastExpression(location: SourceLocation, val targetType: TypeName, val expression: Expression) : Expression(location) {
    override fun <R, C> accept(visitor: AstExpressionVisitor<R, C>, ctx: C): R = visitor.visitCast(this, ctx)

    override fun toString(): String {
        return "($targetType)$expression"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is CastExpression) {
            return false
        }

        if (targetType != other.targetType) return false
        if (expression != other.expression) return false

        return true
    }

    override fun hashCode(): Int {
        var result = targetType.hashCode()
        result = 31 * result + expression.hashCode()
        return result
    }
}
