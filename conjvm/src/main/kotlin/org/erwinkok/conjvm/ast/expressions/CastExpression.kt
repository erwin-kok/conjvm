package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.types.QualType
import org.erwinkok.conjvm.declarations.TypeName
import org.erwinkok.conjvm.parser.SourceLocation

class CastExpression(location: SourceLocation, val targetType: TypeName, val expression: Expression) : Expression(location) {
    var targetQualType: QualType? = null

    override fun <R> accept(visitor: AstExpressionVisitor<R>): R = visitor.visitCast(this)

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
