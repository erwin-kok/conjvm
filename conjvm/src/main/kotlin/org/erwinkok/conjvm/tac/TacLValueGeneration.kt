package org.erwinkok.conjvm.tac

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.expressions.ArrayAccessExpression
import org.erwinkok.conjvm.ast.expressions.AssignmentExpression
import org.erwinkok.conjvm.ast.expressions.BinaryExpression
import org.erwinkok.conjvm.ast.expressions.CallExpression
import org.erwinkok.conjvm.ast.expressions.CastExpression
import org.erwinkok.conjvm.ast.expressions.CharacterLiteralExpression
import org.erwinkok.conjvm.ast.expressions.Expression
import org.erwinkok.conjvm.ast.expressions.FieldAccessExpression
import org.erwinkok.conjvm.ast.expressions.FloatLiteralExpression
import org.erwinkok.conjvm.ast.expressions.IntegerLiteralExpression
import org.erwinkok.conjvm.ast.expressions.ParenthesizedExpression
import org.erwinkok.conjvm.ast.expressions.PostfixDecrementExpression
import org.erwinkok.conjvm.ast.expressions.PostfixIncrementExpression
import org.erwinkok.conjvm.ast.expressions.StringLiteralExpression
import org.erwinkok.conjvm.ast.expressions.TernaryExpression
import org.erwinkok.conjvm.ast.expressions.UnaryExpression
import org.erwinkok.conjvm.ast.expressions.UnaryType
import org.erwinkok.conjvm.ast.expressions.VariableReference
import org.erwinkok.conjvm.tac.instructions.TacInstruction
import org.erwinkok.conjvm.tac.lvalues.ArrayLValue
import org.erwinkok.conjvm.tac.lvalues.FieldLValue
import org.erwinkok.conjvm.tac.lvalues.IndirectLValue
import org.erwinkok.conjvm.tac.lvalues.TacIdentifier
import org.erwinkok.conjvm.tac.lvalues.TacLValue
import org.erwinkok.conjvm.tac.lvalues.VarLValue

data class TacAddressResult(
    val statements: List<TacInstruction>,
    val tacValue: TacLValue,
)

class TacLValueGeneration(private val rValueVisitor: TacRValueGeneration) : AstExpressionVisitor<TacAddressResult> {
    fun translate(node: Expression): TacAddressResult = node.accept(this)

    override fun visitArrayAccess(expression: ArrayAccessExpression): TacAddressResult {
        val (tsb, teb) = when (expression.base) {
            is VariableReference,
            is FieldAccessExpression,
            is ArrayAccessExpression,
            is UnaryExpression,
            -> {
                // base already lvalue
                translate(expression.base)
            }

            else -> {
                // Complex expression: calculate pointer and wrap it in IndirectLValue
                val (rts, rte) = rValueVisitor.translate(expression.base)
                requireNotNull(rte)
                TacAddressResult(rts, IndirectLValue(rte))
            }
        }
        val (ts, te) = rValueVisitor.translate(expression.index)
        requireNotNull(te)
        return TacAddressResult(tsb + ts, ArrayLValue(teb, te))
    }

    override fun visitIntegerLiteral(expression: IntegerLiteralExpression): TacAddressResult {
        error("expression is not an lvalue: $expression")
    }

    override fun visitFloatLiteral(expression: FloatLiteralExpression): TacAddressResult {
        error("expression is not an lvalue: $expression")
    }

    override fun visitStringLiteral(expression: StringLiteralExpression): TacAddressResult {
        error("expression is not an lvalue: $expression")
    }

    override fun visitCharacterLiteral(expression: CharacterLiteralExpression): TacAddressResult {
        error("expression is not an lvalue: $expression")
    }

    override fun visitFieldAccess(expression: FieldAccessExpression): TacAddressResult {
        val (ts, te) = translate(expression.base)
        requireNotNull(te)
        return TacAddressResult(ts, FieldLValue(te, expression.field))
    }

    override fun visitParenthesized(expression: ParenthesizedExpression): TacAddressResult {
        return translate(expression.expression)
    }

    override fun visitPostfixDecrement(expression: PostfixDecrementExpression): TacAddressResult {
        error("expression is not an lvalue: $expression")
    }

    override fun visitPostfixIncrement(expression: PostfixIncrementExpression): TacAddressResult {
        error("expression is not an lvalue: $expression")
    }

    override fun visitAssignment(expression: AssignmentExpression): TacAddressResult {
        error("expression is not an lvalue: $expression")
    }

    override fun visitBinary(expression: BinaryExpression): TacAddressResult {
        error("expression is not an lvalue: $expression")
    }

    override fun visitCall(expression: CallExpression): TacAddressResult {
        error("expression is not an lvalue: $expression")
    }

    override fun visitCast(expression: CastExpression): TacAddressResult {
        error("expression is not an lvalue: $expression")
    }

    override fun visitTernary(expression: TernaryExpression): TacAddressResult {
        error("expression is not an lvalue: $expression")
    }

    override fun visitUnary(expression: UnaryExpression): TacAddressResult {
        return if (expression.type == UnaryType.Indirection) {
            val (ts, te) = rValueVisitor.translate(expression.operand)
            requireNotNull(te)
            TacAddressResult(ts, IndirectLValue(te))
        } else {
            error("expression is not an lvalue: $expression")
        }
    }

    override fun visitVariableReference(variableReference: VariableReference): TacAddressResult {
        return TacAddressResult(emptyList(), VarLValue(TacIdentifier(variableReference.name)))
    }
}
