package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.SourceLocation
import org.erwinkok.conjvm.ast.expressions.Expression

class WhileStatement(
    location: SourceLocation,
    val condition: Expression,
    val statements: BlockStatement,
) : Statement(location) {
    override fun <R> accept(visitor: AstStatementVisitor<R>): R = visitor.visitWhile(this)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is WhileStatement) {
            return false
        }

        if (condition != other.condition) return false
        if (statements != other.statements) return false

        return true
    }

    override fun hashCode(): Int {
        var result = condition.hashCode()
        result = 31 * result + statements.hashCode()
        return result
    }
}
