package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.expressions.Expression
import org.erwinkok.conjvm.parser.SourceLocation

class IfThenElseStatement(
    location: SourceLocation,
    val condition: Expression,
    val thenBlock: BlockStatement,
    val elseBlock: BlockStatement,
) : Statement(location) {
    override fun <R> accept(visitor: AstStatementVisitor<R>): R = visitor.visitIfThenElse(this)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is IfThenElseStatement) {
            return false
        }
        if (condition != other.condition) return false
        if (thenBlock != other.thenBlock) return false
        if (elseBlock != other.elseBlock) return false
        return true
    }

    override fun hashCode(): Int {
        var result = condition.hashCode()
        result = 31 * result + thenBlock.hashCode()
        result = 31 * result + elseBlock.hashCode()
        return result
    }
}
