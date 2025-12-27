package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.SourceLocation

class BlockStatement(location: SourceLocation, val statements: List<Statement>) : Statement(location) {
    override fun <R, C> accept(visitor: AstStatementVisitor<R, C>, ctx: C): R = visitor.visitBlock(this, ctx)

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
