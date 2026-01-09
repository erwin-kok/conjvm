package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.expressions.Expression
import org.erwinkok.conjvm.parser.SourceLocation

class DoWhileStatement(
    location: SourceLocation,
    val condition: Expression,
    val statements: BlockStatement,
) : Statement(location) {
    override fun <R> accept(visitor: AstStatementVisitor<R>): R = visitor.visitDoWhile(this)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is DoWhileStatement) {
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
