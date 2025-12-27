package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.SourceLocation

class GotoStatement(location: SourceLocation, val label: String) : Statement(location) {
    override fun <R, C> accept(visitor: AstStatementVisitor<R, C>, ctx: C): R = visitor.visitGoto(this, ctx)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is GotoStatement) {
            return false
        }
        return label == other.label
    }

    override fun hashCode(): Int {
        return label.hashCode()
    }
}
