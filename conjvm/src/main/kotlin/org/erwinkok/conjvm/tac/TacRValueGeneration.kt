package org.erwinkok.conjvm.tac

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.expressions.ArrayAccessExpression
import org.erwinkok.conjvm.ast.expressions.AssignmentExpression
import org.erwinkok.conjvm.ast.expressions.AssignmentExpressionType
import org.erwinkok.conjvm.ast.expressions.BinaryExpression
import org.erwinkok.conjvm.ast.expressions.BinaryExpressionType
import org.erwinkok.conjvm.ast.expressions.CallExpression
import org.erwinkok.conjvm.ast.expressions.CastExpression
import org.erwinkok.conjvm.ast.expressions.ConstantIntExpression
import org.erwinkok.conjvm.ast.expressions.ConstantLongExpression
import org.erwinkok.conjvm.ast.expressions.ConstantStringExpression
import org.erwinkok.conjvm.ast.expressions.Expression
import org.erwinkok.conjvm.ast.expressions.FieldAccessExpression
import org.erwinkok.conjvm.ast.expressions.Identifier
import org.erwinkok.conjvm.ast.expressions.ParenthesizedExpression
import org.erwinkok.conjvm.ast.expressions.PostfixDecrementExpression
import org.erwinkok.conjvm.ast.expressions.PostfixIncrementExpression
import org.erwinkok.conjvm.ast.expressions.TernaryExpression
import org.erwinkok.conjvm.ast.expressions.UnaryExpression
import org.erwinkok.conjvm.ast.expressions.UnaryType
import org.erwinkok.conjvm.ast.types.VariableType
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
import org.erwinkok.conjvm.tac.values.TacConstantLongValue
import org.erwinkok.conjvm.tac.values.TacConstantStringValue
import org.erwinkok.conjvm.tac.values.TacValue

class TacRValueGeneration(
    private val tempFactory: TacTempFactory,
) : AstExpressionVisitor<TacResult, TacContext> {
    private val lValueVisitor = TacLValueGeneration(this)

    fun translate(node: Expression): TacResult = node.accept(this, TacContext())

    override fun visitArrayAccess(expression: ArrayAccessExpression, ctx: TacContext): TacResult {
        val (ts, te) = lValueVisitor.translate(expression)
        requireNotNull(te)
        val (tsl, tel) = generateLoadInstruction(te)
        return TacResult(ts + tsl, tel)
    }

    override fun visitConstantInt(expression: ConstantIntExpression, ctx: TacContext): TacResult {
        return TacResult(emptyList(), TacConstantLongValue(expression.value.toLong()))
    }

    override fun visitConstantLong(expression: ConstantLongExpression, ctx: TacContext): TacResult {
        return TacResult(emptyList(), TacConstantLongValue(expression.value))
    }

    override fun visitConstantString(expression: ConstantStringExpression, ctx: TacContext): TacResult {
        return TacResult(emptyList(), TacConstantStringValue(expression.value))
    }

    override fun visitFieldAccess(expression: FieldAccessExpression, ctx: TacContext): TacResult {
        val (ts, te) = lValueVisitor.translate(expression)
        requireNotNull(te)
        val (tsl, tel) = generateLoadInstruction(te)
        return TacResult(ts + tsl, tel)
    }

    override fun visitIdentifier(identifier: Identifier, ctx: TacContext): TacResult {
        val (ts, te) = lValueVisitor.translate(identifier)
        requireNotNull(te)
        val (tsl, tel) = generateLoadInstruction(te)
        return TacResult(ts + tsl, tel)
    }

    override fun visitParenthesized(expression: ParenthesizedExpression, ctx: TacContext): TacResult {
        val (ts, te) = translate(expression.expression)
        requireNotNull(te)
        return TacResult(ts, te)
    }

    override fun visitPostfixDecrement(expression: PostfixDecrementExpression, ctx: TacContext): TacResult {
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
                BinaryExpressionType.Subtract,
                lte,
                TacConstantLongValue(1),
            ),
        )
        val (sts, _) = generateStoreInstruction(addr, newTemp)
        instructions.addAll(sts)
        return TacResult(instructions, lte)
    }

    override fun visitPostfixIncrement(expression: PostfixIncrementExpression, ctx: TacContext): TacResult {
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
                BinaryExpressionType.Add,
                lte,
                TacConstantLongValue(1),
            ),
        )
        val (sts, _) = generateStoreInstruction(addr, newTemp)
        instructions.addAll(sts)
        return TacResult(instructions, lte)
    }

    override fun visitAssignment(expression: AssignmentExpression, ctx: TacContext): TacResult {
        val (lts, lte) = lValueVisitor.translate(expression.leftExpression)
        val (rts, rte) = translate(expression.rightExpression)
        requireNotNull(lte)
        requireNotNull(rte)
        require(expression.type == AssignmentExpressionType.Assign)
        val (tsl, tel) = generateStoreInstruction(lte, rte)
        return TacResult(lts + rts + tsl, tel)
    }

    override fun visitBinary(expression: BinaryExpression, ctx: TacContext): TacResult {
        val allArguments = mutableListOf<TacInstruction>()
        val lte = translate(expression.leftExpression)
        val rte = translate(expression.rightExpression)
        requireNotNull(lte.tacValue)
        requireNotNull(rte.tacValue)
        allArguments.addAll(lte.statements)
        allArguments.addAll(rte.statements)
        val temp = tempFactory.newTemp()
        allArguments.add(TacBinaryInstruction(temp, expression.type, lte.tacValue, rte.tacValue))
        return TacResult(allArguments, temp)
    }

    override fun visitCall(expression: CallExpression, ctx: TacContext): TacResult {
        val allArguments = mutableListOf<TacInstruction>()
        val args = expression.arguments.map {
            val (ts, te) = translate(it)
            requireNotNull(te)
            allArguments.addAll(ts)
            te
        }
        val temp = tempFactory.newTemp()
        if (expression.name is Identifier) {
            allArguments.add(TacCallInstruction(temp, TacConstantStringValue(expression.name.name), args))
        } else {
            val (ts, te) = translate(expression.name)
            requireNotNull(te)
            allArguments.addAll(ts)
            allArguments.add(TacCallInstruction(temp, te, args))
        }
        return TacResult(allArguments, temp)
    }

    override fun visitCast(expression: CastExpression, ctx: TacContext): TacResult {
        val allArguments = mutableListOf<TacInstruction>()
        val testTr = translate(expression.expression)
        requireNotNull(testTr.tacValue)
        allArguments.addAll(testTr.statements)
        val temp = tempFactory.newTemp()
        allArguments.add(TacCastInstruction(temp, VariableType.INT, testTr.tacValue)) // TODO VariableType
        return TacResult(allArguments, temp)
    }

    override fun visitTernary(expression: TernaryExpression, ctx: TacContext): TacResult {
        val allArguments = mutableListOf<TacInstruction>()
        val testTr = translate(expression.testExpression)
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

    override fun visitUnary(expression: UnaryExpression, ctx: TacContext): TacResult {
        return when (expression.type) {
            UnaryType.Address -> translateUnaryAddressOf(expression)
            UnaryType.Indirection -> translateUnaryIndirection(expression)
            UnaryType.Plus -> translateUnaryPlus(expression)
            UnaryType.Minus -> translateUnaryMinus(expression)
            UnaryType.BitwiseNot -> translateUnaryBitwiseNot(expression)
            UnaryType.LogicalNot -> translateUnaryLogicalNot(expression)
            UnaryType.PlusPlus -> translateUnaryIncrement(expression)
            UnaryType.MinusMinus -> translateUnaryDecrement(expression)
        }
    }

    private fun translateUnaryAddressOf(expression: UnaryExpression): TacResult {
        val (ts, te) = lValueVisitor.translate(expression.expression)
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
        val (ts, te) = translate(expression.expression)
        requireNotNull(te)
        return TacResult(ts, te)
    }

    private fun translateUnaryMinus(expression: UnaryExpression): TacResult {
        val (ts, te) = translate(expression.expression)
        requireNotNull(te)
        val allArguments = mutableListOf<TacInstruction>()
        allArguments.addAll(ts)
        val temp = tempFactory.newTemp()
        allArguments.add(TacBinaryInstruction(temp, BinaryExpressionType.Subtract, TacConstantLongValue(0), te))
        return TacResult(allArguments, temp)
    }

    private fun translateUnaryBitwiseNot(expression: UnaryExpression): TacResult {
        val (ts, te) = translate(expression.expression)
        requireNotNull(te)
        val allArguments = mutableListOf<TacInstruction>()
        allArguments.addAll(ts)
        val temp = tempFactory.newTemp()
        allArguments.add(TacBinaryInstruction(temp, BinaryExpressionType.ExclusiveOr, te, TacConstantLongValue(-1)))
        return TacResult(allArguments, temp)
    }

    private fun translateUnaryLogicalNot(expression: UnaryExpression): TacResult {
        val (ts, te) = translate(expression.expression)
        requireNotNull(te)
        val allArguments = mutableListOf<TacInstruction>()
        allArguments.addAll(ts)
        val temp = tempFactory.newTemp()
        allArguments.add(TacBinaryInstruction(temp, BinaryExpressionType.Equals, te, TacConstantLongValue(0)))
        return TacResult(allArguments, temp)
    }

    private fun translateUnaryIncrement(expression: UnaryExpression): TacResult {
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
                BinaryExpressionType.Add,
                lte,
                TacConstantLongValue(1),
            ),
        )
        val (sts, _) = generateStoreInstruction(addr, newTemp)
        instructions.addAll(sts)
        return TacResult(instructions, newTemp)
    }

    private fun translateUnaryDecrement(expression: UnaryExpression): TacResult {
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
                BinaryExpressionType.Subtract,
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
