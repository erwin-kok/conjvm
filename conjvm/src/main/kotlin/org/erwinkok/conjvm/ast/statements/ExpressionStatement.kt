package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.expressions.Expression
import org.erwinkok.conjvm.parser.SourceLocation

class ExpressionStatement(location: SourceLocation, val expression: Expression) : Statement(location) {
    override fun <R> accept(visitor: AstStatementVisitor<R>): R = visitor.visitExpression(this)

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
