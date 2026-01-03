package org.erwinkok.conjvm.ast.types

import org.erwinkok.conjvm.ast.expressions.Expression
import java.util.IdentityHashMap

data class ExpressionType(val type: QualType, val isLValue: Boolean)

class ExpressionTypeSystem(private val visitor: TypeVisitor) {
    private val cache = IdentityHashMap<Expression, ExpressionType>()

    fun typeOf(expression: Expression): ExpressionType {
        return cache.getOrPut(expression) { visitor.visit(expression, TypeContext()) }
    }
}
