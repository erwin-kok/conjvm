package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.parser.SourceLocation
import org.erwinkok.conjvm.types.QualType
import org.erwinkok.conjvm.types.VariableSymbol

class VariableReference(
    location: SourceLocation,
    val name: String,
    val symbol: VariableSymbol,
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

        return name == other.name
    }

    override fun hashCode(): Int {
        return name.hashCode()
    }

    override fun toString(): String {
        return name
    }
}
