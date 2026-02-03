package org.erwinkok.conjvm.ast

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

interface AstExpressionVisitor<out R> {
    fun visit(node: Expression): R = node.accept(this)

    fun visitArrayAccess(expression: ArrayAccessExpression): R
    fun visitAssignment(expression: AssignmentExpression): R
    fun visitBinary(expression: BinaryExpression): R
    fun visitCall(expression: CallExpression): R
    fun visitCast(expression: CastExpression): R
    fun visitCharacterLiteral(expression: CharacterLiteralExpression): R
    fun visitFieldAccess(expression: FieldAccessExpression): R
    fun visitFloatLiteral(expression: FloatLiteralExpression): R
    fun visitIntegerLiteral(expression: IntegerLiteralExpression): R
    fun visitParenthesized(expression: ParenthesizedExpression): R
    fun visitPostfixDecrement(expression: PostfixDecrementExpression): R
    fun visitPostfixIncrement(expression: PostfixIncrementExpression): R
    fun visitStringLiteral(expression: StringLiteralExpression): R
    fun visitTernary(expression: TernaryExpression): R
    fun visitUnary(expression: UnaryExpression): R
    fun visitVariableReference(variableReference: VariableReference): R
}

interface AstStatementVisitor<out R> {
    fun visit(node: Statement): R = node.accept(this)

    fun visitBlock(statement: BlockStatement): R
    fun visitBreak(statement: BreakStatement): R
    fun visitCompilationUnit(statement: CompilationUnitStatement): R
    fun visitContinue(statement: ContinueStatement): R
    fun visitDoWhile(statement: DoWhileStatement): R
    fun visitExpression(statement: ExpressionStatement): R
    fun visitFor(statement: ForStatement): R
    fun visitFunctionDefinition(definition: FunctionDefinitionStatement): R
    fun visitGoto(statement: GotoStatement): R
    fun visitIfThen(statement: IfThenStatement): R
    fun visitIfThenElse(statement: IfThenElseStatement): R
    fun visitLabeled(statement: LabeledStatement): R
    fun visitReturn(statement: ReturnStatement): R
    fun visitSwitch(statement: SwitchStatement): R
    fun visitVariableDeclaration(statement: VariableDeclarationStatement): R
    fun visitWhile(statement: WhileStatement): R
}

interface AstVisitor<out R> :
    AstExpressionVisitor<R>,
    AstStatementVisitor<R>
