package org.erwinkok.conjvm.ast

import org.antlr.v4.runtime.ParserRuleContext
import org.erwinkok.conjvm.CBaseVisitor
import org.erwinkok.conjvm.CParser
import org.erwinkok.conjvm.ast.expressions.ArrayAccessExpression
import org.erwinkok.conjvm.ast.expressions.AssignmentExpression
import org.erwinkok.conjvm.ast.expressions.BinaryExpression
import org.erwinkok.conjvm.ast.expressions.BinaryExpressionType
import org.erwinkok.conjvm.ast.expressions.CallExpression
import org.erwinkok.conjvm.ast.expressions.CastExpression
import org.erwinkok.conjvm.ast.expressions.ConstantExpression
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
import org.erwinkok.conjvm.ast.expressions.UnaryType
import org.erwinkok.conjvm.ast.statements.BlockStatement
import org.erwinkok.conjvm.ast.statements.BreakStatement
import org.erwinkok.conjvm.ast.statements.CompilationUnitStatement
import org.erwinkok.conjvm.ast.statements.ContinueStatement
import org.erwinkok.conjvm.ast.statements.ExpressionStatement
import org.erwinkok.conjvm.ast.statements.ForInit
import org.erwinkok.conjvm.ast.statements.ForInitAssignmentExpression
import org.erwinkok.conjvm.ast.statements.ForInitVariableDeclaration
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
import org.erwinkok.conjvm.parser.ErrorReporter

private val ParserRuleContext.location: SourceLocation
    get() {
        return if (this.stop != null) {
            SourceLocation(
                this.start.line,
                this.start.charPositionInLine,
                this.stop.line,
                this.stop.charPositionInLine + (this.stop.text?.length ?: 0),
            )
        } else {
            SourceLocation(
                this.start.line,
                this.start.charPositionInLine,
                0,
                0,
            )
        }
    }

class Value private constructor(val value: Any) {
    inline fun <reified T> cast(): T {
        return value as T
    }

    inline fun <reified T> tryCast(): T? {
        return value as? T
    }

    companion object {
        fun of(value: Any): Value {
            return Value(value)
        }
    }
}

class AstBuilder(val reporter: ErrorReporter) : CBaseVisitor<Value>() {
    override fun visitCompilationUnit(ctx: CParser.CompilationUnitContext): Value {
        val functionDefinitionStatements = ctx.functionDefinition().map { visit(it).cast<FunctionDefinitionStatement>() }
        return Value.of(
            CompilationUnitStatement(
                ctx.location,
                functionDefinitionStatements,
            ),
        )
    }

    override fun visitFunctionDefinition(ctx: CParser.FunctionDefinitionContext): Value {
        return Value.of(
            FunctionDefinitionStatement(
                ctx.location,
                ctx.Identifier().text,
                visit(ctx.block_statement()).cast<BlockStatement>(),
            ),
        )
    }

    //
    // EXPRESSIONS
    //
    override fun visitExpression(ctx: CParser.ExpressionContext): Value {
        return visit(ctx.assignment_expression())
    }

    override fun visitSimpleAssignExpr(ctx: CParser.SimpleAssignExprContext): Value {
        return visit(ctx.conditional_expression())
    }

    override fun visitCompoundAssignExpr(ctx: CParser.CompoundAssignExprContext): Value {
        return Value.of(
            AssignmentExpression(
                ctx.location,
                ctx.assignment_operator().text,
                visit(ctx.unary_expression()).cast<Expression>(),
                visit(ctx.assignment_expression()).cast<Expression>(),
            ),
        )
    }

    override fun visitSimpleConditional(ctx: CParser.SimpleConditionalContext): Value {
        return visit(ctx.logical_or_expression())
    }

    override fun visitCompoundConditional(ctx: CParser.CompoundConditionalContext): Value {
        val testResult = visit(ctx.test).cast<Expression>()
        val thenResult = visit(ctx.thenExpr).cast<Expression>()
        val elseResult = visit(ctx.elseExpr).cast<Expression>()
        return Value.of(
            TernaryExpression(
                ctx.location,
                testResult,
                thenResult,
                elseResult,
            ),
        )
    }

    override fun visitSimpleLogicalOr(ctx: CParser.SimpleLogicalOrContext): Value {
        return visit(ctx.logical_and_expression())
    }

    override fun visitCompoundLogicalOr(ctx: CParser.CompoundLogicalOrContext): Value {
        val leftResult = visit(ctx.left).cast<Expression>()
        val rightResult = visit(ctx.right).cast<Expression>()
        return Value.of(BinaryExpression(ctx.location, BinaryExpressionType.LogicalOr, leftResult, rightResult))
    }

    override fun visitSimpleLogicalAnd(ctx: CParser.SimpleLogicalAndContext): Value {
        return visit(ctx.inclusive_or_expression())
    }

    override fun visitCompoundLogicalAnd(ctx: CParser.CompoundLogicalAndContext): Value {
        val leftResult = visit(ctx.left).cast<Expression>()
        val rightResult = visit(ctx.right).cast<Expression>()
        return Value.of(BinaryExpression(ctx.location, BinaryExpressionType.LogicalAnd, leftResult, rightResult))
    }

    override fun visitSimpleInclusiveOr(ctx: CParser.SimpleInclusiveOrContext): Value {
        return visit(ctx.exclusive_or_expression())
    }

    override fun visitCompoundInclusiveOr(ctx: CParser.CompoundInclusiveOrContext): Value {
        val leftResult = visit(ctx.left).cast<Expression>()
        val rightResult = visit(ctx.right).cast<Expression>()
        return Value.of(BinaryExpression(ctx.location, BinaryExpressionType.InclusiveOr, leftResult, rightResult))
    }

    override fun visitSimpleExclusiveOr(ctx: CParser.SimpleExclusiveOrContext): Value {
        return visit(ctx.and_expression())
    }

    override fun visitCompoundExclusiveOr(ctx: CParser.CompoundExclusiveOrContext): Value {
        val leftResult = visit(ctx.left).cast<Expression>()
        val rightResult = visit(ctx.right).cast<Expression>()
        return Value.of(BinaryExpression(ctx.location, BinaryExpressionType.ExclusiveOr, leftResult, rightResult))
    }

    override fun visitSimpleAnd(ctx: CParser.SimpleAndContext): Value {
        return visit(ctx.equality_expression())
    }

    override fun visitCompoundAnd(ctx: CParser.CompoundAndContext): Value {
        val leftResult = visit(ctx.left).cast<Expression>()
        val rightResult = visit(ctx.right).cast<Expression>()
        return Value.of(BinaryExpression(ctx.location, BinaryExpressionType.And, leftResult, rightResult))
    }

    override fun visitSimpleEquality(ctx: CParser.SimpleEqualityContext): Value {
        return visit(ctx.relational_expression())
    }

    override fun visitEqualityEquals(ctx: CParser.EqualityEqualsContext): Value {
        val leftResult = visit(ctx.left).cast<Expression>()
        val rightResult = visit(ctx.right).cast<Expression>()
        return Value.of(BinaryExpression(ctx.location, BinaryExpressionType.Equals, leftResult, rightResult))
    }

    override fun visitEqualityNotEquals(ctx: CParser.EqualityNotEqualsContext): Value {
        val leftResult = visit(ctx.left).cast<Expression>()
        val rightResult = visit(ctx.right).cast<Expression>()
        return Value.of(BinaryExpression(ctx.location, BinaryExpressionType.NotEquals, leftResult, rightResult))
    }

    override fun visitSimpleRelational(ctx: CParser.SimpleRelationalContext): Value {
        return visit(ctx.shift_expression())
    }

    override fun visitRelationalLess(ctx: CParser.RelationalLessContext): Value {
        val leftResult = visit(ctx.left).cast<Expression>()
        val rightResult = visit(ctx.right).cast<Expression>()
        return Value.of(BinaryExpression(ctx.location, BinaryExpressionType.Less, leftResult, rightResult))
    }

    override fun visitRelationalGreater(ctx: CParser.RelationalGreaterContext): Value {
        val leftResult = visit(ctx.left).cast<Expression>()
        val rightResult = visit(ctx.right).cast<Expression>()
        return Value.of(BinaryExpression(ctx.location, BinaryExpressionType.Greater, leftResult, rightResult))
    }

    override fun visitRelationalLessOrEqual(ctx: CParser.RelationalLessOrEqualContext): Value {
        val leftResult = visit(ctx.left).cast<Expression>()
        val rightResult = visit(ctx.right).cast<Expression>()
        return Value.of(BinaryExpression(ctx.location, BinaryExpressionType.LessOrEqual, leftResult, rightResult))
    }

    override fun visitRelationalGreaterOrEqual(ctx: CParser.RelationalGreaterOrEqualContext): Value {
        val leftResult = visit(ctx.left).cast<Expression>()
        val rightResult = visit(ctx.right).cast<Expression>()
        return Value.of(BinaryExpression(ctx.location, BinaryExpressionType.GreaterOrEqual, leftResult, rightResult))
    }

    override fun visitSimpleShift(ctx: CParser.SimpleShiftContext): Value {
        return visit(ctx.additive_expression())
    }

    override fun visitShiftLeft(ctx: CParser.ShiftLeftContext): Value {
        val leftResult = visit(ctx.left).cast<Expression>()
        val rightResult = visit(ctx.right).cast<Expression>()
        return Value.of(BinaryExpression(ctx.location, BinaryExpressionType.ShiftLeft, leftResult, rightResult))
    }

    override fun visitShiftRight(ctx: CParser.ShiftRightContext): Value {
        val leftResult = visit(ctx.left).cast<Expression>()
        val rightResult = visit(ctx.right).cast<Expression>()
        return Value.of(BinaryExpression(ctx.location, BinaryExpressionType.ShiftRight, leftResult, rightResult))
    }

    override fun visitSimpleAdditive(ctx: CParser.SimpleAdditiveContext): Value {
        return visit(ctx.multiplicative_expression())
    }

    override fun visitAdditiveAdd(ctx: CParser.AdditiveAddContext): Value {
        val leftResult = visit(ctx.left).cast<Expression>()
        val rightResult = visit(ctx.right).cast<Expression>()
        return Value.of(BinaryExpression(ctx.location, BinaryExpressionType.Add, leftResult, rightResult))
    }

    override fun visitAdditiveSubtract(ctx: CParser.AdditiveSubtractContext): Value {
        val leftResult = visit(ctx.left).cast<Expression>()
        val rightResult = visit(ctx.right).cast<Expression>()
        return Value.of(BinaryExpression(ctx.location, BinaryExpressionType.Subtract, leftResult, rightResult))
    }

    override fun visitSimpleMultiplicative(ctx: CParser.SimpleMultiplicativeContext): Value {
        return visit(ctx.cast_expression())
    }

    override fun visitMultiplicativeMultiply(ctx: CParser.MultiplicativeMultiplyContext): Value {
        val leftResult = visit(ctx.left).cast<Expression>()
        val rightResult = visit(ctx.right).cast<Expression>()
        return Value.of(BinaryExpression(ctx.location, BinaryExpressionType.Multiply, leftResult, rightResult))
    }

    override fun visitMultiplicativeDivide(ctx: CParser.MultiplicativeDivideContext): Value {
        val leftResult = visit(ctx.left).cast<Expression>()
        val rightResult = visit(ctx.right).cast<Expression>()
        return Value.of(BinaryExpression(ctx.location, BinaryExpressionType.Divide, leftResult, rightResult))
    }

    override fun visitMultiplicativeModulo(ctx: CParser.MultiplicativeModuloContext): Value {
        val leftResult = visit(ctx.left).cast<Expression>()
        val rightResult = visit(ctx.right).cast<Expression>()
        return Value.of(BinaryExpression(ctx.location, BinaryExpressionType.Modulo, leftResult, rightResult))
    }

    override fun visitSimpleCast(ctx: CParser.SimpleCastContext): Value {
        return visit(ctx.unary_expression())
    }

    override fun visitCastExpr(ctx: CParser.CastExprContext): Value {
        val typeName = visit(ctx.type_name()).cast<List<String>>()
        val variableType = typeName.firstOrNull()
        requireNotNull(variableType) { "Variable type $typeName must be set for cast" }
        val nodeResult = visit(ctx.cast_expression()).cast<Expression>()
        return Value.of(CastExpression(ctx.location, VariableType.parse(variableType), nodeResult))
    }

    override fun visitSimpleUnary(ctx: CParser.SimpleUnaryContext): Value {
        return visit(ctx.postfix_expression())
    }

    override fun visitUnaryAddress(ctx: CParser.UnaryAddressContext): Value {
        val result = visit(ctx.cast_expression()).cast<Expression>()
        return Value.of(UnaryExpression(ctx.location, UnaryType.Address, result))
    }

    override fun visitUnaryIndirection(ctx: CParser.UnaryIndirectionContext): Value {
        val result = visit(ctx.cast_expression()).cast<Expression>()
        return Value.of(UnaryExpression(ctx.location, UnaryType.Indirection, result))
    }

    override fun visitUnaryPlus(ctx: CParser.UnaryPlusContext): Value {
        val result = visit(ctx.cast_expression()).cast<Expression>()
        return Value.of(UnaryExpression(ctx.location, UnaryType.Plus, result))
    }

    override fun visitUnaryMinus(ctx: CParser.UnaryMinusContext): Value {
        val result = visit(ctx.cast_expression()).cast<Expression>()
        return Value.of(UnaryExpression(ctx.location, UnaryType.Minus, result))
    }

    override fun visitUnaryBitwiseNot(ctx: CParser.UnaryBitwiseNotContext): Value {
        val result = visit(ctx.cast_expression()).cast<Expression>()
        return Value.of(UnaryExpression(ctx.location, UnaryType.BitwiseNot, result))
    }

    override fun visitUnaryLogicalNot(ctx: CParser.UnaryLogicalNotContext): Value {
        val result = visit(ctx.cast_expression()).cast<Expression>()
        return Value.of(UnaryExpression(ctx.location, UnaryType.LogicalNot, result))
    }

    override fun visitUnaryPlusPlus(ctx: CParser.UnaryPlusPlusContext): Value {
        val result = visit(ctx.cast_expression()).cast<Expression>()
        return Value.of(UnaryExpression(ctx.location, UnaryType.PlusPlus, result))
    }

    override fun visitUnaryMinusMinus(ctx: CParser.UnaryMinusMinusContext): Value {
        val result = visit(ctx.cast_expression()).cast<Expression>()
        return Value.of(UnaryExpression(ctx.location, UnaryType.MinusMinus, result))
    }

    override fun visitPostfixPrimary(ctx: CParser.PostfixPrimaryContext): Value {
        return visit(ctx.primary_expression())
    }

    override fun visitPostfixArrayAccess(ctx: CParser.PostfixArrayAccessContext): Value {
        val base = visit(ctx.postfix_expression()).cast<Expression>()
        return Value.of(ArrayAccessExpression(ctx.location, base, visit(ctx.expression()).cast<Expression>()))
    }

    override fun visitPostfixCall(ctx: CParser.PostfixCallContext): Value {
        val argumentList = ctx.argument_list()?.let { visit(it).cast<List<Expression>>() } ?: emptyList()
        return Value.of(CallExpression(ctx.location, ctx.id.text, argumentList))
    }

    override fun visitPostfixFieldAccess(ctx: CParser.PostfixFieldAccessContext): Value {
        val base = visit(ctx.postfix_expression()).cast<Expression>()
        return Value.of(FieldAccessExpression(ctx.location, base, ctx.Identifier().text))
    }

    override fun visitPostfixPtrFieldAccess(ctx: CParser.PostfixPtrFieldAccessContext): Value {
        val base = visit(ctx.postfix_expression()).cast<Expression>()
        val deref = UnaryExpression(ctx.location, UnaryType.Indirection, base)
        return Value.of(FieldAccessExpression(ctx.location, deref, ctx.Identifier().text))
    }

    override fun visitPostfixPlusPlus(ctx: CParser.PostfixPlusPlusContext): Value {
        val expression = visit(ctx.postfix_expression()).cast<Expression>()
        return Value.of(PostfixPlusPlusExpression(ctx.location, expression))
    }

    override fun visitPostfixMinusMinus(ctx: CParser.PostfixMinusMinusContext): Value {
        val expression = visit(ctx.postfix_expression()).cast<Expression>()
        return Value.of(PostfixMinusMinusExpression(ctx.location, expression))
    }

    override fun visitPrimaryId(ctx: CParser.PrimaryIdContext): Value {
        return Value.of(Identifier(ctx.location, ctx.Identifier().text))
    }

    override fun visitPrimaryConstant(ctx: CParser.PrimaryConstantContext): Value {
        return Value.of(parseConstant(ctx.location, ctx.Constant().text))
    }

    override fun visitPrimaryStringLiteral(ctx: CParser.PrimaryStringLiteralContext): Value {
        return Value.of(ConstantStringExpression(ctx.location, ctx.StringLiteral().text))
    }

    override fun visitPrimaryParenthesized(ctx: CParser.PrimaryParenthesizedContext): Value {
        return Value.of(ParenthesizedExpression(ctx.location, visit(ctx.expression()).cast<Expression>()))
    }

    override fun visitArgument_list(ctx: CParser.Argument_listContext): Value {
        return Value.of(ctx.assignment_expression().map { visit(it).cast<Expression>() })
    }

    //
    // STATEMENTS
    //
    override fun visitStatementLabel(ctx: CParser.StatementLabelContext): Value {
        return visit(ctx.labeled_statement())
    }

    override fun visitStatementVarDecl(ctx: CParser.StatementVarDeclContext): Value {
        return visit(ctx.variable_declaration())
    }

    override fun visitStatementEmbedded(ctx: CParser.StatementEmbeddedContext): Value {
        return visit(ctx.embedded_statement())
    }

    override fun visitStatementBlock(ctx: CParser.StatementBlockContext): Value {
        return visit(ctx.block_statement())
    }

    override fun visitStatementExpression(ctx: CParser.StatementExpressionContext): Value {
        return visit(ctx.expression_statement())
    }

    override fun visitStatementIfThen(ctx: CParser.StatementIfThenContext): Value {
        return visit(ctx.if_then_statement())
    }

    override fun visitStatementIfThenElse(ctx: CParser.StatementIfThenElseContext): Value {
        return visit(ctx.if_then_else_statement())
    }

    override fun visitStatementWhile(ctx: CParser.StatementWhileContext): Value {
        return visit(ctx.while_statement())
    }

    override fun visitStatementFor(ctx: CParser.StatementForContext): Value {
        return visit(ctx.for_statement())
    }

    override fun visitStatementSwitch(ctx: CParser.StatementSwitchContext): Value {
        return visit(ctx.switch_statement())
    }

    override fun visitStatementBreak(ctx: CParser.StatementBreakContext): Value {
        return visit(ctx.break_statement())
    }

    override fun visitStatementContinue(ctx: CParser.StatementContinueContext): Value {
        return visit(ctx.continue_statement())
    }

    override fun visitStatementGoto(ctx: CParser.StatementGotoContext): Value {
        return visit(ctx.goto_statement())
    }

    override fun visitStatementReturn(ctx: CParser.StatementReturnContext): Value {
        return visit(ctx.return_statement())
    }

    override fun visitBlock_statement(ctx: CParser.Block_statementContext): Value {
        return Value.of(
            BlockStatement(
                ctx.location,
                ctx.statement().map { visit(it).cast<Statement>() },
            ),
        )
    }

    override fun visitLabeled_statement(ctx: CParser.Labeled_statementContext): Value {
        return Value.of(
            LabeledStatement(
                ctx.location,
                ctx.Identifier().text,
                visit(ctx.statement()).cast<Statement>(),
            ),
        )
    }

    override fun visitExprStatAssign(ctx: CParser.ExprStatAssignContext): Value {
        return Value.of(ExpressionStatement(ctx.location, visit(ctx.expression()).cast<Expression>()))
    }

    override fun visitIf_then_statement(ctx: CParser.If_then_statementContext): Value {
        return Value.of(
            IfThenStatement(
                ctx.location,
                visit(ctx.test).cast<Expression>(),
                visit(ctx.thenExpr).toBlockStatement(ctx.location),
            ),
        )
    }

    override fun visitIf_then_else_statement(ctx: CParser.If_then_else_statementContext): Value {
        return Value.of(
            IfThenElseStatement(
                ctx.location,
                visit(ctx.test).cast<Expression>(),
                visit(ctx.thenExpr).toBlockStatement(ctx.location),
                visit(ctx.elseExpr).toBlockStatement(ctx.location),
            ),
        )
    }

    override fun visitSwitch_statement(ctx: CParser.Switch_statementContext): Value {
        val (cases, default) = ctx.switch_section().map { visit(it) }.partition { it.tryCast<SwitchCaseStatement>() != null }
        require(default.size <= 1) { "There must be one or zero default cases in a switch statement" }
        val defaultCase = default.firstOrNull()?.tryCast<SwitchDefaultStatement>()
        return Value.of(
            SwitchStatement(
                ctx.location,
                visit(ctx.expression()).cast<Expression>(),
                cases.map { it.cast<SwitchCaseStatement>() },
                defaultCase,
            ),
        )
    }

    override fun visitSwitchSectionCase(ctx: CParser.SwitchSectionCaseContext): Value {
        return Value.of(
            SwitchCaseStatement(
                ctx.location,
                visit(ctx.expression()).cast<ConstantExpression>(),
                BlockStatement(ctx.location, ctx.statement().map { visit(it).cast<Statement>() }),
            ),
        )
    }

    override fun visitSwitchSectionDefault(ctx: CParser.SwitchSectionDefaultContext): Value {
        return Value.of(
            SwitchDefaultStatement(
                ctx.location,
                BlockStatement(ctx.location, ctx.statement().map { visit(it).cast<Statement>() }),
            ),
        )
    }

    override fun visitWhile_statement(ctx: CParser.While_statementContext): Value {
        return Value.of(
            WhileStatement(
                ctx.location,
                visit(ctx.test).cast<Expression>(),
                visit(ctx.statements).toBlockStatement(ctx.location),
            ),
        )
    }

    override fun visitFor_statement(ctx: CParser.For_statementContext): Value {
        return Value.of(
            ForStatement(
                ctx.location,
                ctx.init?.let { visit(it).cast<ForInit>() },
                ctx.test?.let { visit(ctx.test).cast<Expression>() },
                ctx.iterator?.let { visit(it).cast<List<Expression>>() },
                visit(ctx.embedded_statement()).toBlockStatement(ctx.location),
            ),
        )
    }

    override fun visitForInitAssignmentExpr(ctx: CParser.ForInitAssignmentExprContext): Value {
        return Value.of(ForInitAssignmentExpression(visit(ctx.argument_list()).cast<List<AssignmentExpression>>()))
    }

    override fun visitForInitVarDecl(ctx: CParser.ForInitVarDeclContext): Value {
        return Value.of(
            ForInitVariableDeclaration(
                VariableDeclarationStatement(
                    ctx.location,
                    ctx.declaration_specifiers().text?.let { VariableType.parse(it) },
                    visit(ctx.init_declarator_list()).cast<List<VariableDeclarator>>(),
                ),
            ),
        )
    }

    override fun visitFor_expression(ctx: CParser.For_expressionContext): Value {
        return Value.of(ctx.assignment_expression().map { visit(it).cast<Expression>() })
    }

    override fun visitBreak_statement(ctx: CParser.Break_statementContext): Value {
        return Value.of(BreakStatement(ctx.location))
    }

    override fun visitContinue_statement(ctx: CParser.Continue_statementContext): Value {
        return Value.of(ContinueStatement(ctx.location))
    }

    override fun visitGoto_statement(ctx: CParser.Goto_statementContext): Value {
        return Value.of(GotoStatement(ctx.location, ctx.Identifier().text))
    }

    override fun visitReturn_statement(ctx: CParser.Return_statementContext): Value {
        return Value.of(
            ReturnStatement(
                ctx.location,
                ctx.expression()?.let { visit(it).cast<Expression>() },
            ),
        )
    }

    //
    // VARIABLE DECLARATION
    //
    override fun visitVariable_declaration(ctx: CParser.Variable_declarationContext): Value {
        // Currently, only VariableType is supported. Other declaration specifiers are ignored.
        val declarationSpecifiers = visit(ctx.declaration_specifiers()).cast<List<DeclarationSpecifier>>()
        val variableType = declarationSpecifiers.filterIsInstance<VariableType>().firstOrNull()
        return Value.of(
            VariableDeclarationStatement(
                ctx.location,
                variableType,
                visit(ctx.init_declarator_list()).cast<List<VariableDeclarator>>(),
            ),
        )
    }

    override fun visitDeclaration_specifiers(ctx: CParser.Declaration_specifiersContext): Value {
        return Value.of(ctx.declaration_specifier().map { visit(it).cast<DeclarationSpecifier>() })
    }

    override fun visitStorageClassSpec(ctx: CParser.StorageClassSpecContext): Value {
        reporter.reportWarning(ctx.location, "Storage class specifier '${ctx.text}' is not supported.")
        return Value.of(DeclarationSpecifier.NONE)
    }

    override fun visitDeclSpecTypeSpec(ctx: CParser.DeclSpecTypeSpecContext): Value {
        return Value.of(VariableType.parse(ctx.text))
    }

    override fun visitDeclSpecTypeQual(ctx: CParser.DeclSpecTypeQualContext): Value {
        reporter.reportWarning(ctx.location, "Type qualifier '${ctx.text}' is not supported.")
        return Value.of(DeclarationSpecifier.NONE)
    }

    override fun visitDeclSpecFuncSpec(ctx: CParser.DeclSpecFuncSpecContext): Value {
        reporter.reportWarning(ctx.location, "Function specifier '${ctx.text}' is not supported.")
        return Value.of(DeclarationSpecifier.NONE)
    }

    override fun visitInit_declarator_list(ctx: CParser.Init_declarator_listContext): Value {
        return Value.of(ctx.init_declarator().map { visit(it).cast<VariableDeclarator>() })
    }

    override fun visitInit_declarator(ctx: CParser.Init_declaratorContext): Value {
        return Value.of(
            VariableDeclarator(
                ctx.location,
                visit(ctx.declarator()).cast<Declarator>(),
                ctx.initializer()?.let { visit(it).cast<Expression>() },
            ),
        )
    }

    override fun visitSpecifier_qualifier_list(ctx: CParser.Specifier_qualifier_listContext): Value {
        val result = ArrayList<String>()
        if (ctx.type_specifier() != null) {
            result.add(ctx.type_specifier().text)
        } else {
            result.add(ctx.type_qualifier().text)
        }
        if (ctx.specifier_qualifier_list() != null) {
            result.addAll(visit(ctx.specifier_qualifier_list()).cast<List<String>>())
        }
        return Value.of(result)
    }

    override fun visitDeclarator(ctx: CParser.DeclaratorContext): Value {
        return Value.of(Declarator(ctx.location, ctx.pointer() != null, ctx.Identifier().text))
    }

    override fun visitType_name(ctx: CParser.Type_nameContext): Value {
        return visit(ctx.specifier_qualifier_list())
    }

    override fun visitInitializer(ctx: CParser.InitializerContext): Value {
        return visit(ctx.assignment_expression())
    }

    private fun Value.toBlockStatement(location: SourceLocation): BlockStatement {
        return this.tryCast<BlockStatement>() ?: BlockStatement(location, listOf(this.cast<Statement>()))
    }

    private fun parseConstant(location: SourceLocation, input: String): ConstantExpression {
        if (input.startsWith("0x", ignoreCase = true)) {
            val hexValue = input.substring(2)
            hexValue.toIntOrNull(radix = 16)?.let { return ConstantIntExpression(location, it) }
            hexValue.toLongOrNull(radix = 16)?.let { return ConstantLongExpression(location, it) }
        }
        input.toIntOrNull()?.let { return ConstantIntExpression(location, it) }
        input.toLongOrNull()?.let { return ConstantLongExpression(location, it) }
        error("Could not parse constant: $input")
    }
}
