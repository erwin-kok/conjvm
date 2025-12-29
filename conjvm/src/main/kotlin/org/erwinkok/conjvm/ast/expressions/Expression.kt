package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.AstNode
import org.erwinkok.conjvm.ast.SourceLocation
import org.erwinkok.conjvm.ast.Type

sealed class Expression(location: SourceLocation) : AstNode(location) {
    var expressionType: Type? = null

    abstract fun <R, C> accept(visitor: AstExpressionVisitor<R, C>, ctx: C): R

    abstract override fun equals(other: Any?): Boolean
    abstract override fun hashCode(): Int
}
