package org.erwinkok.conjvm.ast

import org.antlr.v4.runtime.ParserRuleContext
import org.antlr.v4.runtime.Token
import org.erwinkok.conjvm.CBaseVisitor
import org.erwinkok.conjvm.CParser
import org.erwinkok.conjvm.CParser.DeclSpecFuncSpecContext
import org.erwinkok.conjvm.CParser.DeclSpecTypeQualContext
import org.erwinkok.conjvm.CParser.DeclSpecTypeSpecContext
import org.erwinkok.conjvm.CParser.StorageClassSpecContext
import org.erwinkok.conjvm.ast.expressions.ArrayAccessExpression
import org.erwinkok.conjvm.ast.expressions.AssignmentExpression
import org.erwinkok.conjvm.ast.expressions.AssignmentExpressionType
import org.erwinkok.conjvm.ast.expressions.BinaryExpression
import org.erwinkok.conjvm.ast.expressions.BinaryOperator
import org.erwinkok.conjvm.ast.expressions.CallExpression
import org.erwinkok.conjvm.ast.expressions.CastExpression
import org.erwinkok.conjvm.ast.expressions.CastKind
import org.erwinkok.conjvm.ast.expressions.CharacterLiteralExpression
import org.erwinkok.conjvm.ast.expressions.ConditionalExpression
import org.erwinkok.conjvm.ast.expressions.ConstantExpression
import org.erwinkok.conjvm.ast.expressions.Expression
import org.erwinkok.conjvm.ast.expressions.FloatLiteralExpression
import org.erwinkok.conjvm.ast.expressions.ImplicitCastExpression
import org.erwinkok.conjvm.ast.expressions.IntegerLiteralExpression
import org.erwinkok.conjvm.ast.expressions.MemberAccessExpression
import org.erwinkok.conjvm.ast.expressions.ParenthesizedExpression
import org.erwinkok.conjvm.ast.expressions.PointerMemberAccessExpression
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
import org.erwinkok.conjvm.ast.statements.VariableDeclarator
import org.erwinkok.conjvm.ast.statements.WhileStatement
import org.erwinkok.conjvm.declarations.DeclarationSpecifier
import org.erwinkok.conjvm.declarations.Declarator
import org.erwinkok.conjvm.declarations.Entity
import org.erwinkok.conjvm.declarations.FunctionSpec
import org.erwinkok.conjvm.declarations.Linkage
import org.erwinkok.conjvm.declarations.Parameter
import org.erwinkok.conjvm.declarations.Scope
import org.erwinkok.conjvm.declarations.ScopeKind
import org.erwinkok.conjvm.declarations.StorageClass
import org.erwinkok.conjvm.declarations.TypeName
import org.erwinkok.conjvm.declarations.TypeQualifier
import org.erwinkok.conjvm.declarations.TypeSpec
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.SourceFile
import org.erwinkok.conjvm.parser.SourceLocation
import org.erwinkok.conjvm.parser.UnknownLocation
import org.erwinkok.conjvm.types.QualType
import org.erwinkok.conjvm.types.Type
import org.erwinkok.conjvm.types.TypeException
import org.erwinkok.conjvm.types.TypeResolutionResult
import org.erwinkok.conjvm.types.VariableSymbol
import org.erwinkok.conjvm.utils.ParserReporting
import org.erwinkok.conjvm.utils.Value

class AstBuilder(
    override val reporter: ErrorReporter,
    override val source: SourceFile,
    private val typeResolution: TypeResolutionResult,
) : CBaseVisitor<Value>(),
    ParserReporting {
    private var currentScope: Scope? = null
    private val symbolTable = typeResolution.symbolTable
    private val entityTable = typeResolution.entityTable

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
        val declarationSpecifier = visit(ctx.declaration_specifiers()).cast<DeclarationSpecifier>()
        val declarator = visit(ctx.declarator()).cast<Declarator>()
        return Value.of(
            FunctionDefinitionStatement(
                ctx.location,
                declarationSpecifier,
                declarator,
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
        val left = visit(ctx.unary_expression()).cast<Expression>()
        val right = visit(ctx.assignment_expression()).cast<Expression>()
        if (!left.isLValue) {
            reporter.reportError(
                ctx.unary_expression().location,
                "expression is not assignable",
            )
        }
        val operator = AssignmentExpressionType.parse(ctx.assignment_operator().text) ?: return reportErrorNode(ctx.location, "Unknown assignment operator")
        if (!isAssignmentCompatible(left.type, right.type)) {
            reporter.reportError(
                ctx.location,
                "incompatible types in assignment: cannot assign '${right.type}' to '${left.type}'",
            )
        }
        val convertedRight = insertImplicitConversion(right, left.type)
        return Value.of(
            AssignmentExpression(
                ctx.location,
                operator = operator,
                left = left,
                right = convertedRight,
                type = left.type,
            ),
        )
    }

    override fun visitAssignExprWithLiteral(ctx: CParser.AssignExprWithLiteralContext): Value {
        return Value.of(parseConstant(ctx.location, ctx.DigitSequence().text))
    }

    override fun visitSimpleConditional(ctx: CParser.SimpleConditionalContext): Value {
        return visit(ctx.logical_or_expression())
    }

    override fun visitCompoundConditional(ctx: CParser.CompoundConditionalContext): Value {
        val condition = visit(ctx.test).cast<Expression>()
        val thenExpr = visit(ctx.thenExpr).cast<Expression>()
        val elseExpr = visit(ctx.elseExpr).cast<Expression>()
        if (!isScalarType(condition.type)) {
            reporter.reportError(
                ctx.logical_or_expression().location,
                "condition must have scalar type",
            )
        }
        // Result type is the common type of then and else
        val resultType = usualArithmeticConversions(thenExpr.type, elseExpr.type)

        val convertedThen = insertImplicitConversion(thenExpr, resultType)
        val convertedElse = insertImplicitConversion(elseExpr, resultType)

        return Value.of(
            ConditionalExpression(
                ctx.location,
                condition,
                convertedThen,
                convertedElse,
                type = resultType,
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
        val typeName = entityTable.getTypeName(ctx.type_name())
            ?: return reportErrorNode(ctx.location, "Type name not found")
        val targetType = resolveTypeName(typeName)
        val expression = visit(ctx.cast_expression()).cast<Expression>()
        // Validate cast
        if (!isCastValid(expression.type, targetType)) {
            reporter.reportError(
                ctx.location,
                "invalid cast from '${expression.type}' to '$targetType'",
            )
        }
        return Value.of(CastExpression(ctx.location, typeName, expression))
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
                                reporter.reportError(ctx.location, "operand must be an lvalue")
                            }
                            buildUnaryOp(ctx.location, UnaryOperator.PrefixIncrement, result)
                        }

                        is CParser.PrefixDecrementContext -> {
                            if (!result.isLValue) {
                                reporter.reportError(ctx.location, "operand must be an lvalue")
                            }
                            buildUnaryOp(ctx.location, UnaryOperator.PrefixDecrement, result)
                        }

                        is CParser.PrefixSizeofContext -> {
//                            val size = computeTypeSize(result.type)
//                            return SizeofExpression(
//                                location = ctx.location,
//                                expression = result,
//                                type = QualType(Type.Long(signed = false)),
//                                size = size,
//                            )
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
        // sizeof(type)
//        val typeName = entityTable.getTypeName(ctx.type_name())
//            ?: return reportErrorNode(ctx.location, "Type name not found")
//        val targetType = resolveTypeName(typeName)
//        val size = computeTypeSize(targetType)
//        return SizeofType(
//            location = ctx.location,
//            targetType = targetType,
//            type = QualType(Type.Long(signed = false)),  // size_t
//            size = size,
//        )
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
                            buildUnaryOp(ctx.location, UnaryOperator.PostfixIncrement, result)
                        }

                        is CParser.PostfixDecrementContext -> {
                            if (!result.isLValue) {
                                reporter.reportError(ctx.location, "operand must be an lvalue")
                            }
                            buildUnaryOp(ctx.location, UnaryOperator.PostfixDecrement, result)
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
        return Value.of(
            BlockStatement(
                ctx.location,
                ctx.block_item().map { visit(it).cast<Statement>() },
            ),
        )
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
        return Value.of(
            WhileStatement(
                ctx.location,
                visit(ctx.test).cast<Expression>(),
                visit(ctx.statements).toBlockStatement(ctx.location),
            ),
        )
    }

    override fun visitDo_statement(ctx: CParser.Do_statementContext): Value {
        return Value.of(
            DoWhileStatement(
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
        val declarationSpecifier = visit(ctx.declaration_specifiers()).cast<DeclarationSpecifier>()
        val variableDeclarators = ctx.init_declarator_list()?.let { visit(it).cast<List<VariableDeclarator>>() } ?: emptyList()
        return Value.of(
            ForInitVariableDeclaration(
                VariableDeclarationStatement(
                    ctx.location,
                    declarationSpecifier,
                    variableDeclarators,
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
    // DECLARATION
    //
    override fun visitDeclaration(ctx: CParser.DeclarationContext): Value {
        val declarationSpecifier = visit(ctx.declaration_specifiers()).cast<DeclarationSpecifier>()
        val variableDeclarators = ctx.init_declarator_list()?.let { visit(it).cast<List<VariableDeclarator>>() } ?: emptyList()
        return Value.of(
            VariableDeclarationStatement(
                ctx.location,
                declarationSpecifier,
                variableDeclarators,
            ),
        )
    }

    override fun visitDeclaration_specifiers(ctx: CParser.Declaration_specifiersContext): Value {
        val storage = mutableSetOf<StorageClass>()
        val typeSpecs = mutableListOf<TypeSpec>()
        val qualifiers = mutableSetOf<TypeQualifier>()
        val functionSpecs = mutableSetOf<FunctionSpec>()
        ctx.declaration_specifier().forEach {
            when (it) {
                is StorageClassSpecContext -> storage += parseStorageClassSpec(it.storage_class_specifier())
                is DeclSpecTypeSpecContext -> typeSpecs += parseTypeSpec(it.type_specifier())
                is DeclSpecTypeQualContext -> qualifiers += parseTypeQualifier(it.type_qualifier())
                is DeclSpecFuncSpecContext -> functionSpecs += parseFunctionSpec(it.function_specifier())
            }
        }
        return Value.of(DeclarationSpecifier(storage, typeSpecs, qualifiers, functionSpecs))
    }

    override fun visitDeclaration_specifiers_2(ctx: CParser.Declaration_specifiers_2Context): Value {
        val storage = mutableSetOf<StorageClass>()
        val typeSpecs = mutableListOf<TypeSpec>()
        val qualifiers = mutableSetOf<TypeQualifier>()
        val functionSpecs = mutableSetOf<FunctionSpec>()
        ctx.declaration_specifier().forEach {
            when (it) {
                is StorageClassSpecContext -> storage += parseStorageClassSpec(it.storage_class_specifier())
                is DeclSpecTypeSpecContext -> typeSpecs += parseTypeSpec(it.type_specifier())
                is DeclSpecTypeQualContext -> qualifiers += parseTypeQualifier(it.type_qualifier())
                is DeclSpecFuncSpecContext -> functionSpecs += parseFunctionSpec(it.function_specifier())
            }
        }
        return Value.of(DeclarationSpecifier(storage, typeSpecs, qualifiers, functionSpecs))
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
        val typeSpecs = mutableListOf<TypeSpec>()
        val qualifiers = mutableSetOf<TypeQualifier>()
        ctx.type_specifier().map { typeSpecs += parseTypeSpec(it) }
        ctx.type_qualifier().map { qualifiers += parseTypeQualifier(it) }
        return Value.of(DeclarationSpecifier(emptySet(), typeSpecs, qualifiers, emptySet()))
    }

    override fun visitDeclarator(ctx: CParser.DeclaratorContext): Value {
        val base = visit(ctx.direct_declarator()).cast<Declarator>()
        val pointerQualifiers = ctx.pointer()?.let { visit(it).cast<List<List<TypeQualifier>>>() } ?: emptyList()
        val declarator = pointerQualifiers.foldRight(base) { qualifiers, inner ->
            Declarator.PointerDeclarator(ctx.location, qualifiers.toSet(), inner)
        }
        return Value.of(declarator)
    }

    override fun visitDirectDeclIdentifier(ctx: CParser.DirectDeclIdentifierContext): Value {
        return Value.of(Declarator.IdentifierDeclarator(ctx.location, ctx.Identifier().text))
    }

    override fun visitDirectDeclParenthesized(ctx: CParser.DirectDeclParenthesizedContext): Value {
        return visit(ctx.declarator())
    }

    override fun visitDirectDeclFunction(ctx: CParser.DirectDeclFunctionContext): Value {
        val inner = visit(ctx.direct_declarator()).cast<Declarator>()
        val params = ctx.parameter_type_list()?.let { visit(it).cast<List<Parameter>>() } ?: emptyList()
        return Value.of(Declarator.FunctionDeclarator(ctx.location, inner, params))
    }

    override fun visitDirectDeclArray(ctx: CParser.DirectDeclArrayContext): Value {
        val inner = visit(ctx.direct_declarator()).cast<Declarator>()
        val sizeCtx = ctx.assignment_expression()
        return Value.of(Declarator.ArrayDeclarator(ctx.location, inner, sizeCtx))
    }

    override fun visitDirectDeclBitField(ctx: CParser.DirectDeclBitFieldContext): Value {
        val name = ctx.Identifier().text
        val width = ctx.DigitSequence().text.toInt()
        return Value.of(Declarator.BitFieldDeclarator(ctx.location, name, width))
    }

    override fun visitPointer(ctx: CParser.PointerContext): Value {
        val pointer = ctx.pointer_part().map { visit(it).cast<List<TypeQualifier>>() }
        return Value.of(pointer)
    }

    override fun visitPointer_part(ctx: CParser.Pointer_partContext): Value {
        return Value.of(ctx.type_qualifier().map { parseTypeQualifier(it) })
    }

    override fun visitParamListNoParams(ctx: CParser.ParamListNoParamsContext): Value {
        return Value.of(emptyList<Parameter>())
    }

    override fun visitParamList(ctx: CParser.ParamListContext): Value {
        val params = ctx.parameter_list().parameter_declaration().map { visit(it).cast<Parameter>() }
        return Value.of(params)
    }

    override fun visitParamSpecDecl(ctx: CParser.ParamSpecDeclContext): Value {
        val declarationSpecifier = visit(ctx.declaration_specifiers()).cast<DeclarationSpecifier>()
        val declarator = visit(ctx.declarator()).cast<Declarator>()
        return Value.of(Parameter(ctx.location, declarationSpecifier, declarator))
    }

    override fun visitParamSpecAbstractDecl(ctx: CParser.ParamSpecAbstractDeclContext): Value {
        val declarationSpecifier = visit(ctx.declaration_specifiers_2()).cast<DeclarationSpecifier>()
        val declarator = visit(ctx.abstract_declarator()).cast<Declarator>()
        return Value.of(Parameter(ctx.location, declarationSpecifier, declarator))
    }

    override fun visitType_name(ctx: CParser.Type_nameContext): Value {
        val declarationSpecifier = visit(ctx.specifier_qualifier_list()).cast<DeclarationSpecifier>()
        val declarator = ctx.abstract_declarator()?.let { visit(it).cast<Declarator>() } ?: Declarator.AnonymousDeclarator(ctx.location)
        return Value.of(TypeName(ctx.location, declarationSpecifier, declarator))
    }

    override fun visitAbsDeclPointer(ctx: CParser.AbsDeclPointerContext): Value {
        val base: Declarator = Declarator.AnonymousDeclarator(ctx.location)
        val pointerQualifiers = visit(ctx.pointer()).cast<List<List<TypeQualifier>>>()
        val declarator = pointerQualifiers.foldRight(base) { qualifiers, inner ->
            Declarator.PointerDeclarator(ctx.location, qualifiers.toSet(), inner)
        }
        return Value.of(declarator)
    }

    override fun visitAbsDeclCompound(ctx: CParser.AbsDeclCompoundContext): Value {
        val base = visit(ctx.direct_abstract_declarator()).cast<Declarator>()
        val pointerQualifiers = ctx.pointer()?.let { visit(it).cast<List<List<TypeQualifier>>>() } ?: emptyList()
        val declarator = pointerQualifiers.foldRight(base) { qualifiers, inner ->
            Declarator.PointerDeclarator(ctx.location, qualifiers.toSet(), inner)
        }
        return Value.of(declarator)
    }

    override fun visitDirectAbsDeclParenthesized(ctx: CParser.DirectAbsDeclParenthesizedContext): Value {
        return visit(ctx.abstract_declarator())
    }

    override fun visitDirectAbsDeclArray(ctx: CParser.DirectAbsDeclArrayContext): Value {
        val inner = Declarator.AnonymousDeclarator(ctx.location)
        val sizeCtx = ctx.assignment_expression()
        return Value.of(Declarator.ArrayDeclarator(ctx.location, inner, sizeCtx))
    }

    override fun visitDirectAbsDeclFunctionSimple(ctx: CParser.DirectAbsDeclFunctionSimpleContext): Value {
        val inner = Declarator.AnonymousDeclarator(ctx.location)
        val params = ctx.parameter_type_list()?.let { visit(it).cast<List<Parameter>>() } ?: emptyList()
        return Value.of(Declarator.FunctionDeclarator(ctx.location, inner, params))
    }

    override fun visitDirectAbsDeclArrayCompound(ctx: CParser.DirectAbsDeclArrayCompoundContext): Value {
        val inner = visit(ctx.direct_abstract_declarator()).cast<Declarator>()
        val sizeCtx = ctx.assignment_expression()
        return Value.of(Declarator.ArrayDeclarator(ctx.location, inner, sizeCtx))
    }

    override fun visitDirectAbsDeclFunctionCompound(ctx: CParser.DirectAbsDeclFunctionCompoundContext): Value {
        val inner = visit(ctx.direct_abstract_declarator()).cast<Declarator>()
        val params = ctx.parameter_type_list()?.let { visit(it).cast<List<Parameter>>() } ?: emptyList()
        return Value.of(Declarator.FunctionDeclarator(ctx.location, inner, params))
    }

    override fun visitInitializer(ctx: CParser.InitializerContext): Value {
        return visit(ctx.assignment_expression())
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
            val operator = BinaryOperator.parse(op.text)
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
                            QualType(Type.Long(signed = true))  // ptrdiff_t
                        }

                        else -> usualArithmeticConversions(left.type, right.type)
                    }
                }

                else -> usualArithmeticConversions(left.type, right.type)
            }
            // Insert implicit conversions
            val convertedLeft = if (operator in setOf(BinaryOperator.LogicalAnd, BinaryOperator.LogicalOr)) {
                left
            } else {
                insertImplicitConversion(left, resultType)
            }
            val convertedRight = if (operator in setOf(BinaryOperator.LogicalAnd, BinaryOperator.LogicalOr)) {
                right
            } else {
                insertImplicitConversion(right, resultType)
            }
            left = BinaryExpression(
                ctx.location,
                operator,
                convertedLeft,
                convertedRight,
                resultType,
            )
        }
        return left
    }

    private fun buildUnaryOp(
        location: SourceLocation,
        operator: UnaryOperator,
        operand: Expression,
    ): Expression {
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

            UnaryOperator.PrefixIncrement, UnaryOperator.PrefixDecrement,
            UnaryOperator.PostfixIncrement, UnaryOperator.PostfixDecrement,
            -> {
                if (!isScalarType(operand.type)) {
                    reporter.reportError(location, "operand must have scalar type")
                }
                operand.type
            }
        }
        return UnaryExpression(location, operator, operand, resultType)
    }

    private fun buildArraySubscript(location: SourceLocation, array: Expression, index: Expression): Expression {
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

    private fun buildFunctionCall(location: SourceLocation, function: Expression, arguments: List<Expression>): Expression {
        val funcType = when (val canonical = function.type.canonical.type) {
            is Type.Function -> canonical
            is Type.Pointer -> {
                when (val pointee = canonical.pointee.canonical.type) {
                    is Type.Function -> pointee
                    else -> {
                        reporter.reportError(location, "called object is not a function")
                        return CallExpression(location, function, arguments, null, QualType(Type.Error))
                    }
                }
            }

            else -> {
                reporter.reportError(location, "called object is not a function")
                return CallExpression(location, function, arguments, null, QualType(Type.Error))
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
            insertImplicitConversion(arg, paramType)
        }
        // Try to get function symbol if this is a direct function reference
        val functionSymbol = if (function is VariableReference) {
            function.symbol.entity.scope.lookupFunctionEntity(function.name)?.let {
                symbolTable.getAllFunctions().find { func -> func.entity == it }
            }
        } else {
            null
        }
        return CallExpression(location, function, convertedArgs, functionSymbol, funcType.returnType)
    }

    private fun buildMemberAccess(location: SourceLocation, struct: Expression, memberName: String): Expression {
        val structType = struct.type.canonical.type
        if (structType !is Type.Struct) {
            reporter.reportError(location, "member access requires struct type, got '${struct.type}'")
            return MemberAccessExpression(location, struct, memberName, -1, QualType(Type.Error))
        }
        val memberIndex = structType.symbol.members.indexOfFirst { it.name == memberName }
        if (memberIndex == -1) {
            reporter.reportError(location, "struct has no member named '$memberName'")
            return MemberAccessExpression(location, struct, memberName, -1, QualType(Type.Error))
        }
        val member = structType.symbol.members[memberIndex]
        return MemberAccessExpression(location, struct, memberName, memberIndex, member.type)
    }

    private fun buildPointerMemberAccess(location: SourceLocation, pointer: Expression, memberName: String): Expression {
        val pointerType = pointer.type.canonical.type

        if (pointerType !is Type.Pointer) {
            reporter.reportError(location, "pointer member access requires pointer type")
            return PointerMemberAccessExpression(location, pointer, memberName, -1, QualType(Type.Error))
        }

        val structType = pointerType.pointee.canonical.type
        if (structType !is Type.Struct) {
            reporter.reportError(location, "pointer member access requires pointer to struct")
            return PointerMemberAccessExpression(location, pointer, memberName, -1, QualType(Type.Error))
        }

        val memberIndex = structType.symbol.members.indexOfFirst { it.name == memberName }
        if (memberIndex == -1) {
            reporter.reportError(location, "struct has no member named '$memberName'")
            return PointerMemberAccessExpression(location, pointer, memberName, -1, QualType(Type.Error))
        }

        val member = structType.symbol.members[memberIndex]
        return PointerMemberAccessExpression(location, pointer, memberName, memberIndex, member.type)
    }

    private fun lookupIdentifier(location: SourceLocation, name: String): Expression {
        // Try enum constant first
        symbolTable.lookupEnumConstantSymbol(name)?.let { enumConst ->
            return IntegerLiteralExpression(
                location = location,
                value = enumConst.value,
                type = QualType(Type.Int(signed = true)),
            )
        }

        // Try variable lookup
        val scope = currentScope ?: run {
            reporter.reportError(location, "no scope available")
            return VariableReference(
                location,
                name,
                VariableSymbol(
                    "",
                    QualType(Type.Error),
                    emptySet(),
                    Linkage.NONE,
                    Scope(ScopeKind.FILE, null),
                    Entity.Variable(Scope(ScopeKind.FILE, null), ""),
                ),
                QualType(Type.Error),
            )
        }

        val entity = scope.lookupVariableEntity(name)
        if (entity == null) {
            reporter.reportError(location, "undefined identifier '$name'")
            return VariableReference(
                location,
                name,
                VariableSymbol(
                    "",
                    QualType(Type.Error),
                    emptySet(),
                    Linkage.NONE,
                    scope,
                    Entity.Variable(scope, ""),
                ),
                QualType(Type.Error),
            )
        }

        // Find the symbol for this entity
        val symbol = symbolTable.getAllVariables().find { it.entity == entity }
            ?: run {
                reporter.reportError(location, "symbol not found for '$name'")
                return VariableReference(
                    location,
                    name,
                    VariableSymbol(
                        "",
                        QualType(Type.Error),
                        emptySet(),
                        Linkage.NONE,
                        scope,
                        entity,
                    ),
                    QualType(Type.Error),
                )
            }
        return VariableReference(location, name, symbol, symbol.type)
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

    private fun insertImplicitConversion(expr: Expression, targetType: QualType): Expression {
        if (expr.type.canonical == targetType.canonical) {
            return expr
        }
        val castKind = determineCastKind(expr.type, targetType)
        return ImplicitCastExpression(expr.location, castKind, expr, targetType)
    }

    private fun determineCastKind(fromType: QualType, toType: QualType): CastKind {
        val from = fromType.canonical.type
        val to = toType.canonical.type

        return when {
            from == to -> CastKind.NO_OP

            from is Type.Array -> CastKind.ARRAY_TO_POINTER
            from is Type.Function -> CastKind.FUNCTION_TO_POINTER

            isIntegerType(fromType) && isIntegerType(toType) -> CastKind.INTEGRAL_CAST
            isIntegerType(fromType) && isFloatingType(toType) -> CastKind.INTEGRAL_TO_FLOATING
            isFloatingType(fromType) && isIntegerType(toType) -> CastKind.FLOATING_TO_INTEGRAL
            isFloatingType(fromType) && isFloatingType(toType) -> CastKind.FLOATING_CAST

            isPointerType(fromType) && isIntegerType(toType) -> CastKind.POINTER_TO_INTEGRAL
            isIntegerType(fromType) && isPointerType(toType) -> CastKind.INTEGRAL_TO_POINTER
            isPointerType(fromType) && isPointerType(toType) -> CastKind.POINTER_TO_POINTER

            else -> CastKind.NO_OP
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

    private fun computeTypeSize(type: QualType): Long {
        return when (val canonical = type.canonical.type) {
            is Type.Void -> 1
            is Type.Bool -> 1
            is Type.Char -> 1
            is Type.Short -> 2
            is Type.Int -> 4
            is Type.Long -> 8
            is Type.LongLong -> 8
            is Type.Float -> 4
            is Type.Double -> 8
            is Type.LongDouble -> 16
            is Type.Pointer -> 8
            is Type.Array -> {
                val elementSize = computeTypeSize(canonical.elementType)
                (canonical.size ?: 0) * elementSize
            }

//            is Type.Struct -> canonical.symbol.size ?: 0
//            is Type.Enum -> canonical.symbol.size ?: 0

            is Type.Function -> {
                reporter.reportError(UnknownLocation, "cannot compute size of function type")
                0
            }

            is Type.Error -> 0
        }
    }

    private fun Value.toBlockStatement(location: SourceLocation): BlockStatement {
        return this.tryCast<BlockStatement>() ?: BlockStatement(location, listOf(this.cast<Statement>()))
    }

    private fun parseStorageClassSpec(ctx: CParser.Storage_class_specifierContext): StorageClass {
        return when {
            ctx.Typedef() != null -> StorageClass.TYPEDEF
            ctx.Extern() != null -> StorageClass.EXTERN
            ctx.Static() != null -> StorageClass.STATIC
            ctx.ThreadLocal() != null -> StorageClass.THREAD_LOCAL
            ctx.Auto() != null -> StorageClass.AUTO
            ctx.Register() != null -> StorageClass.REGISTER
            else -> throw TypeException("Invalid storage class spec: ${ctx.text}")
        }
    }

    private fun parseTypeSpec(ctx: CParser.Type_specifierContext): TypeSpec {
        if (ctx.typedef_name() != null) {
            return TypeSpec.TypedefName(ctx.typedef_name().text)
        }
        ctx.struct_specifier()?.let {
            return TypeSpec.Struct(it.Identifier()?.text)
        }
        ctx.enum_specifier()?.let {
            return TypeSpec.Enum(it.Identifier()?.text)
        }
        return when {
            ctx.Void() != null -> TypeSpec.VOID
            ctx.Char() != null -> TypeSpec.CHAR
            ctx.Short() != null -> TypeSpec.SHORT
            ctx.Int() != null -> TypeSpec.INT
            ctx.Long() != null -> TypeSpec.LONG
            ctx.Float() != null -> TypeSpec.FLOAT
            ctx.Double() != null -> TypeSpec.DOUBLE
            ctx.Signed() != null -> TypeSpec.SIGNED
            ctx.Unsigned() != null -> TypeSpec.UNSIGNED
            else -> throw TypeException("Invalid type spec: ${ctx.text}")
        }
    }

    private fun parseTypeQualifier(ctx: CParser.Type_qualifierContext): TypeQualifier {
        return when {
            ctx.Const() != null -> TypeQualifier.CONST
            ctx.Volatile() != null -> TypeQualifier.VOLATILE
            ctx.Restrict() != null -> TypeQualifier.RESTRICT
            else -> throw TypeException("Invalid type spec: ${ctx.text}")
        }
    }

    private fun parseFunctionSpec(ctx: CParser.Function_specifierContext): FunctionSpec {
        return when {
            ctx.Inline() != null -> FunctionSpec.INLINE
            else -> throw TypeException("Invalid function spec: ${ctx.text}")
        }
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

    private fun resolveTypeName(typeName: TypeName): QualType {
    }

    private fun reportErrorNode(location: SourceLocation, string: String): Value {
    }
}
