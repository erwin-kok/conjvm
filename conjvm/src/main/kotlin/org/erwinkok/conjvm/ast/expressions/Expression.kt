package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.AstNode
import org.erwinkok.conjvm.ast.SourceLocation

sealed class Expression(location: SourceLocation) : AstNode(location) {
    abstract fun <R, C> accept(visitor: AstExpressionVisitor<R, C>, ctx: C): R

    abstract override fun equals(other: Any?): Boolean
    abstract override fun hashCode(): Int
}
