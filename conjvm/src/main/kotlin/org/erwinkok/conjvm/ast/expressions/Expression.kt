package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.AstNode
import org.erwinkok.conjvm.ast.types.ExpressionType
import org.erwinkok.conjvm.parser.SourceLocation

sealed class Expression(location: SourceLocation) : AstNode(location) {
    var expressionType: ExpressionType? = null

    abstract fun <R> accept(visitor: AstExpressionVisitor<R>): R

    abstract override fun equals(other: Any?): Boolean
    abstract override fun hashCode(): Int
}
