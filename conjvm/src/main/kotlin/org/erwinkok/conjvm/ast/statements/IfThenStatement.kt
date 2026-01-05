package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.expressions.Expression
import org.erwinkok.conjvm.parser.SourceLocation

class IfThenStatement(location: SourceLocation, val test: Expression, val thenBlock: BlockStatement) : Statement(location) {
    override fun <R> accept(visitor: AstStatementVisitor<R>): R = visitor.visitIfThen(this)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is IfThenStatement) {
            return false
        }

        if (test != other.test) return false
        if (thenBlock != other.thenBlock) return false

        return true
    }

    override fun hashCode(): Int {
        var result = test.hashCode()
        result = 31 * result + thenBlock.hashCode()
        return result
    }
}
