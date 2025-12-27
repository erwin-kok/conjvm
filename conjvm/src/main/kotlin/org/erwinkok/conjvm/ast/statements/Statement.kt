package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstNode
import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.SourceLocation

abstract class Statement(location: SourceLocation) : AstNode(location) {
    abstract fun <R, C> accept(visitor: AstStatementVisitor<R, C>, ctx: C): R

    abstract override fun equals(other: Any?): Boolean
    abstract override fun hashCode(): Int
}
