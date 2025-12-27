package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.SourceLocation
import org.erwinkok.conjvm.ast.expressions.Expression

class WhileStatement(
    location: SourceLocation,
    val test: Expression,
    val statements: BlockStatement,
) : Statement(location) {
    override fun <R, C> accept(visitor: AstStatementVisitor<R, C>, ctx: C): R = visitor.visitWhile(this, ctx)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is WhileStatement) {
            return false
        }

        if (test != other.test) return false
        if (statements != other.statements) return false

        return true
    }

    override fun hashCode(): Int {
        var result = test.hashCode()
        result = 31 * result + statements.hashCode()
        return result
    }
}
