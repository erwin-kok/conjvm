package org.erwinkok.conjvm.ast

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
import org.erwinkok.conjvm.ast.expressions.PostfixMinusMinusExpression
import org.erwinkok.conjvm.ast.expressions.PostfixPlusPlusExpression
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

interface AstExpressionVisitor<out R, in C> {
    fun visit(node: Expression, ctx: C): R = node.accept(this, ctx)

    fun visitArrayAccess(expression: ArrayAccessExpression, ctx: C): R
    fun visitAssignment(expression: AssignmentExpression, ctx: C): R
    fun visitBinary(expression: BinaryExpression, ctx: C): R
    fun visitCall(expression: CallExpression, ctx: C): R
    fun visitCast(expression: CastExpression, ctx: C): R
    fun visitConstantInt(expression: ConstantIntExpression, ctx: C): R
    fun visitConstantLong(expression: ConstantLongExpression, ctx: C): R
    fun visitConstantString(expression: ConstantStringExpression, ctx: C): R
    fun visitFieldAccess(expression: FieldAccessExpression, ctx: C): R
    fun visitIdentifier(identifier: Identifier, ctx: C): R
    fun visitParenthesized(expression: ParenthesizedExpression, ctx: C): R
    fun visitPostfixMinusMinus(expression: PostfixMinusMinusExpression, ctx: C): R
    fun visitPostfixPlusPlus(expression: PostfixPlusPlusExpression, ctx: C): R
    fun visitTernary(expression: TernaryExpression, ctx: C): R
    fun visitUnary(expression: UnaryExpression, ctx: C): R
}

interface AstStatementVisitor<out R, in C> {
    fun visit(node: Statement, ctx: C): R = node.accept(this, ctx)

    fun visitBlock(statement: BlockStatement, ctx: C): R
    fun visitBreak(statement: BreakStatement, ctx: C): R
    fun visitCompilationUnit(statement: CompilationUnitStatement, ctx: C): R
    fun visitContinue(statement: ContinueStatement, ctx: C): R
    fun visitExpression(statement: ExpressionStatement, ctx: C): R
    fun visitFor(statement: ForStatement, ctx: C): R
    fun visitFunctionDefinition(definition: FunctionDefinitionStatement, ctx: C): R
    fun visitGoto(statement: GotoStatement, ctx: C): R
    fun visitIfThenElse(statement: IfThenElseStatement, ctx: C): R
    fun visitIfThen(statement: IfThenStatement, ctx: C): R
    fun visitLabeled(statement: LabeledStatement, ctx: C): R
    fun visitReturn(statement: ReturnStatement, ctx: C): R
    fun visitSwitch(statement: SwitchStatement, ctx: C): R
    fun visitVariableDeclaration(statement: VariableDeclarationStatement, ctx: C): R
    fun visitWhile(statement: WhileStatement, ctx: C): R
}

interface AstVisitor<out R, in C> :
    AstExpressionVisitor<R, C>,
    AstStatementVisitor<R, C>
