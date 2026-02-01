package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.parser.SourceLocation

class BlockStatement(
    location: SourceLocation,
    val statements: List<Statement>,
) : Statement(location) {
    override fun <R> accept(visitor: AstStatementVisitor<R>): R = visitor.visitBlock(this)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is BlockStatement) {
            return false
        }
        return statements == other.statements
    }

    override fun hashCode(): Int {
        return statements.hashCode()
    }
}
