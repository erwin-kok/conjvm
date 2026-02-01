package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.parser.SourceLocation
import org.erwinkok.conjvm.types.QualType

class StringLiteralExpression(
    location: SourceLocation,
    val value: String,
    type: QualType, // char[N] where N = length + 1
) : ConstantExpression(location, type) {
    override fun <R> accept(visitor: AstExpressionVisitor<R>): R = visitor.visitStringLiteral(this)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is StringLiteralExpression) {
            return false
        }

        if (value != other.value) return false

        return true
    }

    override fun hashCode(): Int {
        return value.hashCode()
    }

    override fun toString(): String {
        return value
    }
}
