package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.parser.SourceLocation

class ContinueStatement(
    location: SourceLocation,
) : Statement(location) {
    override fun <R> accept(visitor: AstStatementVisitor<R>): R = visitor.visitContinue(this)

    override fun equals(other: Any?): Boolean {
        return other is ContinueStatement
    }

    override fun hashCode(): Int {
        return javaClass.hashCode()
    }
}
