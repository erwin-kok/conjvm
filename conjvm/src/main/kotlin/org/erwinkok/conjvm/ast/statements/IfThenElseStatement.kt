package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.SourceLocation
import org.erwinkok.conjvm.ast.expressions.Expression

class IfThenElseStatement(location: SourceLocation, val test: Expression, val thenBlock: BlockStatement, val elseBlock: BlockStatement) : Statement(location) {
    override fun <R, C> accept(visitor: AstStatementVisitor<R, C>, ctx: C): R = visitor.visitIfThenElse(this, ctx)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is IfThenElseStatement) {
            return false
        }

        if (test != other.test) return false
        if (thenBlock != other.thenBlock) return false
        if (elseBlock != other.elseBlock) return false

        return true
    }

    override fun hashCode(): Int {
        var result = test.hashCode()
        result = 31 * result + thenBlock.hashCode()
        result = 31 * result + elseBlock.hashCode()
        return result
    }
}
