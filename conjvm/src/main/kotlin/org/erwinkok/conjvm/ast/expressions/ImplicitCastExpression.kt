package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.parser.SourceLocation
import org.erwinkok.conjvm.types.QualType

enum class CastKind {
    NO_OP, // Type is the same
    LVALUE_TO_RVALUE, // Load from memory
    ARRAY_TO_POINTER, // Array decay
    FUNCTION_TO_POINTER, // Function decay
    INTEGRAL_CAST, // int -> long, etc.
    INTEGRAL_TO_FLOATING, // int -> float
    FLOATING_TO_INTEGRAL, // float -> int
    FLOATING_CAST, // float -> double
    POINTER_TO_INTEGRAL, // ptr -> int
    INTEGRAL_TO_POINTER, // int -> ptr
    POINTER_TO_POINTER, // void* -> char*
}

class ImplicitCastExpression(
    location: SourceLocation,
    val castKind: CastKind,
    val expression: Expression,
    type: QualType,
) : Expression(location, type) {
    override fun <R> accept(visitor: AstExpressionVisitor<R>): R = visitor.visitImplicitCast(this)

    override fun toString(): String {
        return "implicit_cast($castKind, $expression)"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is ImplicitCastExpression) {
            return false
        }

        if (castKind != other.castKind) return false
        if (expression != other.expression) return false

        return true
    }

    override fun hashCode(): Int {
        var result = castKind.hashCode()
        result = 31 * result + expression.hashCode()
        return result
    }
}
