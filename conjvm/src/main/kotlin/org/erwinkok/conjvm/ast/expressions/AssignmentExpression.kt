package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.parser.SourceLocation
import org.erwinkok.conjvm.types.QualType

class AssignmentExpression(
    location: SourceLocation,
    val operator: AssignmentOperator,
    val left: Expression,
    val right: Expression,
    type: QualType,
) : Expression(location, type) {
    override fun <R> accept(visitor: AstExpressionVisitor<R>): R = visitor.visitAssignment(this)

    override fun toString(): String {
        return "$left $operator $right"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is AssignmentExpression) {
            return false
        }
        if (operator != other.operator) return false
        if (left != other.left) return false
        if (right != other.right) return false
        if (type != other.type) return false
        return true
    }

    override fun hashCode(): Int {
        var result = operator.hashCode()
        result = 31 * result + left.hashCode()
        result = 31 * result + right.hashCode()
        result = 31 * result + type.hashCode()
        return result
    }
}
