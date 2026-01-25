package org.erwinkok.conjvm.tac

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.expressions.BinaryExpressionType
import org.erwinkok.conjvm.ast.expressions.Expression
import org.erwinkok.conjvm.ast.statements.BlockStatement
import org.erwinkok.conjvm.ast.statements.BreakStatement
import org.erwinkok.conjvm.ast.statements.CompilationUnitStatement
import org.erwinkok.conjvm.ast.statements.ContinueStatement
import org.erwinkok.conjvm.ast.statements.DoWhileStatement
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
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.tac.instructions.TacBinaryInstruction
import org.erwinkok.conjvm.tac.instructions.TacFunctionDefinition
import org.erwinkok.conjvm.tac.instructions.TacGotoInstruction
import org.erwinkok.conjvm.tac.instructions.TacIfGotoInstruction
import org.erwinkok.conjvm.tac.instructions.TacInstruction
import org.erwinkok.conjvm.tac.instructions.TacLabeledInstruction
import org.erwinkok.conjvm.tac.instructions.TacReturnInstruction
import org.erwinkok.conjvm.tac.instructions.TacStoreInstruction
import org.erwinkok.conjvm.tac.lvalues.TacIdentifier

class TacTranslation(
    private val reporter: ErrorReporter,
) : AstStatementVisitor<TacResult> {
    private val tempFactory = TacTempFactory()
    private val labelFactory = TacLabelFactory()
    private val functionMap = mutableMapOf<String, TacFunctionDefinition>()
    private val rvalueGeneration = TacRValueGeneration(tempFactory)

    val functions: Map<String, TacFunctionDefinition>
        get() = functionMap

    fun translateStatement(node: Statement): TacResult = node.accept(this)
    fun translateExpression(node: Expression): TacResult = node.accept(rvalueGeneration)

    override fun visitCompilationUnit(statement: CompilationUnitStatement): TacResult {
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

    override fun visitFunctionDefinition(definition: FunctionDefinitionStatement): TacResult {
        tempFactory.clear()
        labelFactory.clear()
        val translatedBlock = translateBlockStatement(definition.statements)
        val name = definition.declarator.name() ?: "anonymous" // TODO
        return TacResult(listOf(TacFunctionDefinition(name, translatedBlock)), null)
    }

    override fun visitBlock(statement: BlockStatement): TacResult {
        return TacResult(translateBlockStatement(statement), null)
    }

    override fun visitBreak(statement: BreakStatement): TacResult {
        return TacResult(emptyList(), null)
    }

    override fun visitContinue(statement: ContinueStatement): TacResult {
        error("continue statement should not be present when transforming to TAC")
    }

    override fun visitExpression(statement: ExpressionStatement): TacResult {
        val (ts, _) = translateExpression(statement.expression)
        return TacResult(ts, null)
    }

    override fun visitFor(statement: ForStatement): TacResult {
        error("for statement should not be present when transforming to TAC")
    }

    override fun visitGoto(statement: GotoStatement): TacResult {
        return TacResult(listOf(TacGotoInstruction(TacLabel(statement.label))), null)
    }

    override fun visitIfThenElse(statement: IfThenElseStatement): TacResult {
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

    override fun visitIfThen(statement: IfThenStatement): TacResult {
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

    override fun visitLabeled(statement: LabeledStatement): TacResult {
        val (ts, te) = translateStatement(statement.statement)
        require(te == null)
        val allStatements = mutableListOf<TacInstruction>()
        allStatements.add(TacLabeledInstruction(TacLabel(statement.id)))
        allStatements.addAll(ts)
        return TacResult(allStatements, null)
    }

    override fun visitReturn(statement: ReturnStatement): TacResult {
        require(statement.value == null)
        return TacResult(listOf(TacReturnInstruction()), null)
    }

    override fun visitSwitch(statement: SwitchStatement): TacResult {
        val allStatements = mutableListOf<TacInstruction>()

        // Evaluate switch expression
        val (testInstrs, testExpr) = translateExpression(statement.test)
        require(testExpr != null)
        allStatements.addAll(testInstrs)

        // Prepare labels
        val caseLabels = statement.sections.map { it to labelFactory.new() }
        val endLabel = labelFactory.new()

        // Assign label to default if present
        val defaultLabel = statement.defaultSection?.let { it to labelFactory.new() }

        // First, write the case goto table.
        for ((caseStatement, caseLabel) in caseLabels) {
            val (caseInstrs, caseTemp) = translateExpression(caseStatement.test)
            require(caseTemp != null)
            val cmpTemp = tempFactory.newTemp()
            allStatements.addAll(caseInstrs)
            allStatements.add(TacBinaryInstruction(cmpTemp, BinaryExpressionType.Equals, testExpr, caseTemp))
            allStatements.add(TacIfGotoInstruction(cmpTemp, caseLabel))
        }

        // Then, if there is a default block...
        if (defaultLabel != null) {
            // jump to the default label
            allStatements.add(TacGotoInstruction(defaultLabel.second))
        } else {
            // If not, jump to the end label
            allStatements.add(TacGotoInstruction(endLabel))
        }

        // Write all the case blocks with their label
        for ((caseStatement, caseLabel) in caseLabels) {
            allStatements.add(TacLabeledInstruction(caseLabel))
            allStatements.addAll(emitSwitchBlock(caseStatement.blockStatement, endLabel))
        }

        // If there is a default block, write the block
        if (defaultLabel != null) {
            allStatements.add(TacLabeledInstruction(defaultLabel.second))
            allStatements.addAll(emitSwitchBlock(defaultLabel.first.blockStatement, endLabel))
        }

        // Write the end label
        allStatements.add(TacLabeledInstruction(endLabel))
        return TacResult(allStatements, null)
    }

    private fun emitSwitchBlock(blockStatement: BlockStatement, endLabel: TacLabel): List<TacInstruction> {
        val allStatements = mutableListOf<TacInstruction>()
        for (i in blockStatement.statements) {
            if (i is BreakStatement) {
                allStatements.add(TacGotoInstruction(endLabel))
            } else {
                val (ts, te) = translateStatement(i)
                require(te == null)
                allStatements.addAll(ts)
            }
        }
        return allStatements
    }

    override fun visitVariableDeclaration(statement: VariableDeclarationStatement): TacResult {
        val allStatements = mutableListOf<TacInstruction>()
        statement.variableDeclarators.forEach {
            it.init?.let { vd ->
                val (ts, te) = translateExpression(vd)
                requireNotNull(te)
                val name = it.declarator.name() ?: "anonymous" // TODO
                allStatements.addAll(ts)
                allStatements.add(TacStoreInstruction(TacIdentifier(name), te))
            }
        }
        return TacResult(allStatements, null)
    }

    override fun visitWhile(statement: WhileStatement): TacResult {
        val allStatements = mutableListOf<TacInstruction>()
        val (ts, te) = translateExpression(statement.condition)
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

    override fun visitDoWhile(statement: DoWhileStatement): TacResult {
        val allStatements = mutableListOf<TacInstruction>()
        val (ts, te) = translateExpression(statement.condition)
        requireNotNull(te)
        val translatedBlock = translateBlockStatement(statement.statements)
        val doLabel = labelFactory.new()
        allStatements.add(TacLabeledInstruction(doLabel))
        allStatements.addAll(translatedBlock)
        allStatements.addAll(ts)
        allStatements.add(TacIfGotoInstruction(te, doLabel))
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
