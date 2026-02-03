package org.erwinkok.conjvm.tac

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.expressions.ArrayAccessExpression
import org.erwinkok.conjvm.ast.expressions.AssignmentExpression
import org.erwinkok.conjvm.ast.expressions.AssignmentOperator
import org.erwinkok.conjvm.ast.expressions.BinaryExpression
import org.erwinkok.conjvm.ast.expressions.BinaryOperator
import org.erwinkok.conjvm.ast.expressions.CallExpression
import org.erwinkok.conjvm.ast.expressions.CastExpression
import org.erwinkok.conjvm.ast.expressions.CharacterLiteralExpression
import org.erwinkok.conjvm.ast.expressions.ConditionalExpression
import org.erwinkok.conjvm.ast.expressions.Expression
import org.erwinkok.conjvm.ast.expressions.FieldAccessExpression
import org.erwinkok.conjvm.ast.expressions.FloatLiteralExpression
import org.erwinkok.conjvm.ast.expressions.IntegerLiteralExpression
import org.erwinkok.conjvm.ast.expressions.ParenthesizedExpression
import org.erwinkok.conjvm.ast.expressions.PostfixDecrementExpression
import org.erwinkok.conjvm.ast.expressions.PostfixIncrementExpression
import org.erwinkok.conjvm.ast.expressions.StringLiteralExpression
import org.erwinkok.conjvm.ast.expressions.UnaryExpression
import org.erwinkok.conjvm.ast.expressions.UnaryOperator
import org.erwinkok.conjvm.ast.expressions.VariableReference
import org.erwinkok.conjvm.tac.instructions.TacAddressOfInstruction
import org.erwinkok.conjvm.tac.instructions.TacBinaryInstruction
import org.erwinkok.conjvm.tac.instructions.TacCallInstruction
import org.erwinkok.conjvm.tac.instructions.TacCastInstruction
import org.erwinkok.conjvm.tac.instructions.TacInstruction
import org.erwinkok.conjvm.tac.instructions.TacLoadArrayInstruction
import org.erwinkok.conjvm.tac.instructions.TacLoadFieldInstruction
import org.erwinkok.conjvm.tac.instructions.TacLoadIndirectInstruction
import org.erwinkok.conjvm.tac.instructions.TacLoadInstruction
import org.erwinkok.conjvm.tac.instructions.TacStoreArrayInstruction
import org.erwinkok.conjvm.tac.instructions.TacStoreFieldInstruction
import org.erwinkok.conjvm.tac.instructions.TacStoreIndirectInstruction
import org.erwinkok.conjvm.tac.instructions.TacStoreInstruction
import org.erwinkok.conjvm.tac.instructions.TacTernaryInstruction
import org.erwinkok.conjvm.tac.lvalues.ArrayLValue
import org.erwinkok.conjvm.tac.lvalues.FieldLValue
import org.erwinkok.conjvm.tac.lvalues.IndirectLValue
import org.erwinkok.conjvm.tac.lvalues.TacLValue
import org.erwinkok.conjvm.tac.lvalues.VarLValue
import org.erwinkok.conjvm.tac.values.TacConstantCharacterValue
import org.erwinkok.conjvm.tac.values.TacConstantFloatValue
import org.erwinkok.conjvm.tac.values.TacConstantLongValue
import org.erwinkok.conjvm.tac.values.TacConstantStringValue
import org.erwinkok.conjvm.tac.values.TacValue

class TacRValueGeneration(
    private val tempFactory: TacTempFactory,
) : AstExpressionVisitor<TacResult> {
    private val lValueVisitor = TacLValueGeneration(this)

    fun translate(node: Expression): TacResult = node.accept(this)

    override fun visitArrayAccess(expression: ArrayAccessExpression): TacResult {
        val (ts, te) = lValueVisitor.translate(expression)
        requireNotNull(te)
        val (tsl, tel) = generateLoadInstruction(te)
        return TacResult(ts + tsl, tel)
    }

    override fun visitIntegerLiteral(expression: IntegerLiteralExpression): TacResult {
        return TacResult(emptyList(), TacConstantLongValue(expression.value))
    }

    override fun visitFloatLiteral(expression: FloatLiteralExpression): TacResult {
        return TacResult(emptyList(), TacConstantFloatValue(expression.value))
    }

    override fun visitStringLiteral(expression: StringLiteralExpression): TacResult {
        return TacResult(emptyList(), TacConstantStringValue(expression.value))
    }

    override fun visitCharacterLiteral(expression: CharacterLiteralExpression): TacResult {
        return TacResult(emptyList(), TacConstantCharacterValue(expression.value))
    }

    override fun visitFieldAccess(expression: FieldAccessExpression): TacResult {
        val (ts, te) = lValueVisitor.translate(expression)
        requireNotNull(te)
        val (tsl, tel) = generateLoadInstruction(te)
        return TacResult(ts + tsl, tel)
    }

    override fun visitVariableReference(expression: VariableReference): TacResult {
        val (ts, te) = lValueVisitor.translate(expression)
        requireNotNull(te)
        val (tsl, tel) = generateLoadInstruction(te)
        return TacResult(ts + tsl, tel)
    }

    override fun visitParenthesized(expression: ParenthesizedExpression): TacResult {
        val (ts, te) = translate(expression.expression)
        requireNotNull(te)
        return TacResult(ts, te)
    }

    override fun visitPostfixDecrement(expression: PostfixDecrementExpression): TacResult {
        val (addrInstrs, addr) = lValueVisitor.translate(expression.expression)
        val instructions = mutableListOf<TacInstruction>()
        instructions.addAll(addrInstrs)
        val (lts, lte) = generateLoadInstruction(addr)
        requireNotNull(lte)
        instructions.addAll(lts)
        val newTemp = tempFactory.newTemp()
        instructions.add(
            TacBinaryInstruction(
                newTemp,
                BinaryOperator.Subtract,
                lte,
                TacConstantLongValue(1),
            ),
        )
        val (sts, _) = generateStoreInstruction(addr, newTemp)
        instructions.addAll(sts)
        return TacResult(instructions, lte)
    }

    override fun visitPostfixIncrement(expression: PostfixIncrementExpression): TacResult {
        val (addrInstrs, addr) = lValueVisitor.translate(expression.expression)
        val instructions = mutableListOf<TacInstruction>()
        instructions.addAll(addrInstrs)
        val (lts, lte) = generateLoadInstruction(addr)
        requireNotNull(lte)
        instructions.addAll(lts)
        val newTemp = tempFactory.newTemp()
        instructions.add(
            TacBinaryInstruction(
                newTemp,
                BinaryOperator.Add,
                lte,
                TacConstantLongValue(1),
            ),
        )
        val (sts, _) = generateStoreInstruction(addr, newTemp)
        instructions.addAll(sts)
        return TacResult(instructions, lte)
    }

    override fun visitAssignment(expression: AssignmentExpression): TacResult {
        val (lts, lte) = lValueVisitor.translate(expression.left)
        val (rts, rte) = translate(expression.right)
        requireNotNull(lte)
        requireNotNull(rte)
        require(expression.operator == AssignmentOperator.Assign)
        val (tsl, tel) = generateStoreInstruction(lte, rte)
        return TacResult(lts + rts + tsl, tel)
    }

    override fun visitBinary(expression: BinaryExpression): TacResult {
        val allArguments = mutableListOf<TacInstruction>()
        val lte = translate(expression.leftExpression)
        val rte = translate(expression.rightExpression)
        requireNotNull(lte.tacValue)
        requireNotNull(rte.tacValue)
        allArguments.addAll(lte.statements)
        allArguments.addAll(rte.statements)
        val temp = tempFactory.newTemp()
        allArguments.add(TacBinaryInstruction(temp, expression.operator, lte.tacValue, rte.tacValue))
        return TacResult(allArguments, temp)
    }

    override fun visitCall(expression: CallExpression): TacResult {
        val allArguments = mutableListOf<TacInstruction>()
        val args = expression.arguments.map {
            val (ts, te) = translate(it)
            requireNotNull(te)
            allArguments.addAll(ts)
            te
        }
        val temp = tempFactory.newTemp()
        if (expression.function is VariableReference) {
            allArguments.add(TacCallInstruction(temp, TacConstantStringValue(expression.function.name), args))
        } else {
            val (ts, te) = translate(expression.function)
            requireNotNull(te)
            allArguments.addAll(ts)
            allArguments.add(TacCallInstruction(temp, te, args))
        }
        return TacResult(allArguments, temp)
    }

    override fun visitCast(expression: CastExpression): TacResult {
        val allArguments = mutableListOf<TacInstruction>()
        val testTr = translate(expression.expression)
        requireNotNull(testTr.tacValue)
        allArguments.addAll(testTr.statements)
        val temp = tempFactory.newTemp()
        val targetQualType = expression.targetQualType
        requireNotNull(targetQualType)
        allArguments.add(TacCastInstruction(temp, targetQualType, testTr.tacValue))
        return TacResult(allArguments, temp)
    }

    override fun visitConditional(expression: ConditionalExpression): TacResult {
        val allArguments = mutableListOf<TacInstruction>()
        val testTr = translate(expression.condition)
        val thenTr = translate(expression.thenExpression)
        val elseTr = translate(expression.elseExpression)
        requireNotNull(testTr.tacValue)
        requireNotNull(thenTr.tacValue)
        requireNotNull(elseTr.tacValue)
        allArguments.addAll(testTr.statements)
        allArguments.addAll(thenTr.statements)
        allArguments.addAll(elseTr.statements)
        val temp = tempFactory.newTemp()
        allArguments.add(TacTernaryInstruction(temp, testTr.tacValue, thenTr.tacValue, elseTr.tacValue))
        return TacResult(allArguments, temp)
    }

    override fun visitUnary(expression: UnaryExpression): TacResult {
        return when (expression.operator) {
            UnaryOperator.AddressOf -> translateUnaryAddressOf(expression)
            UnaryOperator.Dereference -> translateUnaryIndirection(expression)
            UnaryOperator.Plus -> translateUnaryPlus(expression)
            UnaryOperator.Minus -> translateUnaryMinus(expression)
            UnaryOperator.BitwiseNot -> translateUnaryBitwiseNot(expression)
            UnaryOperator.LogicalNot -> translateUnaryLogicalNot(expression)
            UnaryOperator.PlusPlus -> translateUnaryIncrement(expression)
            UnaryOperator.MinusMinus -> translateUnaryDecrement(expression)
        }
    }

    private fun translateUnaryAddressOf(expression: UnaryExpression): TacResult {
        val (ts, te) = lValueVisitor.translate(expression.operand)
        requireNotNull(te)
        val temp = tempFactory.newTemp()
        return TacResult(ts + TacAddressOfInstruction(temp, te), temp)
    }

    private fun translateUnaryIndirection(expression: UnaryExpression): TacResult {
        val (ts, te) = lValueVisitor.translate(expression)
        requireNotNull(te)
        val (tsl, tel) = generateLoadInstruction(te)
        return TacResult(ts + tsl, tel)
    }

    private fun translateUnaryPlus(expression: UnaryExpression): TacResult {
        val (ts, te) = translate(expression.operand)
        requireNotNull(te)
        return TacResult(ts, te)
    }

    private fun translateUnaryMinus(expression: UnaryExpression): TacResult {
        val (ts, te) = translate(expression.operand)
        requireNotNull(te)
        val allArguments = mutableListOf<TacInstruction>()
        allArguments.addAll(ts)
        val temp = tempFactory.newTemp()
        allArguments.add(TacBinaryInstruction(temp, BinaryOperator.Subtract, TacConstantLongValue(0), te))
        return TacResult(allArguments, temp)
    }

    private fun translateUnaryBitwiseNot(expression: UnaryExpression): TacResult {
        val (ts, te) = translate(expression.operand)
        requireNotNull(te)
        val allArguments = mutableListOf<TacInstruction>()
        allArguments.addAll(ts)
        val temp = tempFactory.newTemp()
        allArguments.add(TacBinaryInstruction(temp, BinaryOperator.ExclusiveOr, te, TacConstantLongValue(-1)))
        return TacResult(allArguments, temp)
    }

    private fun translateUnaryLogicalNot(expression: UnaryExpression): TacResult {
        val (ts, te) = translate(expression.operand)
        requireNotNull(te)
        val allArguments = mutableListOf<TacInstruction>()
        allArguments.addAll(ts)
        val temp = tempFactory.newTemp()
        allArguments.add(TacBinaryInstruction(temp, BinaryOperator.Equals, te, TacConstantLongValue(0)))
        return TacResult(allArguments, temp)
    }

    private fun translateUnaryIncrement(expression: UnaryExpression): TacResult {
        val (addrInstrs, addr) = lValueVisitor.translate(expression.operand)
        val instructions = mutableListOf<TacInstruction>()
        instructions.addAll(addrInstrs)
        val (lts, lte) = generateLoadInstruction(addr)
        requireNotNull(lte)
        instructions.addAll(lts)
        val newTemp = tempFactory.newTemp()
        instructions.add(
            TacBinaryInstruction(
                newTemp,
                BinaryOperator.Add,
                lte,
                TacConstantLongValue(1),
            ),
        )
        val (sts, _) = generateStoreInstruction(addr, newTemp)
        instructions.addAll(sts)
        return TacResult(instructions, newTemp)
    }

    private fun translateUnaryDecrement(expression: UnaryExpression): TacResult {
        val (addrInstrs, addr) = lValueVisitor.translate(expression.operand)
        val instructions = mutableListOf<TacInstruction>()
        instructions.addAll(addrInstrs)
        val (lts, lte) = generateLoadInstruction(addr)
        requireNotNull(lte)
        instructions.addAll(lts)
        val newTemp = tempFactory.newTemp()
        instructions.add(
            TacBinaryInstruction(
                newTemp,
                BinaryOperator.Subtract,
                lte,
                TacConstantLongValue(1),
            ),
        )
        val (sts, _) = generateStoreInstruction(addr, newTemp)
        instructions.addAll(sts)
        return TacResult(instructions, newTemp)
    }

    private fun generateLoadInstruction(lvalue: TacLValue): TacResult {
        return when (lvalue) {
            is VarLValue -> {
                val temp = tempFactory.newTemp()
                val instruction = TacLoadInstruction(temp, lvalue.variable)
                TacResult(listOf(instruction), temp)
            }

            is IndirectLValue -> {
                val temp = tempFactory.newTemp()
                val instruction = TacLoadIndirectInstruction(temp, lvalue.ptr)
                TacResult(listOf(instruction), temp)
            }

            is ArrayLValue -> {
                val (ts, te) = generateLoadInstruction(lvalue.base)
                requireNotNull(te)
                val temp = tempFactory.newTemp()
                val instruction = TacLoadArrayInstruction(temp, te, lvalue.index)
                TacResult(ts + instruction, temp)
            }

            is FieldLValue -> {
                val (ts, te) = generateLoadInstruction(lvalue.base)
                requireNotNull(te)
                val temp = tempFactory.newTemp()
                val instruction = TacLoadFieldInstruction(temp, te, lvalue.field)
                TacResult(ts + instruction, temp)
            }
        }
    }

    private fun generateStoreInstruction(lvalue: TacLValue, value: TacValue): TacResult {
        return when (lvalue) {
            is VarLValue -> {
                val instruction = TacStoreInstruction(lvalue.variable, value)
                TacResult(listOf(instruction), null)
            }

            is IndirectLValue -> {
                val instruction = TacStoreIndirectInstruction(lvalue.ptr, value)
                TacResult(listOf(instruction), null)
            }

            is ArrayLValue -> {
                val (ts, te) = generateLoadInstruction(lvalue.base)
                requireNotNull(te)
                val instruction = TacStoreArrayInstruction(te, lvalue.index, value)
                TacResult(ts + instruction, null)
            }

            is FieldLValue -> {
                val (ts, te) = generateLoadInstruction(lvalue.base)
                requireNotNull(te)
                val instruction = TacStoreFieldInstruction(te, lvalue.field, value)
                TacResult(ts + instruction, null)
            }
        }
    }
}
