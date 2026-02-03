package org.erwinkok.conjvm.ast.translation

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.expressions.ArrayAccessExpression
import org.erwinkok.conjvm.ast.expressions.AssignmentExpression
import org.erwinkok.conjvm.ast.expressions.BinaryExpression
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
import org.erwinkok.conjvm.ast.expressions.VariableReference
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

data class TranslationResult(
    val statements: List<Statement>,
    val expression: Expression?,
)

interface ExpressionTranslationVisitor : AstExpressionVisitor<TranslationResult> {
    fun translate(node: Expression): TranslationResult = node.accept(this)

    fun translateArrayAccess(expression: ArrayAccessExpression): TranslationResult
    fun translateAssignment(expression: AssignmentExpression): TranslationResult
    fun translateBinary(expression: BinaryExpression): TranslationResult
    fun translateCall(expression: CallExpression): TranslationResult
    fun translateCast(expression: CastExpression): TranslationResult
    fun translateCharacterLiteral(expression: CharacterLiteralExpression): TranslationResult
    fun translateConditional(expression: ConditionalExpression): TranslationResult
    fun translateFieldAccess(expression: FieldAccessExpression): TranslationResult
    fun translateFloatLiteral(expression: FloatLiteralExpression): TranslationResult
    fun translateIntegerLiteral(expression: IntegerLiteralExpression): TranslationResult
    fun translateParenthesized(expression: ParenthesizedExpression): TranslationResult
    fun translatePostfixDecrement(expression: PostfixDecrementExpression): TranslationResult
    fun translatePostfixIncrement(expression: PostfixIncrementExpression): TranslationResult
    fun translateStringLiteral(expression: StringLiteralExpression): TranslationResult
    fun translateUnary(expression: UnaryExpression): TranslationResult
    fun translateVariableReference(variableReference: VariableReference): TranslationResult

    override fun visitArrayAccess(expression: ArrayAccessExpression): TranslationResult {
        return translateArrayAccess(expression)
    }

    override fun visitAssignment(expression: AssignmentExpression): TranslationResult {
        return translateAssignment(expression)
    }

    override fun visitBinary(expression: BinaryExpression): TranslationResult {
        return translateBinary(expression)
    }

    override fun visitCall(expression: CallExpression): TranslationResult {
        return translateCall(expression)
    }

    override fun visitCast(expression: CastExpression): TranslationResult {
        return translateCast(expression)
    }

    override fun visitCharacterLiteral(expression: CharacterLiteralExpression): TranslationResult {
        return translateCharacterLiteral(expression)
    }

    override fun visitConditional(expression: ConditionalExpression): TranslationResult {
        return translateConditional(expression)
    }

    override fun visitFieldAccess(expression: FieldAccessExpression): TranslationResult {
        return translateFieldAccess(expression)
    }

    override fun visitFloatLiteral(expression: FloatLiteralExpression): TranslationResult {
        return translateFloatLiteral(expression)
    }

    override fun visitIntegerLiteral(expression: IntegerLiteralExpression): TranslationResult {
        return translateIntegerLiteral(expression)
    }

    override fun visitParenthesized(expression: ParenthesizedExpression): TranslationResult {
        return translateParenthesized(expression)
    }

    override fun visitPostfixDecrement(expression: PostfixDecrementExpression): TranslationResult {
        return translatePostfixDecrement(expression)
    }

    override fun visitPostfixIncrement(expression: PostfixIncrementExpression): TranslationResult {
        return translatePostfixIncrement(expression)
    }

    override fun visitStringLiteral(expression: StringLiteralExpression): TranslationResult {
        return translateStringLiteral(expression)
    }

    override fun visitUnary(expression: UnaryExpression): TranslationResult {
        return translateUnary(expression)
    }

    override fun visitVariableReference(expression: VariableReference): TranslationResult {
        return translateVariableReference(expression)
    }
}

interface StatementTranslationVisitor : AstStatementVisitor<TranslationResult> {
    fun translate(node: Statement): TranslationResult = node.accept(this)

    fun translateBlock(statement: BlockStatement): TranslationResult
    fun translateBreak(statement: BreakStatement): TranslationResult
    fun translateCompilationUnit(statement: CompilationUnitStatement): TranslationResult
    fun translateContinue(statement: ContinueStatement): TranslationResult
    fun translateDoWhile(statement: DoWhileStatement): TranslationResult
    fun translateExpression(statement: ExpressionStatement): TranslationResult
    fun translateFor(statement: ForStatement): TranslationResult
    fun translateFunctionDefinition(definition: FunctionDefinitionStatement): TranslationResult
    fun translateGoto(statement: GotoStatement): TranslationResult
    fun translateIfThen(statement: IfThenStatement): TranslationResult
    fun translateIfThenElse(statement: IfThenElseStatement): TranslationResult
    fun translateLabeled(statement: LabeledStatement): TranslationResult
    fun translateReturn(statement: ReturnStatement): TranslationResult
    fun translateSwitch(statement: SwitchStatement): TranslationResult
    fun translateVariableDeclaration(statement: VariableDeclarationStatement): TranslationResult
    fun translateWhile(statement: WhileStatement): TranslationResult

    override fun visitBlock(statement: BlockStatement): TranslationResult {
        return translateBlock(statement)
    }

    override fun visitBreak(statement: BreakStatement): TranslationResult {
        return translateBreak(statement)
    }

    override fun visitCompilationUnit(statement: CompilationUnitStatement): TranslationResult {
        return translateCompilationUnit(statement)
    }

    override fun visitContinue(statement: ContinueStatement): TranslationResult {
        return translateContinue(statement)
    }

    override fun visitDoWhile(statement: DoWhileStatement): TranslationResult {
        return translateDoWhile(statement)
    }

    override fun visitExpression(statement: ExpressionStatement): TranslationResult {
        return translateExpression(statement)
    }

    override fun visitFor(statement: ForStatement): TranslationResult {
        return translateFor(statement)
    }

    override fun visitFunctionDefinition(definition: FunctionDefinitionStatement): TranslationResult {
        return translateFunctionDefinition(definition)
    }

    override fun visitGoto(statement: GotoStatement): TranslationResult {
        return translateGoto(statement)
    }

    override fun visitIfThen(statement: IfThenStatement): TranslationResult {
        return translateIfThen(statement)
    }

    override fun visitIfThenElse(statement: IfThenElseStatement): TranslationResult {
        return translateIfThenElse(statement)
    }

    override fun visitLabeled(statement: LabeledStatement): TranslationResult {
        return translateLabeled(statement)
    }

    override fun visitReturn(statement: ReturnStatement): TranslationResult {
        return translateReturn(statement)
    }

    override fun visitSwitch(statement: SwitchStatement): TranslationResult {
        return translateSwitch(statement)
    }

    override fun visitVariableDeclaration(statement: VariableDeclarationStatement): TranslationResult {
        return translateVariableDeclaration(statement)
    }

    override fun visitWhile(statement: WhileStatement): TranslationResult {
        return translateWhile(statement)
    }
}

interface TranslationVisitor :
    StatementTranslationVisitor,
    ExpressionTranslationVisitor
