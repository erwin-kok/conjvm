package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.SourceLocation
import org.erwinkok.conjvm.ast.expressions.Expression

class ReturnStatement(location: SourceLocation, val value: Expression?) : Statement(location) {
    override fun <R, C> accept(visitor: AstStatementVisitor<R, C>, ctx: C): R = visitor.visitReturn(this, ctx)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is ReturnStatement) {
            return false
        }
        return value == other.value
    }

    override fun hashCode(): Int {
        return value?.hashCode() ?: 0
    }
}
