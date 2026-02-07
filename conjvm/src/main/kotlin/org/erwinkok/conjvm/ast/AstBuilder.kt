package org.erwinkok.conjvm.ast

import org.antlr.v4.runtime.ParserRuleContext
import org.antlr.v4.runtime.Token
import org.erwinkok.conjvm.CBaseVisitor
import org.erwinkok.conjvm.CParser
import org.erwinkok.conjvm.ast.expressions.ArrayAccessExpression
import org.erwinkok.conjvm.ast.expressions.AssignmentExpression
import org.erwinkok.conjvm.ast.expressions.AssignmentOperator
import org.erwinkok.conjvm.ast.expressions.BinaryExpression
import org.erwinkok.conjvm.ast.expressions.BinaryOperator
import org.erwinkok.conjvm.ast.expressions.CallExpression
import org.erwinkok.conjvm.ast.expressions.CastExpression
import org.erwinkok.conjvm.ast.expressions.CharacterLiteralExpression
import org.erwinkok.conjvm.ast.expressions.ConditionalExpression
import org.erwinkok.conjvm.ast.expressions.ConstantExpression
import org.erwinkok.conjvm.ast.expressions.Expression
import org.erwinkok.conjvm.ast.expressions.FieldAccessExpression
import org.erwinkok.conjvm.ast.expressions.FloatLiteralExpression
import org.erwinkok.conjvm.ast.expressions.IntegerLiteralExpression
import org.erwinkok.conjvm.ast.expressions.ParenthesizedExpression
import org.erwinkok.conjvm.ast.expressions.PostfixDecrementExpression
import org.erwinkok.conjvm.ast.expressions.PostfixIncrementExpression
import org.erwinkok.conjvm.ast.expressions.StringLiteralExpression
import org.erwinkok.conjvm.ast.expressions.UnaryExpression
import org.erwinkok.conjvm.ast.expressions.UnaryOperator
import org.erwinkok.conjvm.ast.expressions.VariableReference
import org.erwinkok.conjvm.ast.statements.BlockStatement
import org.erwinkok.conjvm.ast.statements.BreakStatement
import org.erwinkok.conjvm.ast.statements.CompilationUnitStatement
import org.erwinkok.conjvm.ast.statements.ContinueStatement
import org.erwinkok.conjvm.ast.statements.DoWhileStatement
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
import org.erwinkok.conjvm.ast.statements.WhileStatement
import org.erwinkok.conjvm.declarations.Entity
import org.erwinkok.conjvm.declarations.Scope
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.SourceFile
import org.erwinkok.conjvm.parser.SourceLocation
import org.erwinkok.conjvm.parser.UnknownLocation
import org.erwinkok.conjvm.types.QualType
import org.erwinkok.conjvm.types.Type
import org.erwinkok.conjvm.types.TypeException
import org.erwinkok.conjvm.types.TypeResolutionResult
import org.erwinkok.conjvm.types.TypeResolver
import org.erwinkok.conjvm.utils.ParserReporting
import org.erwinkok.conjvm.utils.Value

class AstBuilder(
    override val reporter: ErrorReporter,
    override val source: SourceFile,
    private val typeResolution: TypeResolutionResult,
) : CBaseVisitor<Value>(),
    ParserReporting {
    private var currentScope: Scope? = null
    private val entityTable = typeResolution.entityTable
    private var currentFunction: Entity.Function? = null
    private var loopDepth = 0
    private var switchDepth = 0
    val typeResolver = TypeResolver(
        reporter = reporter,
        source = source,
        entityTable = typeResolution.entityTable,
        rootScope = typeResolution.rootScope,
    )

    override fun visitCompilationUnit(ctx: CParser.CompilationUnitContext): Value {
        currentScope = entityTable.getScope(ctx)

        val varDecls = mutableListOf<VariableDeclarationStatement>()
        val funcDefs = mutableListOf<FunctionDefinitionStatement>()
        for (decl in ctx.external_declaration()) {
            when (decl) {
                is CParser.DeclrVarDeclContext -> varDecls.add(visit(decl).cast<VariableDeclarationStatement>())
                is CParser.DeclrFunctionDefContext -> funcDefs.add(visit(decl).cast<FunctionDefinitionStatement>())
                is CParser.DeclrStrayContext -> Unit // ignore stray semicolon
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
        val function = entityTable.getFunction(ctx) ?: error("function not found")
        val functionScope = entityTable.getScope(ctx) ?: error("function scope not found")
        val previousFunction = currentFunction
        val previousScope = currentScope
        currentFunction = function
        currentScope = functionScope
        try {
            val body = visit(ctx.block_statement()).cast<BlockStatement>()
            return Value.of(FunctionDefinitionStatement(ctx.location, function, body))
        } finally {
            currentScope = previousScope
            currentFunction = previousFunction
        }
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
        val left = visit(ctx.unary_expression()).cast<Expression>()
        if (!left.isLValue) {
            return reportErrorNode(ctx.unary_expression().location, "expression is not assignable")
        }
        val right = visit(ctx.assignment_expression()).cast<Expression>()
        val type = ctx.assignment_operator().text
        val operator = AssignmentOperator.parse(type) ?: return reportErrorNode(ctx.location, "Unknown assignment operator: $type")
        if (!isAssignmentCompatible(left.type, right.type)) {
            reporter.reportError(
                ctx.location,
                "incompatible types in assignment: cannot assign '${right.type}' to '${left.type}'",
            )
        }
        return Value.of(AssignmentExpression(ctx.location, operator, left, right, left.type))
    }

    override fun visitAssignExprWithLiteral(ctx: CParser.AssignExprWithLiteralContext): Value {
        return Value.of(parseConstant(ctx.location, ctx.DigitSequence().text))
    }

    override fun visitSimpleConditional(ctx: CParser.SimpleConditionalContext): Value {
        return visit(ctx.logical_or_expression())
    }

    override fun visitCompoundConditional(ctx: CParser.CompoundConditionalContext): Value {
        val condition = visit(ctx.test).cast<Expression>()
        val thenExpression = visit(ctx.thenExpr).cast<Expression>()
        val elseExpression = visit(ctx.elseExpr).cast<Expression>()
        if (!isScalarType(condition.type)) {
            reporter.reportError(
                ctx.logical_or_expression().location,
                "condition must have scalar type",
            )
        }
        // Result type is the common type of then and else
        val resultType = usualArithmeticConversions(thenExpression.type, elseExpression.type)
        return Value.of(
            ConditionalExpression(
                ctx.location,
                condition,
                thenExpression,
                elseExpression,
                resultType,
            ),
        )
    }

    override fun visitLogical_or_expression(ctx: CParser.Logical_or_expressionContext): Value {
        return Value.of(buildBinaryOp(ctx, ctx.left, ctx.op, ctx.right))
    }

    override fun visitLogical_and_expression(ctx: CParser.Logical_and_expressionContext): Value {
        return Value.of(buildBinaryOp(ctx, ctx.left, ctx.op, ctx.right))
    }

    override fun visitInclusive_or_expression(ctx: CParser.Inclusive_or_expressionContext): Value {
        return Value.of(buildBinaryOp(ctx, ctx.left, ctx.op, ctx.right))
    }

    override fun visitExclusive_or_expression(ctx: CParser.Exclusive_or_expressionContext): Value {
        return Value.of(buildBinaryOp(ctx, ctx.left, ctx.op, ctx.right))
    }

    override fun visitAnd_expression(ctx: CParser.And_expressionContext): Value {
        return Value.of(buildBinaryOp(ctx, ctx.left, ctx.op, ctx.right))
    }

    override fun visitEquality_expression(ctx: CParser.Equality_expressionContext): Value {
        return Value.of(buildBinaryOp(ctx, ctx.left, ctx.op, ctx.right))
    }

    override fun visitRelational_expression(ctx: CParser.Relational_expressionContext): Value {
        return Value.of(buildBinaryOp(ctx, ctx.left, ctx.op, ctx.right))
    }

    override fun visitShift_expression(ctx: CParser.Shift_expressionContext): Value {
        return Value.of(buildBinaryOp(ctx, ctx.left, ctx.op, ctx.right))
    }

    override fun visitAdditive_expression(ctx: CParser.Additive_expressionContext): Value {
        return Value.of(buildBinaryOp(ctx, ctx.left, ctx.op, ctx.right))
    }

    override fun visitMultiplicative_expression(ctx: CParser.Multiplicative_expressionContext): Value {
        return Value.of(buildBinaryOp(ctx, ctx.left, ctx.op, ctx.right))
    }

    override fun visitSimpleCast(ctx: CParser.SimpleCastContext): Value {
        return visit(ctx.unary_expression())
    }

    override fun visitCastExpr(ctx: CParser.CastExprContext): Value {
        val typeName = entityTable.getTypeName(ctx) ?: error("typeName scope not found")
        val scope = currentScope ?: error("current scope is null")
        val nodeResult = visit(ctx.cast_expression()).cast<Expression>()
        val targetType = typeResolver.buildType(typeName.declarationSpecifier, typeName.abstractDeclarator, scope)
        return Value.of(CastExpression(ctx.location, targetType, nodeResult))
    }

    override fun visitCastWithLiteral(ctx: CParser.CastWithLiteralContext): Value {
        return Value.of(parseConstant(ctx.location, ctx.DigitSequence().text))
    }

    override fun visitUnary_expression(ctx: CParser.Unary_expressionContext): Value {
        val coreExpr = visit(ctx.unary_core()).cast<Expression>()
        return Value.of(
            ctx.prefix_operator()
                .asReversed()
                .fold(coreExpr) { result, op ->
                    when (op) {
                        is CParser.PrefixIncrementContext -> {
                            if (!result.isLValue) {
                                return reportErrorNode(ctx.location, "operand must be an lvalue")
                            }
                            buildUnaryOp(ctx.location, UnaryOperator.PrefixIncrement, result)
                        }

                        is CParser.PrefixDecrementContext -> {
                            if (!result.isLValue) {
                                return reportErrorNode(ctx.location, "operand must be an lvalue")
                            }
                            buildUnaryOp(ctx.location, UnaryOperator.PrefixDecrement, result)
                        }

                        is CParser.PrefixSizeofContext -> {
                            error("sizeof operator is currently not supported")
                        }

                        else -> return reportErrorNode(ctx.location, "Unknown unary expression")
                    }
                },
        )
    }

    override fun visitCompoundUnaryCore(ctx: CParser.CompoundUnaryCoreContext): Value {
        val operator = UnaryOperator.parse(ctx.unary_operator().text) ?: return reportErrorNode(ctx.location, "Unknown unary operator")
        val operand = visit(ctx.cast_expression()).cast<Expression>()
        return Value.of(buildUnaryOp(ctx.location, operator, operand))
    }

    override fun visitSimpleUnaryCore(ctx: CParser.SimpleUnaryCoreContext): Value {
        return visit(ctx.postfix_expression())
    }

    override fun visitSizeofUnaryCore(ctx: CParser.SizeofUnaryCoreContext): Value? {
        error("sizeof operator is currently not supported")
    }

    override fun visitPostfix_expression(ctx: CParser.Postfix_expressionContext): Value {
        return Value.of(
            ctx
                .postfix_suffix()
                .fold(visit(ctx.primary_expression()).cast<Expression>()) { result, suffix ->
                    when (suffix) {
                        is CParser.PostfixArrayAccessContext -> {
                            val index = visit(suffix.index).cast<Expression>()
                            buildArraySubscript(ctx.location, result, index)
                        }

                        is CParser.PostfixFunctionCallContext -> {
                            val argumentList = suffix.args?.assignment_expression()?.map { visit(it).cast<Expression>() } ?: emptyList()
                            buildFunctionCall(ctx.location, result, argumentList)
                        }

                        is CParser.PostfixMemberAccessContext -> {
                            val memberName = suffix.Identifier().text
                            buildMemberAccess(ctx.location, result, memberName)
                        }

                        is CParser.PostfixPointerMemberAccessContext -> {
                            val memberName = suffix.Identifier().text
                            buildPointerMemberAccess(ctx.location, result, memberName)
                        }

                        is CParser.PostfixIncrementContext -> {
                            if (!result.isLValue) {
                                reporter.reportError(ctx.location, "operand must be an lvalue")
                            }
                            PostfixIncrementExpression(ctx.location, result, result.type)
                        }

                        is CParser.PostfixDecrementContext -> {
                            if (!result.isLValue) {
                                reporter.reportError(ctx.location, "operand must be an lvalue")
                            }
                            PostfixDecrementExpression(ctx.location, result, result.type)
                        }

                        else -> error("unknown postfix suffix $suffix")
                    }
                },
        )
    }

    override fun visitPrimaryId(ctx: CParser.PrimaryIdContext): Value {
        val name = ctx.Identifier().text
        return Value.of(lookupIdentifier(ctx.location, name))
    }

    override fun visitPrimaryConstant(ctx: CParser.PrimaryConstantContext): Value {
        return Value.of(parseConstant(ctx.location, ctx.Constant().text))
    }

    override fun visitPrimaryStringLiteral(ctx: CParser.PrimaryStringLiteralContext): Value {
        val text = ctx.StringLiteral().joinToString("") { it.text }
        val value = parseStringLiteral(text)
        val arrayType = QualType(
            Type.Array(
                QualType(Type.Char(signed = true)),
                (value.length + 1).toLong(),
            ),
        )
        return Value.of(StringLiteralExpression(ctx.location, value, arrayType))
    }

    override fun visitPrimaryParenthesized(ctx: CParser.PrimaryParenthesizedContext): Value {
        val expression = visit(ctx.expression()).cast<Expression>()
        return Value.of(ParenthesizedExpression(ctx.location, expression, expression.type))
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

    override fun visitStatementEmbedded(ctx: CParser.StatementEmbeddedContext): Value {
        return visit(ctx.embedded_statement())
    }

    override fun visitEmbeddedStmtBlock(ctx: CParser.EmbeddedStmtBlockContext): Value {
        return visit(ctx.block_statement())
    }

    override fun visitEmbeddedStmtExpression(ctx: CParser.EmbeddedStmtExpressionContext): Value {
        return visit(ctx.expression_statement())
    }

    override fun visitEmbeddedStmtIfThen(ctx: CParser.EmbeddedStmtIfThenContext): Value {
        return visit(ctx.if_then_statement())
    }

    override fun visitEmbeddedStmtIfThenElse(ctx: CParser.EmbeddedStmtIfThenElseContext): Value {
        return visit(ctx.if_then_else_statement())
    }

    override fun visitEmbeddedStmtWhile(ctx: CParser.EmbeddedStmtWhileContext): Value {
        return visit(ctx.while_statement())
    }

    override fun visitEmbeddedStmtDo(ctx: CParser.EmbeddedStmtDoContext): Value {
        return visit(ctx.do_statement())
    }

    override fun visitEmbeddedStmtFor(ctx: CParser.EmbeddedStmtForContext): Value {
        return visit(ctx.for_statement())
    }

    override fun visitEmbeddedStmtSwitch(ctx: CParser.EmbeddedStmtSwitchContext): Value {
        return visit(ctx.switch_statement())
    }

    override fun visitEmbeddedStmtBreak(ctx: CParser.EmbeddedStmtBreakContext): Value {
        return visit(ctx.break_statement())
    }

    override fun visitEmbeddedStmtContinue(ctx: CParser.EmbeddedStmtContinueContext): Value {
        return visit(ctx.continue_statement())
    }

    override fun visitEmbeddedStmtGoto(ctx: CParser.EmbeddedStmtGotoContext): Value {
        return visit(ctx.goto_statement())
    }

    override fun visitEmbeddedStmtReturn(ctx: CParser.EmbeddedStmtReturnContext): Value {
        return visit(ctx.return_statement())
    }

    override fun visitBlock_statement(ctx: CParser.Block_statementContext): Value {
        val scope = entityTable.getScope(ctx) ?: error("block scope not found")
        val previousScope = currentScope
        currentScope = scope
        try {
            val statements = ctx.block_item().map { visit(it).cast<Statement>() }
            return Value.of(
                BlockStatement(
                    ctx.location,
                    statements,
                ),
            )
        } finally {
            currentScope = previousScope
        }
    }

    override fun visitBlckItemStmt(ctx: CParser.BlckItemStmtContext): Value {
        return visit(ctx.statement())
    }

    override fun visitBlckItemVarDecl(ctx: CParser.BlckItemVarDeclContext): Value {
        return visit(ctx.declaration())
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
        val ex = ctx.expression()?.let {
            ExpressionStatement(ctx.location, visit(it).cast<Expression>())
        } ?: BlockStatement(ctx.location, emptyList())
        return Value.of(ex)
    }

    override fun visitIf_then_statement(ctx: CParser.If_then_statementContext): Value {
        val condition = visit(ctx.test).cast<Expression>()
        if (!isScalarType(condition.type)) {
            reporter.reportError(
                ctx.expression().location,
                "condition must have scalar type, got '${condition.type}'",
            )
        }
        return Value.of(
            IfThenStatement(
                ctx.location,
                condition,
                visit(ctx.thenExpr).toBlockStatement(ctx.location),
            ),
        )
    }

    override fun visitIf_then_else_statement(ctx: CParser.If_then_else_statementContext): Value {
        val condition = visit(ctx.test).cast<Expression>()
        if (!isScalarType(condition.type)) {
            reporter.reportError(
                ctx.expression().location,
                "condition must have scalar type, got '${condition.type}'",
            )
        }
        return Value.of(
            IfThenElseStatement(
                ctx.location,
                condition,
                visit(ctx.thenExpr).toBlockStatement(ctx.location),
                visit(ctx.elseExpr).toBlockStatement(ctx.location),
            ),
        )
    }

    override fun visitSwitch_statement(ctx: CParser.Switch_statementContext): Value {
        val (cases, default) = ctx.switch_section().map { visit(it) }.partition { it.tryCast<SwitchCaseStatement>() != null }
        if (default.size > 1) {
            reporter.reportError(ctx.location, "Switch statement cannot have more than one default section")
        }
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
        val condition = visit(ctx.test).cast<Expression>()
        if (!isScalarType(condition.type)) {
            reporter.reportError(
                ctx.expression().location,
                "condition must have scalar type",
            )
        }
        loopDepth++
        val statements = visit(ctx.statements).toBlockStatement(ctx.location)
        loopDepth--
        return Value.of(
            WhileStatement(
                ctx.location,
                condition,
                statements,
            ),
        )
    }

    override fun visitDo_statement(ctx: CParser.Do_statementContext): Value {
        val condition = visit(ctx.test).cast<Expression>()
        if (!isScalarType(condition.type)) {
            reporter.reportError(
                ctx.expression().location,
                "condition must have scalar type",
            )
        }
        loopDepth++
        val statements = visit(ctx.statements).toBlockStatement(ctx.location)
        loopDepth--
        return Value.of(
            DoWhileStatement(
                ctx.location,
                condition,
                statements,
            ),
        )
    }

    override fun visitFor_statement(ctx: CParser.For_statementContext): Value {
        val scope = entityTable.getScope(ctx) ?: error("for scope not found")
        val previousScope = currentScope
        currentScope = scope
        try {
            loopDepth++
            val statements = visit(ctx.embedded_statement()).toBlockStatement(ctx.location)
            loopDepth--
            return Value.of(
                ForStatement(
                    ctx.location,
                    ctx.init?.let { visit(it).cast<ForInit>() },
                    ctx.test?.let { visit(ctx.test).cast<Expression>() },
                    ctx.iterator?.let { visit(it).cast<List<Expression>>() },
                    statements,
                ),
            )
        } finally {
            currentScope = previousScope
        }
    }

    override fun visitForInitAssignmentExpr(ctx: CParser.ForInitAssignmentExprContext): Value {
        val assignments = visit(ctx.argument_list()).cast<List<AssignmentExpression>>()
        return Value.of(ForInitAssignmentExpression(ctx.location, assignments))
    }

    override fun visitForInitVarDecl(ctx: CParser.ForInitVarDeclContext): Value {
        val variables = entityTable.getVariables(ctx) ?: error("variables not found for for-loop init")
        for (variable in variables) {
            val definedVar = variable.definition ?: return reportErrorNode(ctx.location, "variable not defined")
            val initializer = definedVar.initializerCtx?.let { visit(it).cast<Expression>() }
            variable.initializer = initializer
        }
        return Value.of(ForInitVariableDeclaration(ctx.location, VariableDeclarationStatement(ctx.location, variables)))
    }

    override fun visitFor_expression(ctx: CParser.For_expressionContext): Value {
        return Value.of(ctx.assignment_expression().map { visit(it).cast<Expression>() })
    }

    override fun visitBreak_statement(ctx: CParser.Break_statementContext): Value {
        if (loopDepth == 0 && switchDepth == 0) {
            reporter.reportError(
                ctx.location,
                "break statement not in loop or switch",
            )
        }
        return Value.of(BreakStatement(ctx.location))
    }

    override fun visitContinue_statement(ctx: CParser.Continue_statementContext): Value {
        if (loopDepth == 0) {
            reporter.reportError(
                ctx.location,
                "continue statement not in loop",
            )
        }
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
    // DECLARATION
    //
    override fun visitDeclaration(ctx: CParser.DeclarationContext): Value {
        val variables = entityTable.getVariables(ctx) ?: return Value.of(VariableDeclarationStatement(ctx.location, emptyList()))
        variables.forEach { variable ->
            val definedVar = variable.definition ?: return reportErrorNode(ctx.location, "variable not defined")
            val initializer = definedVar.initializerCtx?.let { visit(it).cast<Expression>() }
            variable.initializer = initializer
        }
        return Value.of(VariableDeclarationStatement(ctx.location, variables))
    }

    // ========================================================================
    // HELPER FUNCTIONS - Type Checking and Conversions
    // ========================================================================

    private fun buildBinaryOp(
        ctx: ParserRuleContext,
        left: ParserRuleContext,
        operators: List<Token>,
        rights: List<ParserRuleContext>,
    ): Expression {
        var left = visit(left).cast<Expression>()
        for ((op, rightCtx) in operators.zip(rights)) {
            val right = visit(rightCtx).cast<Expression>()
            val operator = BinaryOperator.parse(op.text) ?: throw TypeException("Unknown binary operator: ${op.text}")
            val resultType = when (operator) {
                BinaryOperator.LogicalAnd, BinaryOperator.LogicalOr,
                BinaryOperator.Equals, BinaryOperator.NotEquals,
                BinaryOperator.Less, BinaryOperator.LessOrEqual,
                BinaryOperator.Greater, BinaryOperator.GreaterOrEqual,
                -> {
                    // Result is int
                    QualType(Type.Int(signed = true))
                }

                BinaryOperator.Add, BinaryOperator.Subtract -> {
                    // Handle pointer arithmetic
                    when {
                        isPointerType(left.type) && isIntegerType(right.type) -> left.type
                        isIntegerType(left.type) && isPointerType(right.type) -> right.type
                        isPointerType(left.type) && isPointerType(right.type) && operator == BinaryOperator.Subtract -> {
                            // Pointer difference
                            QualType(Type.Long(signed = true)) // ptrdiff_t
                        }

                        else -> usualArithmeticConversions(left.type, right.type)
                    }
                }

                else -> usualArithmeticConversions(left.type, right.type)
            }
            left = BinaryExpression(
                ctx.location,
                operator,
                left,
                right,
                resultType,
            )
        }
        return left
    }

    private fun buildUnaryOp(
        location: SourceLocation,
        operator: UnaryOperator,
        operand: Expression,
    ): UnaryExpression {
        val resultType = when (operator) {
            UnaryOperator.AddressOf -> {
                if (!operand.isLValue) {
                    reporter.reportError(location, "cannot take address of rvalue")
                }
                QualType(Type.Pointer(operand.type))
            }

            UnaryOperator.Dereference -> {
                if (!isPointerType(operand.type)) {
                    reporter.reportError(location, "cannot dereference non-pointer type '${operand.type}'")
                    operand.type
                } else {
                    (operand.type.canonical.type as Type.Pointer).pointee
                }
            }

            UnaryOperator.LogicalNot -> {
                if (!isScalarType(operand.type)) {
                    reporter.reportError(location, "operand must have scalar type")
                }
                QualType(Type.Int(signed = true))
            }

            UnaryOperator.Plus, UnaryOperator.Minus -> {
                if (!isArithmeticType(operand.type)) {
                    reporter.reportError(location, "operand must have arithmetic type")
                }
                integerPromotion(operand.type)
            }

            UnaryOperator.BitwiseNot -> {
                if (!isIntegerType(operand.type)) {
                    reporter.reportError(location, "operand must have integer type")
                }
                integerPromotion(operand.type)
            }

            UnaryOperator.PrefixIncrement, UnaryOperator.PrefixDecrement -> {
                if (!isScalarType(operand.type)) {
                    reporter.reportError(location, "operand must have scalar type")
                }
                operand.type
            }
        }
        return UnaryExpression(location, operator, operand, resultType)
    }

    private fun buildArraySubscript(location: SourceLocation, array: Expression, index: Expression): ArrayAccessExpression {
        val arrayType = array.type.canonical.type
        val elementType = when {
            arrayType is Type.Array -> arrayType.elementType
            arrayType is Type.Pointer -> arrayType.pointee
            else -> {
                reporter.reportError(location, "subscripted value is not an array or pointer")
                QualType(Type.Error)
            }
        }
        if (!isIntegerType(index.type)) {
            reporter.reportError(location, "array subscript must be an integer")
        }
        return ArrayAccessExpression(location, array, index, elementType)
    }

    private fun buildFunctionCall(location: SourceLocation, function: Expression, arguments: List<Expression>): CallExpression {
        val funcType = when (val canonical = function.type.canonical.type) {
            is Type.Function -> canonical
            is Type.Pointer -> {
                when (val pointee = canonical.pointee.canonical.type) {
                    is Type.Function -> pointee
                    else -> {
                        reporter.reportError(location, "called object is not a function")
                        return CallExpression(location, function, arguments, QualType(Type.Error))
                    }
                }
            }

            else -> {
                reporter.reportError(location, "called object is not a function")
                return CallExpression(location, function, arguments, QualType(Type.Error))
            }
        }
        // Type check arguments
        if (arguments.size != funcType.parameters.size) {
            reporter.reportError(
                location,
                "function expects ${funcType.parameters.size} arguments, got ${arguments.size}",
            )
        }
        val convertedArgs = arguments.zip(funcType.parameters).map { (arg, paramType) ->
            if (!isAssignmentCompatible(paramType, arg.type)) {
                reporter.reportError(
                    location,
                    "incompatible argument type: expected '$paramType', got '${arg.type}'",
                )
            }
            arg
        }
        return CallExpression(location, function, convertedArgs, funcType.returnType)
    }

    private fun buildMemberAccess(location: SourceLocation, struct: Expression, memberName: String): FieldAccessExpression {
        val structType = struct.type.canonical.type
        if (structType !is Type.Struct) {
            reporter.reportError(location, "member access requires struct type, got '${struct.type}'")
            return FieldAccessExpression(location, struct, memberName, QualType(Type.Error))
        }
        val members = structType.members
        if (members == null) {
            reporter.reportError(location, "incomplete struct type")
            return FieldAccessExpression(location, struct, memberName, QualType(Type.Error))
        }
        val member = members.firstOrNull { it.name == memberName }
        if (member == null) {
            reporter.reportError(location, "struct has no member named '$memberName'")
            return FieldAccessExpression(location, struct, memberName, QualType(Type.Error))
        }
        return FieldAccessExpression(location, struct, memberName, member.type)
    }

    private fun buildPointerMemberAccess(location: SourceLocation, struct: Expression, memberName: String): FieldAccessExpression {
        val structType = struct.type.canonical.type
        if (structType !is Type.Struct) {
            reporter.reportError(location, "member access requires struct type, got '${struct.type}'")
            return FieldAccessExpression(location, struct, memberName, QualType(Type.Error))
        }
        val members = structType.members
        if (members == null) {
            reporter.reportError(location, "incomplete struct type")
            return FieldAccessExpression(location, struct, memberName, QualType(Type.Error))
        }
        val member = members.firstOrNull { it.name == memberName }
        if (member == null) {
            reporter.reportError(location, "struct has no member named '$memberName'")
            return FieldAccessExpression(location, struct, memberName, QualType(Type.Error))
        }
        val deref = UnaryExpression(location, UnaryOperator.Dereference, struct, member.type)
        return FieldAccessExpression(location, deref, memberName, member.type)
    }

    private fun lookupIdentifier(location: SourceLocation, name: String): Expression {
        // Try enum constant first
        currentScope?.lookupEnumConstant(name)?.let { enumConst ->
            return IntegerLiteralExpression(
                location = location,
                value = enumConst,
                type = QualType(Type.Int(signed = true)),
            )
        }

        // Try variable lookup
        val entity = currentScope?.lookupVariable(name) ?: throw TypeException("undefined identifier '$name'")
        val type = entity.type ?: throw TypeException("entity '$name' has no type")
        return VariableReference(location, name, entity, type)
    }

    // ========================================================================
    // TYPE SYSTEM HELPERS
    // ========================================================================

    private fun usualArithmeticConversions(t1: QualType, t2: QualType): QualType {
        // Simplified version of C's usual arithmetic conversions
        val c1 = t1.canonical.type
        val c2 = t2.canonical.type

        // If either is error, return error
        if (c1 is Type.Error || c2 is Type.Error) {
            return QualType(Type.Error)
        }

        // If either is floating point, use floating point rules
        when {
            c1 is Type.LongDouble || c2 is Type.LongDouble ->
                return QualType(Type.LongDouble)

            c1 is Type.Double || c2 is Type.Double ->
                return QualType(Type.Double)

            c1 is Type.Float || c2 is Type.Float ->
                return QualType(Type.Float)
        }

        // Integer promotion
        val p1 = integerPromotion(t1)
        val p2 = integerPromotion(t2)

        // If same type, return it
        if (p1.canonical == p2.canonical) return p1

        // Get integer types
        val i1 = p1.canonical.type as? Type.Int ?: p1.canonical.type as? Type.Long ?: p1.canonical.type as? Type.LongLong ?: return p1
        val i2 = p2.canonical.type as? Type.Int ?: p2.canonical.type as? Type.Long ?: p2.canonical.type as? Type.LongLong ?: return p2

        // Rank: long long > long > int
        val rank1 = when (i1) {
            is Type.LongLong -> 3
            is Type.Long -> 2
            is Type.Int -> 1
            else -> 0
        }

        val rank2 = when (i2) {
            is Type.LongLong -> 3
            is Type.Long -> 2
            is Type.Int -> 1
            else -> 0
        }

        // Return higher rank
        return if (rank1 >= rank2) p1 else p2
    }

    private fun integerPromotion(type: QualType): QualType {
        return when (type.canonical.type) {
            is Type.Bool,
            is Type.Char,
            is Type.Short,
            -> QualType(Type.Int(signed = true))

            else -> type
        }
    }

    private fun isAssignmentCompatible(target: QualType, source: QualType): Boolean {
        // Error types are compatible with everything
        if (target.isError || source.isError) return true

        val targetCanon = target.canonical.type
        val sourceCanon = source.canonical.type

        return when {
            // Same type
            targetCanon == sourceCanon -> true

            // Arithmetic types
            isArithmeticType(target) && isArithmeticType(source) -> true

            // Pointer compatibility
            isPointerType(target) && isPointerType(source) -> {
                val targetPointee = (targetCanon as Type.Pointer).pointee
                val sourcePointee = (sourceCanon as Type.Pointer).pointee

                // void* is compatible with any pointer
                targetPointee.canonical.type is Type.Void ||
                    sourcePointee.canonical.type is Type.Void ||
                    targetPointee.canonical == sourcePointee.canonical
            }

            // Null pointer constant (0) to pointer
            isPointerType(target) && isIntegerType(source) -> true

            else -> false
        }
    }

    private fun isCastValid(fromType: QualType, toType: QualType): Boolean {
        // Most casts are valid in C (even if unsafe)
        // Only invalid casts: struct to non-struct, etc.
        return when {
            fromType.isError || toType.isError -> true
            fromType.canonical.type is Type.Struct && toType.canonical.type !is Type.Struct -> false
            toType.canonical.type is Type.Struct && fromType.canonical.type !is Type.Struct -> false
            else -> true
        }
    }

    private fun isScalarType(type: QualType): Boolean {
        return isArithmeticType(type) || isPointerType(type)
    }

    private fun isArithmeticType(type: QualType): Boolean {
        return isIntegerType(type) || isFloatingType(type)
    }

    private fun isIntegerType(type: QualType): Boolean {
        return when (type.canonical.type) {
            is Type.Bool,
            is Type.Char,
            is Type.Short,
            is Type.Int,
            is Type.Long,
            is Type.LongLong,
            -> true

            else -> false
        }
    }

    private fun isFloatingType(type: QualType): Boolean {
        return when (type.canonical.type) {
            is Type.Float,
            is Type.Double,
            is Type.LongDouble,
            -> true

            else -> false
        }
    }

    private fun isPointerType(type: QualType): Boolean {
        return type.canonical.type is Type.Pointer
    }

    private fun Value.toBlockStatement(location: SourceLocation): BlockStatement {
        return this.tryCast<BlockStatement>() ?: BlockStatement(location, listOf(this.cast<Statement>()))
    }

    private fun parseConstant(location: SourceLocation, text: String): Expression {
        // Parse integer or float constant
        return when {
            text.contains('.') || text.contains('e') || text.contains('E') -> {
                // Float constant
                val value = text.toDoubleOrNull() ?: run {
                    reporter.reportError(location, "invalid float constant: $text")
                    0.0
                }

                val type = when {
                    text.endsWith('f') || text.endsWith('F') -> QualType(Type.Float)
                    text.endsWith('l') || text.endsWith('L') -> QualType(Type.LongDouble)
                    else -> QualType(Type.Double)
                }

                FloatLiteralExpression(location, value, type)
            }

            text.startsWith("'") -> {
                // Character constant
                val value = parseCharacterConstant(text)
                CharacterLiteralExpression(location, value, QualType(Type.Int(signed = true)))
            }

            else -> {
                // Integer constant
                val (value, type) = parseIntegerConstant(text)
                IntegerLiteralExpression(location, value, type)
            }
        }
    }

    private fun parseIntegerConstant(text: String): Pair<Long, QualType> {
        // Determine base
        val (base, digits) = when {
            text.startsWith("0x") || text.startsWith("0X") -> 16 to text.substring(2)
            text.startsWith("0") && text.length > 1 -> 8 to text.substring(1)
            else -> 10 to text
        }

        // Remove suffix
        val suffix = digits.takeLastWhile { it in "uUlL" }
        val numberPart = digits.dropLast(suffix.length)

        val value = numberPart.toLongOrNull(base) ?: run {
            reporter.reportError(UnknownLocation, "invalid integer constant: $text")
            0L
        }

        // Determine type from suffix
        val isUnsigned = suffix.contains('u') || suffix.contains('U')
        val isLong = suffix.count { it == 'l' || it == 'L' }

        val type = when {
            isLong >= 2 -> QualType(Type.LongLong(!isUnsigned))
            isLong == 1 -> QualType(Type.Long(!isUnsigned))
            else -> QualType(Type.Int(!isUnsigned))
        }

        return value to type
    }

    private fun parseCharacterConstant(text: String): Char {
        val content = text.substring(1, text.length - 1)
        return when {
            content.startsWith("\\") -> {
                when (content[1]) {
                    'n' -> '\n'
                    't' -> '\t'
                    'r' -> '\r'
                    '0' -> '\u0000'
                    '\\' -> '\\'
                    '\'' -> '\''
                    '"' -> '"'
                    else -> content[1]
                }
            }

            else -> content[0]
        }
    }

    private fun parseStringLiteral(text: String): String {
        // Remove quotes and handle escape sequences
        val content = text.substring(1, text.length - 1)
        return content.replace("\\n", "\n")
            .replace("\\t", "\t")
            .replace("\\r", "\r")
            .replace("\\0", "\u0000")
            .replace("\\\\", "\\")
            .replace("\\'", "'")
            .replace("\\\"", "\"")
    }

    private fun reportErrorNode(location: SourceLocation, message: String): Value {
        throw TypeException(message)
    }
}
