package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstNode
import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.parser.SourceLocation

sealed class Statement(location: SourceLocation) : AstNode(location) {
    abstract fun <R> accept(visitor: AstStatementVisitor<R>): R

    abstract override fun equals(other: Any?): Boolean
    abstract override fun hashCode(): Int
}
