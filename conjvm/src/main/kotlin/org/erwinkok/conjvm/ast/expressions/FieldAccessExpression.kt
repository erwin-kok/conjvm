package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.parser.SourceLocation
import org.erwinkok.conjvm.types.QualType

class FieldAccessExpression(
    location: SourceLocation,
    val struct: Expression,
    val memberName: String,
    type: QualType,
) : Expression(location, type) {
    override fun <R> accept(visitor: AstExpressionVisitor<R>): R = visitor.visitFieldAccess(this)

    override fun toString(): String {
        return "$struct.$memberName"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is FieldAccessExpression) {
            return false
        }
        if (struct != other.struct) return false
        if (memberName != other.memberName) return false
        if (type != other.type) return false
        return true
    }

    override fun hashCode(): Int {
        var result = struct.hashCode()
        result = 31 * result + memberName.hashCode()
        result = 31 * result + type.hashCode()
        return result
    }
}
