package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.SourceLocation

class Identifier(location: SourceLocation, val name: String) : Expression(location) {
    override fun <R, C> accept(visitor: AstExpressionVisitor<R, C>, ctx: C): R = visitor.visitIdentifier(this, ctx)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is Identifier) {
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
