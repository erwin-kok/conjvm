package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.SourceLocation
import org.erwinkok.conjvm.ast.expressions.Expression

class ExpressionStatement(location: SourceLocation, val expression: Expression) : Statement(location) {
    override fun <R, C> accept(visitor: AstStatementVisitor<R, C>, ctx: C): R = visitor.visitExpression(this, ctx)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is ExpressionStatement) {
            return false
        }
        return expression == other.expression
    }

    override fun hashCode(): Int {
        return expression.hashCode()
    }

    override fun toString(): String {
        return "$expression;"
    }
}
