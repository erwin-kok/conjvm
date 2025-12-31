package org.erwinkok.conjvm.translation

import org.erwinkok.conjvm.ast.expressions.ArrayAccessExpression
import org.erwinkok.conjvm.ast.expressions.AssignmentExpression
import org.erwinkok.conjvm.ast.expressions.BinaryExpression
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
import org.erwinkok.conjvm.ast.statements.SwitchCaseStatement
import org.erwinkok.conjvm.ast.statements.SwitchDefaultStatement
import org.erwinkok.conjvm.ast.statements.SwitchStatement
import org.erwinkok.conjvm.ast.statements.VariableDeclarationStatement
import org.erwinkok.conjvm.ast.statements.VariableDeclarator
import org.erwinkok.conjvm.ast.statements.WhileStatement

abstract class BaseTranslationVisitor : TranslationVisitor {
    override fun translateArrayAccess(expression: ArrayAccessExpression): TranslationResult {
        val (ts, te) = translate(expression.index)
        requireNotNull(te)
        return TranslationResult(ts, ArrayAccessExpression(expression.location, expression.base, te))
    }

    override fun translateAssignment(expression: AssignmentExpression): TranslationResult {
        val (lts, lte) = translate(expression.leftExpression)
        val (rts, rte) = translate(expression.rightExpression)
        requireNotNull(lte)
        requireNotNull(rte)
        return TranslationResult(lts + rts, AssignmentExpression(expression.location, expression.type, lte, rte))
    }

    override fun translateBinary(expression: BinaryExpression): TranslationResult {
        val (lts, lte) = translate(expression.leftExpression)
        val (rts, rte) = translate(expression.rightExpression)
        requireNotNull(lte)
        requireNotNull(rte)
        return TranslationResult(lts + rts, BinaryExpression(expression.location, expression.type, lte, rte))
    }

    override fun translateCall(expression: CallExpression): TranslationResult {
        val allStatements = mutableListOf<Statement>()
        val allArguments = mutableListOf<Expression>()
        expression.arguments.map {
            val (ts, te) = translate(it)
            requireNotNull(te)
            allStatements.addAll(ts)
            allArguments.add(te)
        }
        return TranslationResult(allStatements, CallExpression(expression.location, expression.name, allArguments))
    }

    override fun translateCast(expression: CastExpression): TranslationResult {
        val (ts, te) = translate(expression.expression)
        requireNotNull(te)
        return TranslationResult(ts, CastExpression(expression.location, expression.type, te))
    }

    override fun translateConstantInt(expression: ConstantIntExpression): TranslationResult {
        return TranslationResult(emptyList(), expression)
    }

    override fun translateConstantLong(expression: ConstantLongExpression): TranslationResult {
        return TranslationResult(emptyList(), expression)
    }

    override fun translateConstantString(expression: ConstantStringExpression): TranslationResult {
        return TranslationResult(emptyList(), expression)
    }

    override fun translateFieldAccess(expression: FieldAccessExpression): TranslationResult {
        return TranslationResult(emptyList(), expression)
    }

    override fun translateIdentifier(identifier: Identifier): TranslationResult {
        return TranslationResult(emptyList(), identifier)
    }

    override fun translateParenthesized(expression: ParenthesizedExpression): TranslationResult {
        val (ts, te) = translate(expression.expression)
        requireNotNull(te)
        return TranslationResult(ts, ParenthesizedExpression(expression.location, te))
    }

    override fun translatePostfixDecrement(expression: PostfixDecrementExpression): TranslationResult {
        val (ts, te) = translate(expression.expression)
        requireNotNull(te)
        return TranslationResult(ts, PostfixDecrementExpression(expression.location, te))
    }

    override fun translatePostfixIncrement(expression: PostfixIncrementExpression): TranslationResult {
        val (ts, te) = translate(expression.expression)
        requireNotNull(te)
        return TranslationResult(ts, PostfixIncrementExpression(expression.location, te))
    }

    override fun translateTernary(expression: TernaryExpression): TranslationResult {
        val (testTs, testTe) = translate(expression.testExpression)
        val (thenTs, thenTe) = translate(expression.thenExpression)
        val (elseTs, elseTe) = translate(expression.elseExpression)
        requireNotNull(testTe)
        requireNotNull(thenTe)
        requireNotNull(elseTe)
        return TranslationResult(testTs + thenTs + elseTs, TernaryExpression(expression.location, testTe, thenTe, elseTe))
    }

    override fun translateUnary(expression: UnaryExpression): TranslationResult {
        val (ts, te) = translate(expression.expression)
        requireNotNull(te)
        return TranslationResult(ts, UnaryExpression(expression.location, expression.type, te))
    }

    override fun translateBlock(statement: BlockStatement): TranslationResult {
        return TranslationResult(
            listOf(translateBlockStatement(statement)),
            null,
        )
    }

    override fun translateBreak(statement: BreakStatement): TranslationResult {
        return TranslationResult(listOf(statement), null)
    }

    override fun translateCompilationUnit(statement: CompilationUnitStatement): TranslationResult {
        val translatedVarDecls = statement.variableDeclarations.map {
            val (ts, te) = translate(it)
            require(te == null)
            require(ts.size == 1)
            val variableDeclaration = ts.first()
            require(variableDeclaration is VariableDeclarationStatement)
            variableDeclaration
        }
        val translatedStatements = statement.functionDefinitions.map {
            val (ts, te) = translate(it)
            require(te == null)
            require(ts.size == 1)
            val functionDefinitionStatement = ts.first()
            require(functionDefinitionStatement is FunctionDefinitionStatement)
            functionDefinitionStatement
        }
        return TranslationResult(
            listOf(
                CompilationUnitStatement(statement.location, translatedVarDecls, translatedStatements),
            ),
            null,
        )
    }

    override fun translateContinue(statement: ContinueStatement): TranslationResult {
        return TranslationResult(listOf(statement), null)
    }

    override fun translateExpression(statement: ExpressionStatement): TranslationResult {
        val (ts, te) = translate(statement.expression)
        requireNotNull(te)
        return TranslationResult(ts + ExpressionStatement(statement.location, te), null)
    }

    override fun translateFor(statement: ForStatement): TranslationResult {
        val translatedBlock = translateBlockStatement(statement.statements)
        return TranslationResult(
            listOf(ForStatement(statement.location, statement.init, statement.condition, statement.iterators, translatedBlock)),
            null,
        )
    }

    override fun translateFunctionDefinition(definition: FunctionDefinitionStatement): TranslationResult {
        val translatedBlock = translateBlockStatement(definition.statements)
        return TranslationResult(
            listOf(
                FunctionDefinitionStatement(
                    definition.location,
                    definition.returnType,
                    definition.name,
                    definition.params,
                    translatedBlock,
                ),
            ),
            null,
        )
    }

    override fun translateGoto(statement: GotoStatement): TranslationResult {
        return TranslationResult(listOf(statement), null)
    }

    override fun translateIfThenElse(statement: IfThenElseStatement): TranslationResult {
        val translatedThenBlock = translateBlockStatement(statement.thenBlock)
        val translatedElseBlock = translateBlockStatement(statement.elseBlock)
        return TranslationResult(
            listOf(IfThenElseStatement(statement.location, statement.test, translatedThenBlock, translatedElseBlock)),
            null,
        )
    }

    override fun translateIfThen(statement: IfThenStatement): TranslationResult {
        val translatedThenBlock = translateBlockStatement(statement.thenBlock)
        return TranslationResult(
            listOf(IfThenStatement(statement.location, statement.test, translatedThenBlock)),
            null,
        )
    }

    override fun translateLabeled(statement: LabeledStatement): TranslationResult {
        return TranslationResult(listOf(statement), null)
    }

    override fun translateReturn(statement: ReturnStatement): TranslationResult {
        return TranslationResult(listOf(statement), null)
    }

    override fun translateSwitch(statement: SwitchStatement): TranslationResult {
        val sections = statement.sections.map {
            SwitchCaseStatement(it.location, it.test, translateBlockStatement(it.blockStatement))
        }
        val defaultSection = statement.defaultSection?.let { SwitchDefaultStatement(it.location, translateBlockStatement(it.blockStatement)) }
        return TranslationResult(
            listOf(SwitchStatement(statement.location, statement.test, sections, defaultSection)),
            null,
        )
    }

    override fun translateVariableDeclaration(statement: VariableDeclarationStatement): TranslationResult {
        val allStatements = mutableListOf<Statement>()
        val varDecls = statement.variableDeclarators.map {
            translateVariableDeclarator(allStatements, it)
        }
        return TranslationResult(
            allStatements +
                VariableDeclarationStatement(statement.location, statement.declarationSpecifier, varDecls),
            null,
        )
    }

    override fun translateWhile(statement: WhileStatement): TranslationResult {
        val translatedBlock = translateBlockStatement(statement.statements)
        return TranslationResult(
            listOf(WhileStatement(statement.location, statement.condition, translatedBlock)),
            null,
        )
    }

    protected fun translateBlockStatement(statement: BlockStatement): BlockStatement {
        val allStatements = mutableListOf<Statement>()
        for (s in statement.statements) {
            val (ts, te) = translate(s)
            require(te == null)
            allStatements.addAll(ts)
        }
        return BlockStatement(statement.location, allStatements)
    }

    private fun translateVariableDeclarator(allStatements: MutableList<Statement>, varDecl: VariableDeclarator): VariableDeclarator {
        val init = varDecl.init?.let {
            val (ts, te) = translate(it)
            allStatements.addAll(ts)
            te
        }
        return VariableDeclarator(varDecl.location, varDecl.declarator, init)
    }
}
