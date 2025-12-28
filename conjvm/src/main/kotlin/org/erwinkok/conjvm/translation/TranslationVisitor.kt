package org.erwinkok.conjvm.translation

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.AstStatementVisitor
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
import org.erwinkok.conjvm.ast.statements.SwitchStatement
import org.erwinkok.conjvm.ast.statements.VariableDeclarationStatement
import org.erwinkok.conjvm.ast.statements.WhileStatement

data class TranslationResult(
    val statements: List<Statement>,
    val expression: Expression?,
)

class TranslationContext

interface ExpressionTranslationVisitor : AstExpressionVisitor<TranslationResult, TranslationContext> {
    fun translate(node: Expression): TranslationResult = node.accept(this, TranslationContext())

    fun translateArrayAccess(expression: ArrayAccessExpression): TranslationResult
    fun translateAssignment(expression: AssignmentExpression): TranslationResult
    fun translateBinary(expression: BinaryExpression): TranslationResult
    fun translateCall(expression: CallExpression): TranslationResult
    fun translateCast(expression: CastExpression): TranslationResult
    fun translateConstantInt(expression: ConstantIntExpression): TranslationResult
    fun translateConstantLong(expression: ConstantLongExpression): TranslationResult
    fun translateConstantString(expression: ConstantStringExpression): TranslationResult
    fun translateFieldAccess(expression: FieldAccessExpression): TranslationResult
    fun translateIdentifier(identifier: Identifier): TranslationResult
    fun translateParenthesized(expression: ParenthesizedExpression): TranslationResult
    fun translatePostfixDecrement(expression: PostfixDecrementExpression): TranslationResult
    fun translatePostfixIncrement(expression: PostfixIncrementExpression): TranslationResult
    fun translateTernary(expression: TernaryExpression): TranslationResult
    fun translateUnary(expression: UnaryExpression): TranslationResult

    override fun visitArrayAccess(expression: ArrayAccessExpression, ctx: TranslationContext): TranslationResult {
        return translateArrayAccess(expression)
    }

    override fun visitAssignment(expression: AssignmentExpression, ctx: TranslationContext): TranslationResult {
        return translateAssignment(expression)
    }

    override fun visitBinary(expression: BinaryExpression, ctx: TranslationContext): TranslationResult {
        return translateBinary(expression)
    }

    override fun visitCall(expression: CallExpression, ctx: TranslationContext): TranslationResult {
        return translateCall(expression)
    }

    override fun visitCast(expression: CastExpression, ctx: TranslationContext): TranslationResult {
        return translateCast(expression)
    }

    override fun visitConstantInt(expression: ConstantIntExpression, ctx: TranslationContext): TranslationResult {
        return translateConstantInt(expression)
    }

    override fun visitConstantLong(expression: ConstantLongExpression, ctx: TranslationContext): TranslationResult {
        return translateConstantLong(expression)
    }

    override fun visitConstantString(expression: ConstantStringExpression, ctx: TranslationContext): TranslationResult {
        return translateConstantString(expression)
    }

    override fun visitFieldAccess(expression: FieldAccessExpression, ctx: TranslationContext): TranslationResult {
        return translateFieldAccess(expression)
    }

    override fun visitIdentifier(identifier: Identifier, ctx: TranslationContext): TranslationResult {
        return translateIdentifier(identifier)
    }

    override fun visitParenthesized(expression: ParenthesizedExpression, ctx: TranslationContext): TranslationResult {
        return translateParenthesized(expression)
    }

    override fun visitPostfixDecrement(expression: PostfixDecrementExpression, ctx: TranslationContext): TranslationResult {
        return translatePostfixDecrement(expression)
    }

    override fun visitPostfixIncrement(expression: PostfixIncrementExpression, ctx: TranslationContext): TranslationResult {
        return translatePostfixIncrement(expression)
    }

    override fun visitTernary(expression: TernaryExpression, ctx: TranslationContext): TranslationResult {
        return translateTernary(expression)
    }

    override fun visitUnary(expression: UnaryExpression, ctx: TranslationContext): TranslationResult {
        return translateUnary(expression)
    }
}

interface StatementTranslationVisitor : AstStatementVisitor<TranslationResult, TranslationContext> {
    fun translate(node: Statement): TranslationResult = node.accept(this, TranslationContext())

    fun translateBlock(statement: BlockStatement): TranslationResult
    fun translateBreak(statement: BreakStatement): TranslationResult
    fun translateCompilationUnit(statement: CompilationUnitStatement): TranslationResult
    fun translateContinue(statement: ContinueStatement): TranslationResult
    fun translateExpression(statement: ExpressionStatement): TranslationResult
    fun translateFor(statement: ForStatement): TranslationResult
    fun translateFunctionDefinition(definition: FunctionDefinitionStatement): TranslationResult
    fun translateGoto(statement: GotoStatement): TranslationResult
    fun translateIfThenElse(statement: IfThenElseStatement): TranslationResult
    fun translateIfThen(statement: IfThenStatement): TranslationResult
    fun translateLabeled(statement: LabeledStatement): TranslationResult
    fun translateReturn(statement: ReturnStatement): TranslationResult
    fun translateSwitch(statement: SwitchStatement): TranslationResult
    fun translateVariableDeclaration(statement: VariableDeclarationStatement): TranslationResult
    fun translateWhile(statement: WhileStatement): TranslationResult

    override fun visitBlock(statement: BlockStatement, ctx: TranslationContext): TranslationResult {
        return translateBlock(statement)
    }

    override fun visitBreak(statement: BreakStatement, ctx: TranslationContext): TranslationResult {
        return translateBreak(statement)
    }

    override fun visitCompilationUnit(statement: CompilationUnitStatement, ctx: TranslationContext): TranslationResult {
        return translateCompilationUnit(statement)
    }

    override fun visitContinue(statement: ContinueStatement, ctx: TranslationContext): TranslationResult {
        return translateContinue(statement)
    }

    override fun visitExpression(statement: ExpressionStatement, ctx: TranslationContext): TranslationResult {
        return translateExpression(statement)
    }

    override fun visitFor(statement: ForStatement, ctx: TranslationContext): TranslationResult {
        return translateFor(statement)
    }

    override fun visitFunctionDefinition(definition: FunctionDefinitionStatement, ctx: TranslationContext): TranslationResult {
        return translateFunctionDefinition(definition)
    }

    override fun visitGoto(statement: GotoStatement, ctx: TranslationContext): TranslationResult {
        return translateGoto(statement)
    }

    override fun visitIfThenElse(statement: IfThenElseStatement, ctx: TranslationContext): TranslationResult {
        return translateIfThenElse(statement)
    }

    override fun visitIfThen(statement: IfThenStatement, ctx: TranslationContext): TranslationResult {
        return translateIfThen(statement)
    }

    override fun visitLabeled(statement: LabeledStatement, ctx: TranslationContext): TranslationResult {
        return translateLabeled(statement)
    }

    override fun visitReturn(statement: ReturnStatement, ctx: TranslationContext): TranslationResult {
        return translateReturn(statement)
    }

    override fun visitSwitch(statement: SwitchStatement, ctx: TranslationContext): TranslationResult {
        return translateSwitch(statement)
    }

    override fun visitVariableDeclaration(statement: VariableDeclarationStatement, ctx: TranslationContext): TranslationResult {
        return translateVariableDeclaration(statement)
    }

    override fun visitWhile(statement: WhileStatement, ctx: TranslationContext): TranslationResult {
        return translateWhile(statement)
    }
}

interface TranslationVisitor :
    StatementTranslationVisitor,
    ExpressionTranslationVisitor
