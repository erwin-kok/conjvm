package org.erwinkok.conjvm.ast

import org.antlr.v4.runtime.ParserRuleContext
import org.erwinkok.conjvm.CBaseVisitor
import org.erwinkok.conjvm.CParser
import org.erwinkok.conjvm.ast.expressions.ArrayAccessExpression
import org.erwinkok.conjvm.ast.expressions.AssignmentExpression
import org.erwinkok.conjvm.ast.expressions.AssignmentExpressionType
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
import org.erwinkok.conjvm.ast.expressions.PostfixDecrementExpression
import org.erwinkok.conjvm.ast.expressions.PostfixIncrementExpression
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
        val varDecls = mutableListOf<VariableDeclarationStatement>()
        val funcDefs = mutableListOf<FunctionDefinitionStatement>()
        for (decl in ctx.external_declaration()) {
            when (decl) {
                is CParser.DeclrVarDeclContext -> varDecls.add(visit(decl).cast<VariableDeclarationStatement>())
                is CParser.DeclrFunctionDefContext -> funcDefs.add(visit(decl).cast<FunctionDefinitionStatement>())
                is CParser.DeclrStrayContext -> {} // ignore stray semicolon
            }
        }
        return Value.of(
            CompilationUnitStatement(
                ctx.location,
                varDecls,
                funcDefs,
            ),
        )
    }

    override fun visitFunction_definition(ctx: CParser.Function_definitionContext): Value {
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
                AssignmentExpressionType.parse(ctx.assignment_operator().text),
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

    override fun visitLogical_or_expression(ctx: CParser.Logical_or_expressionContext): Value {
        return Value.of(
            ctx.op.zip(ctx.right)
                .fold(visit(ctx.left).cast<Expression>()) { acc, (op, right) ->
                    BinaryExpression(
                        ctx.location,
                        BinaryExpressionType.parse(op.text),
                        acc,
                        visit(right).cast<Expression>(),
                    )
                },
        )
    }

    override fun visitLogical_and_expression(ctx: CParser.Logical_and_expressionContext): Value {
        return Value.of(
            ctx.op.zip(ctx.right)
                .fold(visit(ctx.left).cast<Expression>()) { acc, (op, right) ->
                    BinaryExpression(
                        ctx.location,
                        BinaryExpressionType.parse(op.text),
                        acc,
                        visit(right).cast<Expression>(),
                    )
                },
        )
    }

    override fun visitInclusive_or_expression(ctx: CParser.Inclusive_or_expressionContext): Value {
        return Value.of(
            ctx.op.zip(ctx.right)
                .fold(visit(ctx.left).cast<Expression>()) { acc, (op, right) ->
                    BinaryExpression(
                        ctx.location,
                        BinaryExpressionType.parse(op.text),
                        acc,
                        visit(right).cast<Expression>(),
                    )
                },
        )
    }

    override fun visitExclusive_or_expression(ctx: CParser.Exclusive_or_expressionContext): Value {
        return Value.of(
            ctx.op.zip(ctx.right)
                .fold(visit(ctx.left).cast<Expression>()) { acc, (op, right) ->
                    BinaryExpression(
                        ctx.location,
                        BinaryExpressionType.parse(op.text),
                        acc,
                        visit(right).cast<Expression>(),
                    )
                },
        )
    }

    override fun visitAnd_expression(ctx: CParser.And_expressionContext): Value {
        return Value.of(
            ctx.op.zip(ctx.right)
                .fold(visit(ctx.left).cast<Expression>()) { acc, (op, right) ->
                    BinaryExpression(
                        ctx.location,
                        BinaryExpressionType.parse(op.text),
                        acc,
                        visit(right).cast<Expression>(),
                    )
                },
        )
    }

    override fun visitEquality_expression(ctx: CParser.Equality_expressionContext): Value {
        return Value.of(
            ctx.op.zip(ctx.right)
                .fold(visit(ctx.left).cast<Expression>()) { acc, (op, right) ->
                    BinaryExpression(
                        ctx.location,
                        BinaryExpressionType.parse(op.text),
                        acc,
                        visit(right).cast<Expression>(),
                    )
                },
        )
    }

    override fun visitRelational_expression(ctx: CParser.Relational_expressionContext): Value {
        return Value.of(
            ctx.op.zip(ctx.right)
                .fold(visit(ctx.left).cast<Expression>()) { acc, (op, right) ->
                    BinaryExpression(
                        ctx.location,
                        BinaryExpressionType.parse(op.text),
                        acc,
                        visit(right).cast<Expression>(),
                    )
                },
        )
    }

    override fun visitShift_expression(ctx: CParser.Shift_expressionContext): Value {
        return Value.of(
            ctx.op.zip(ctx.right)
                .fold(visit(ctx.left).cast<Expression>()) { acc, (op, right) ->
                    BinaryExpression(
                        ctx.location,
                        BinaryExpressionType.parse(op.text),
                        acc,
                        visit(right).cast<Expression>(),
                    )
                },
        )
    }

    override fun visitAdditive_expression(ctx: CParser.Additive_expressionContext): Value {
        return Value.of(
            ctx.op.zip(ctx.right)
                .fold(visit(ctx.left).cast<Expression>()) { acc, (op, right) ->
                    BinaryExpression(
                        ctx.location,
                        BinaryExpressionType.parse(op.text),
                        acc,
                        visit(right).cast<Expression>(),
                    )
                },
        )
    }

    override fun visitMultiplicative_expression(ctx: CParser.Multiplicative_expressionContext): Value {
        return Value.of(
            ctx.op.zip(ctx.right)
                .fold(visit(ctx.left).cast<Expression>()) { acc, (op, right) ->
                    BinaryExpression(
                        ctx.location,
                        BinaryExpressionType.parse(op.text),
                        acc,
                        visit(right).cast<Expression>(),
                    )
                },
        )
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

    override fun visitUnary_expression(ctx: CParser.Unary_expressionContext): Value {
        val coreExpr = visit(ctx.unary_core()).cast<Expression>()
        return Value.of(
            ctx.prefix_operator()
                .asReversed()
                .fold(coreExpr) { acc, op ->
                    UnaryExpression(ctx.location, UnaryType.parse(op.text), acc)
                },
        )
    }

    override fun visitSimpleUnaryCore(ctx: CParser.SimpleUnaryCoreContext): Value {
        return Value.of(visit(ctx.postfix_expression()).cast<Expression>())
    }

    override fun visitCompoundUnaryCore(ctx: CParser.CompoundUnaryCoreContext): Value {
        return Value.of(
            UnaryExpression(
                ctx.location,
                UnaryType.parse(ctx.unary_operator().text),
                visit(ctx.cast_expression()).cast<Expression>(),
            ),
        )
    }

    override fun visitSizeofUnaryCore(ctx: CParser.SizeofUnaryCoreContext?): Value? {
        error("sizeof(type_name) is currently not supported")
    }

    override fun visitPostfix_expression(ctx: CParser.Postfix_expressionContext): Value {
        return Value.of(
            ctx
                .postfix_suffix()
                .fold(visit(ctx.primary_expression()).cast<Expression>()) { acc, suffix ->
                    when (suffix) {
                        is CParser.PostfixArrayAccessContext -> {
                            ArrayAccessExpression(ctx.location, acc, visit(suffix.index).cast<Expression>())
                        }

                        is CParser.PostfixFunctionCallContext -> {
                            val argumentList = suffix.args?.assignment_expression()?.map { visit(it).cast<Expression>() } ?: emptyList()
                            if (acc is Identifier) {
                                CallExpression(ctx.location, acc.id, argumentList)
                            } else {
                                error("XXX")
                            }
                        }

                        is CParser.PostfixMemberAccessContext -> {
                            FieldAccessExpression(ctx.location, acc, suffix.field.text)
                        }

                        is CParser.PostfixPointerMemberAccessContext -> {
                            val deref = UnaryExpression(ctx.location, UnaryType.Indirection, acc)
                            FieldAccessExpression(ctx.location, deref, suffix.field.text)
                        }

                        is CParser.PostfixIncrementContext -> {
                            PostfixIncrementExpression(ctx.location, acc)
                        }

                        is CParser.PostfixDecrementContext -> {
                            PostfixDecrementExpression(ctx.location, acc)
                        }

                        else -> error("unknown postfix suffix $suffix")
                    }
                },
        )
    }

    override fun visitPrimaryId(ctx: CParser.PrimaryIdContext): Value {
        return Value.of(Identifier(ctx.location, ctx.Identifier().text))
    }

    override fun visitPrimaryConstant(ctx: CParser.PrimaryConstantContext): Value {
        return Value.of(parseConstant(ctx.location, ctx.Constant().text))
    }

    override fun visitPrimaryStringLiteral(ctx: CParser.PrimaryStringLiteralContext): Value {
        val str = ctx.StringLiteral().joinToString("") { it.text }
        return Value.of(ConstantStringExpression(ctx.location, str))
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
                visit(ctx.constant_expression()).cast<ConstantExpression>(),
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
