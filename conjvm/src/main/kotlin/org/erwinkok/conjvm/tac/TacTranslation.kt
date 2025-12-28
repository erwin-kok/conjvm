package org.erwinkok.conjvm.tac

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.expressions.BinaryExpressionType
import org.erwinkok.conjvm.ast.expressions.Expression
import org.erwinkok.conjvm.ast.statements.BlockStatement
import org.erwinkok.conjvm.ast.statements.BreakStatement
import org.erwinkok.conjvm.ast.statements.CompilationUnitStatement
import org.erwinkok.conjvm.ast.statements.ContinueStatement
import org.erwinkok.conjvm.ast.statements.ExpressionStatement
import org.erwinkok.conjvm.ast.statements.ForStatement
import org.erwinkok.conjvm.ast.statements.FunctionDefinitionStatement
import org.erwinkok.conjvm.ast.statements.GotoStatement
import org.erwinkok.conjvm.ast.statements.IfThenElseStatement
import org.erwinkok.conjvm.ast.statements.IfThenStatement
import org.erwinkok.conjvm.ast.statements.LabeledStatement
import org.erwinkok.conjvm.ast.statements.ReturnStatement
import org.erwinkok.conjvm.ast.statements.Statement
import org.erwinkok.conjvm.ast.statements.SwitchStatement
import org.erwinkok.conjvm.ast.statements.VariableDeclarationStatement
import org.erwinkok.conjvm.ast.statements.WhileStatement
import org.erwinkok.conjvm.tac.instructions.TacBinaryInstruction
import org.erwinkok.conjvm.tac.instructions.TacFunctionDefinition
import org.erwinkok.conjvm.tac.instructions.TacGotoInstruction
import org.erwinkok.conjvm.tac.instructions.TacIfGotoInstruction
import org.erwinkok.conjvm.tac.instructions.TacInstruction
import org.erwinkok.conjvm.tac.instructions.TacLabeledInstruction
import org.erwinkok.conjvm.tac.instructions.TacReturnInstruction
import org.erwinkok.conjvm.tac.instructions.TacStoreInstruction
import org.erwinkok.conjvm.tac.lvalues.TacIdentifier

class TacTranslation : AstStatementVisitor<TacResult, TacContext> {
    private val tempFactory = TacTempFactory()
    private val labelFactory = TacLabelFactory()
    private val functionMap = mutableMapOf<String, TacFunctionDefinition>()
    private val rvalueGeneration = TacRValueGeneration(tempFactory)

    val functions: Map<String, TacFunctionDefinition>
        get() = functionMap

    fun translateStatement(node: Statement): TacResult = node.accept(this, TacContext())
    fun translateExpression(node: Expression): TacResult = node.accept(rvalueGeneration, TacContext())

    override fun visitCompilationUnit(statement: CompilationUnitStatement, ctx: TacContext): TacResult {
        statement.functionDefinitions.forEach {
            val (ts, te) = translateStatement(it)
            require(te == null)
            require(ts.size == 1)
            val functionDefinitionStatement = ts.first()
            require(functionDefinitionStatement is TacFunctionDefinition)
            functionMap[functionDefinitionStatement.name] = functionDefinitionStatement
        }
        return TacResult(emptyList(), null)
    }

    override fun visitFunctionDefinition(definition: FunctionDefinitionStatement, ctx: TacContext): TacResult {
        tempFactory.clear()
        labelFactory.clear()
        val translatedBlock = translateBlockStatement(definition.statements)
        return TacResult(listOf(TacFunctionDefinition(definition.name, translatedBlock)), null)
    }

    override fun visitBlock(statement: BlockStatement, ctx: TacContext): TacResult {
        return TacResult(translateBlockStatement(statement), null)
    }

    override fun visitBreak(statement: BreakStatement, ctx: TacContext): TacResult {
        return TacResult(emptyList(), null)
    }

    override fun visitContinue(statement: ContinueStatement, ctx: TacContext): TacResult {
        error("continue statement should not be present when transforming to TAC")
    }

    override fun visitExpression(statement: ExpressionStatement, ctx: TacContext): TacResult {
        val (ts, _) = translateExpression(statement.expression)
        return TacResult(ts, null)
    }

    override fun visitFor(statement: ForStatement, ctx: TacContext): TacResult {
        error("for statement should not be present when transforming to TAC")
    }

    override fun visitGoto(statement: GotoStatement, ctx: TacContext): TacResult {
        return TacResult(listOf(TacGotoInstruction(TacLabel(statement.label))), null)
    }

    override fun visitIfThenElse(statement: IfThenElseStatement, ctx: TacContext): TacResult {
        val allStatements = mutableListOf<TacInstruction>()
        val (ts, te) = translateExpression(statement.test)
        allStatements.addAll(ts)
        requireNotNull(te)
        val translatedThenBlock = translateBlockStatement(statement.thenBlock)
        val translatedElseBlock = translateBlockStatement(statement.elseBlock)
        val thenLabel = labelFactory.new()
        val elseLabel = labelFactory.new()
        val endLabel = labelFactory.new()
        allStatements.add(TacIfGotoInstruction(te, thenLabel))
        allStatements.add(TacGotoInstruction(elseLabel))
        allStatements.add(TacLabeledInstruction(thenLabel))
        allStatements.addAll(translatedThenBlock)
        allStatements.add(TacGotoInstruction(endLabel))
        allStatements.add(TacLabeledInstruction(elseLabel))
        allStatements.addAll(translatedElseBlock)
        allStatements.add(TacLabeledInstruction(endLabel))
        return TacResult(allStatements, null)
    }

    override fun visitIfThen(statement: IfThenStatement, ctx: TacContext): TacResult {
        val allStatements = mutableListOf<TacInstruction>()
        val (ts, te) = translateExpression(statement.test)
        allStatements.addAll(ts)
        requireNotNull(te)
        val translatedThenBlock = translateBlockStatement(statement.thenBlock)
        val thenLabel = labelFactory.new()
        val endLabel = labelFactory.new()
        allStatements.add(TacIfGotoInstruction(te, thenLabel))
        allStatements.add(TacGotoInstruction(endLabel))
        allStatements.add(TacLabeledInstruction(thenLabel))
        allStatements.addAll(translatedThenBlock)
        allStatements.add(TacLabeledInstruction(endLabel))
        return TacResult(allStatements, null)
    }

    override fun visitLabeled(statement: LabeledStatement, ctx: TacContext): TacResult {
        val (ts, te) = translateStatement(statement.statement)
        require(te == null)
        val allStatements = mutableListOf<TacInstruction>()
        allStatements.add(TacLabeledInstruction(TacLabel(statement.id)))
        allStatements.addAll(ts)
        return TacResult(allStatements, null)
    }

    override fun visitReturn(statement: ReturnStatement, ctx: TacContext): TacResult {
        require(statement.value == null)
        return TacResult(listOf(TacReturnInstruction()), null)
    }

    override fun visitSwitch(statement: SwitchStatement, ctx: TacContext): TacResult {
        val allStatements = mutableListOf<TacInstruction>()
        val (ts, te) = translateExpression(statement.test)
        allStatements.addAll(ts)
        require(te != null)
        val caseList = mutableListOf<Pair<TacLabel, BlockStatement>>()
        for (section in statement.sections) {
            val temp = tempFactory.newTemp()
            val caseLabel = labelFactory.new()
            val (tst, tet) = translateExpression(section.test)
            require(tet != null)
            allStatements.addAll(tst)
            allStatements.add(TacBinaryInstruction(temp, BinaryExpressionType.Equals, te, tet))
            allStatements.add(TacIfGotoInstruction(temp, caseLabel))
            caseList.add(caseLabel to section.blockStatement)
        }
        val endLabel = labelFactory.new()
        var defaultLabel: TacLabel? = null
        var defaultBlock: BlockStatement? = null
        if (statement.defaultSection != null) {
            defaultLabel = labelFactory.new()
            allStatements.add(TacGotoInstruction(defaultLabel))
            defaultBlock = statement.defaultSection.blockStatement
        } else {
            allStatements.add(TacGotoInstruction(endLabel))
        }
        for (case in caseList) {
            allStatements.add(TacLabeledInstruction(case.first))
            for (i in case.second.statements) {
                if (i is BreakStatement) {
                    allStatements.add(TacGotoInstruction(endLabel))
                } else {
                    val (ts, te) = translateStatement(i)
                    require(te == null)
                    allStatements.addAll(ts)
                }
            }
        }
        if (defaultLabel != null) {
            for (i in defaultBlock!!.statements) {
                if (i is BreakStatement) {
                    allStatements.add(TacGotoInstruction(endLabel))
                } else {
                    val (ts, te) = translateStatement(i)
                    require(te == null)
                    allStatements.addAll(ts)
                }
            }
        }
        allStatements.add(TacLabeledInstruction(endLabel))
        return TacResult(allStatements, null)
    }

    override fun visitVariableDeclaration(statement: VariableDeclarationStatement, ctx: TacContext): TacResult {
        val allStatements = mutableListOf<TacInstruction>()
        statement.variableDeclarators.forEach {
            it.init?.let { vd ->
                val (ts, te) = translateExpression(vd)
                requireNotNull(te)
                allStatements.addAll(ts)
                allStatements.add(TacStoreInstruction(TacIdentifier(it.declarator.name), te))
            }
        }
        return TacResult(allStatements, null)
    }

    override fun visitWhile(statement: WhileStatement, ctx: TacContext): TacResult {
        val allStatements = mutableListOf<TacInstruction>()
        val (ts, te) = translateExpression(statement.test)
        requireNotNull(te)
        val translatedBlock = translateBlockStatement(statement.statements)
        val whileLabel = labelFactory.new()
        val doLabel = labelFactory.new()
        val endLabel = labelFactory.new()
        allStatements.add(TacLabeledInstruction(whileLabel))
        allStatements.addAll(ts)
        allStatements.add(TacIfGotoInstruction(te, doLabel))
        allStatements.add(TacGotoInstruction(endLabel))
        allStatements.add(TacLabeledInstruction(doLabel))
        allStatements.addAll(translatedBlock)
        allStatements.add(TacGotoInstruction(whileLabel))
        allStatements.add(TacLabeledInstruction(endLabel))
        return TacResult(allStatements, null)
    }

    private fun translateBlockStatement(statement: BlockStatement): List<TacInstruction> {
        val allStatements = mutableListOf<TacInstruction>()
        for (s in statement.statements) {
            val (ts, te) = translateStatement(s)
            require(te == null)
            allStatements.addAll(ts)
        }
        return allStatements
    }
}
