package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.AstNode
import org.erwinkok.conjvm.parser.SourceLocation
import org.erwinkok.conjvm.types.ExpressionType
import org.erwinkok.conjvm.types.QualType

sealed class Expression(
    location: SourceLocation,
    val type: QualType,
) : AstNode(location) {
    var expressionType: ExpressionType? = null
    var isLValue: Boolean = false

    abstract fun <R> accept(visitor: AstExpressionVisitor<R>): R

    abstract override fun equals(other: Any?): Boolean
    abstract override fun hashCode(): Int
}
