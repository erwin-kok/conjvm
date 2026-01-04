package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.SourceLocation

class LabeledStatement(location: SourceLocation, val id: String, val statement: Statement) : Statement(location) {
    override fun <R> accept(visitor: AstStatementVisitor<R>): R = visitor.visitLabeled(this)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is LabeledStatement) {
            return false
        }

        if (id != other.id) return false
        if (statement != other.statement) return false

        return true
    }

    override fun hashCode(): Int {
        var result = id.hashCode()
        result = 31 * result + statement.hashCode()
        return result
    }
}
