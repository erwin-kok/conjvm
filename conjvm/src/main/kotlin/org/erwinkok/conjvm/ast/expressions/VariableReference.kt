package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.declarations.Entity
import org.erwinkok.conjvm.parser.SourceLocation
import org.erwinkok.conjvm.types.QualType

class VariableReference(
    location: SourceLocation,
    val name: String,
    val entity: Entity.Variable,
    type: QualType,
) : Expression(location, type) {
    override fun <R> accept(visitor: AstExpressionVisitor<R>): R = visitor.visitVariableReference(this)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is VariableReference) {
            return false
        }
        if (name != other.name) return false
        if (entity != other.entity) return false
        if (type != other.type) return false
        return true
    }

    override fun hashCode(): Int {
        var result = name.hashCode()
        result = 31 * result + entity.hashCode()
        result = 31 * result + type.hashCode()
        return result
    }

    override fun toString(): String {
        return name
    }
}
