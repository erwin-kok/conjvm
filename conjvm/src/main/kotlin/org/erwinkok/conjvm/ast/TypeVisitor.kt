package org.erwinkok.conjvm.ast

import org.erwinkok.conjvm.ast.expressions.ArrayAccessExpression
import org.erwinkok.conjvm.ast.expressions.AssignmentExpression
import org.erwinkok.conjvm.ast.expressions.BinaryExpression
import org.erwinkok.conjvm.ast.expressions.CallExpression
import org.erwinkok.conjvm.ast.expressions.CastExpression
import org.erwinkok.conjvm.ast.expressions.ConstantIntExpression
import org.erwinkok.conjvm.ast.expressions.ConstantLongExpression
import org.erwinkok.conjvm.ast.expressions.ConstantStringExpression
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
import org.erwinkok.conjvm.ast.statements.SwitchStatement
import org.erwinkok.conjvm.ast.statements.VariableDeclarationStatement
import org.erwinkok.conjvm.ast.statements.WhileStatement

class TypeContext

class TypeVisitor :
    AstStatementVisitor<Unit, TypeContext>,
    AstExpressionVisitor<Type, TypeContext> {
    private var currentReturn = Type.Void

    fun check(compilationUnitStatement: CompilationUnitStatement) {
        compilationUnitStatement.functionDefinitions.forEach {
            declareFunction(it)
        }
    }

    private fun declareFunction(function: FunctionDefinitionStatement) {
//        Scope.current.define(Symbol(function.name, Type.Func()))
    }

    override fun visitBlock(statement: BlockStatement, ctx: TypeContext) {
        TODO("Not yet implemented")
    }

    override fun visitBreak(statement: BreakStatement, ctx: TypeContext) {
        TODO("Not yet implemented")
    }

    override fun visitCompilationUnit(statement: CompilationUnitStatement, ctx: TypeContext) {
        TODO("Not yet implemented")
    }

    override fun visitContinue(statement: ContinueStatement, ctx: TypeContext) {
        TODO("Not yet implemented")
    }

    override fun visitExpression(statement: ExpressionStatement, ctx: TypeContext) {
        TODO("Not yet implemented")
    }

    override fun visitFor(statement: ForStatement, ctx: TypeContext) {
        TODO("Not yet implemented")
    }

    override fun visitFunctionDefinition(definition: FunctionDefinitionStatement, ctx: TypeContext) {
        TODO("Not yet implemented")
    }

    override fun visitGoto(statement: GotoStatement, ctx: TypeContext) {
        TODO("Not yet implemented")
    }

    override fun visitIfThenElse(statement: IfThenElseStatement, ctx: TypeContext) {
        TODO("Not yet implemented")
    }

    override fun visitIfThen(statement: IfThenStatement, ctx: TypeContext) {
        TODO("Not yet implemented")
    }

    override fun visitLabeled(statement: LabeledStatement, ctx: TypeContext) {
        TODO("Not yet implemented")
    }

    override fun visitReturn(statement: ReturnStatement, ctx: TypeContext) {
        TODO("Not yet implemented")
    }

    override fun visitSwitch(statement: SwitchStatement, ctx: TypeContext) {
        TODO("Not yet implemented")
    }

    override fun visitVariableDeclaration(statement: VariableDeclarationStatement, ctx: TypeContext) {
        TODO("Not yet implemented")
    }

    override fun visitWhile(statement: WhileStatement, ctx: TypeContext) {
        TODO("Not yet implemented")
    }

    override fun visitArrayAccess(expression: ArrayAccessExpression, ctx: TypeContext): Type {
        TODO("Not yet implemented")
    }

    override fun visitAssignment(expression: AssignmentExpression, ctx: TypeContext): Type {
        TODO("Not yet implemented")
    }

    override fun visitBinary(expression: BinaryExpression, ctx: TypeContext): Type {
        TODO("Not yet implemented")
    }

    override fun visitCall(expression: CallExpression, ctx: TypeContext): Type {
        TODO("Not yet implemented")
    }

    override fun visitCast(expression: CastExpression, ctx: TypeContext): Type {
        TODO("Not yet implemented")
    }

    override fun visitConstantInt(expression: ConstantIntExpression, ctx: TypeContext): Type {
        TODO("Not yet implemented")
    }

    override fun visitConstantLong(expression: ConstantLongExpression, ctx: TypeContext): Type {
        TODO("Not yet implemented")
    }

    override fun visitConstantString(expression: ConstantStringExpression, ctx: TypeContext): Type {
        TODO("Not yet implemented")
    }

    override fun visitFieldAccess(expression: FieldAccessExpression, ctx: TypeContext): Type {
        TODO("Not yet implemented")
    }

    override fun visitIdentifier(identifier: Identifier, ctx: TypeContext): Type {
        TODO("Not yet implemented")
    }

    override fun visitParenthesized(expression: ParenthesizedExpression, ctx: TypeContext): Type {
        TODO("Not yet implemented")
    }

    override fun visitPostfixDecrement(expression: PostfixDecrementExpression, ctx: TypeContext): Type {
        TODO("Not yet implemented")
    }

    override fun visitPostfixIncrement(expression: PostfixIncrementExpression, ctx: TypeContext): Type {
        TODO("Not yet implemented")
    }

    override fun visitTernary(expression: TernaryExpression, ctx: TypeContext): Type {
        TODO("Not yet implemented")
    }

    override fun visitUnary(expression: UnaryExpression, ctx: TypeContext): Type {
        TODO("Not yet implemented")
    }
}
