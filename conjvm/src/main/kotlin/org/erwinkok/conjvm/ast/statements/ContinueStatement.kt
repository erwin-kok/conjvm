package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.SourceLocation

class ContinueStatement(location: SourceLocation) : Statement(location) {
    override fun <R, C> accept(visitor: AstStatementVisitor<R, C>, ctx: C): R = visitor.visitContinue(this, ctx)

    override fun equals(other: Any?): Boolean {
        return other is ContinueStatement
    }

    override fun hashCode(): Int {
        return javaClass.hashCode()
    }
}
