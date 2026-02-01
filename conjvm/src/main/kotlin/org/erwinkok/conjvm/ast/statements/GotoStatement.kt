package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.parser.SourceLocation

class GotoStatement(
    location: SourceLocation,
    val label: String,
) : Statement(location) {
    override fun <R> accept(visitor: AstStatementVisitor<R>): R = visitor.visitGoto(this)

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
