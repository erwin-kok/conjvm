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
import org.erwinkok.conjvm.declarations.EntityTable
import org.erwinkok.conjvm.declarations.FunctionSpec
import org.erwinkok.conjvm.declarations.Parameter
import org.erwinkok.conjvm.declarations.StorageClass
import org.erwinkok.conjvm.declarations.TypeName
import org.erwinkok.conjvm.declarations.TypeQualifier
import org.erwinkok.conjvm.declarations.TypeSpec
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.SourceFile
import org.erwinkok.conjvm.parser.SourceLocation
import org.erwinkok.conjvm.types.TypeException
import org.erwinkok.conjvm.utils.ParserReporting
import org.erwinkok.conjvm.utils.Value

class AstBuilder(
    override val reporter: ErrorReporter,
    override val source: SourceFile,
    private val entityTable: EntityTable,
) : CBaseVisitor<Value>(),
    ParserReporting {
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
        return Value.of(
            AssignmentExpression(
                ctx.location,
                AssignmentExpressionType.parse(ctx.assignment_operator().text),
                visit(ctx.unary_expression()).cast<Expression>(),
                visit(ctx.assignment_expression()).cast<Expression>(),
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
        return Value.of(buildLeftAssociativeBinaryExpression(ctx, ctx.left, ctx.op, ctx.right))
    }

    override fun visitLogical_and_expression(ctx: CParser.Logical_and_expressionContext): Value {
        return Value.of(buildLeftAssociativeBinaryExpression(ctx, ctx.left, ctx.op, ctx.right))
    }

    override fun visitInclusive_or_expression(ctx: CParser.Inclusive_or_expressionContext): Value {
        return Value.of(buildLeftAssociativeBinaryExpression(ctx, ctx.left, ctx.op, ctx.right))
    }

    override fun visitExclusive_or_expression(ctx: CParser.Exclusive_or_expressionContext): Value {
        return Value.of(buildLeftAssociativeBinaryExpression(ctx, ctx.left, ctx.op, ctx.right))
    }

    override fun visitAnd_expression(ctx: CParser.And_expressionContext): Value {
        return Value.of(buildLeftAssociativeBinaryExpression(ctx, ctx.left, ctx.op, ctx.right))
    }

    override fun visitEquality_expression(ctx: CParser.Equality_expressionContext): Value {
        return Value.of(buildLeftAssociativeBinaryExpression(ctx, ctx.left, ctx.op, ctx.right))
    }

    override fun visitRelational_expression(ctx: CParser.Relational_expressionContext): Value {
        return Value.of(buildLeftAssociativeBinaryExpression(ctx, ctx.left, ctx.op, ctx.right))
    }

    override fun visitShift_expression(ctx: CParser.Shift_expressionContext): Value {
        return Value.of(buildLeftAssociativeBinaryExpression(ctx, ctx.left, ctx.op, ctx.right))
    }

    override fun visitAdditive_expression(ctx: CParser.Additive_expressionContext): Value {
        return Value.of(buildLeftAssociativeBinaryExpression(ctx, ctx.left, ctx.op, ctx.right))
    }

    override fun visitMultiplicative_expression(ctx: CParser.Multiplicative_expressionContext): Value {
        return Value.of(buildLeftAssociativeBinaryExpression(ctx, ctx.left, ctx.op, ctx.right))
    }

    override fun visitSimpleCast(ctx: CParser.SimpleCastContext): Value {
        return visit(ctx.unary_expression())
    }

    override fun visitCastExpr(ctx: CParser.CastExprContext): Value {
        val typeName = visit(ctx.type_name()).cast<TypeName>()
        val nodeResult = visit(ctx.cast_expression()).cast<Expression>()
        return Value.of(CastExpression(ctx.location, typeName, nodeResult))
    }

    override fun visitCastWithLiteral(ctx: CParser.CastWithLiteralContext): Value {
        return Value.of(parseConstant(ctx.location, ctx.DigitSequence().text))
    }

    override fun visitUnary_expression(ctx: CParser.Unary_expressionContext): Value {
        val coreExpr = visit(ctx.unary_core()).cast<Expression>()
        return Value.of(
            ctx.prefix_operator()
                .asReversed()
                .fold(coreExpr) { acc, op ->
                    when (op) {
                        is CParser.PrefixIncrementContext -> UnaryExpression(op.location, UnaryType.PlusPlus, acc)
                        is CParser.PrefixDecrementContext -> UnaryExpression(op.location, UnaryType.MinusMinus, acc)
                        is CParser.PrefixSizeofContext -> error("sizeof operator is currently not supported")
                        else -> error("Unexpected prefix operator ${op.javaClass}")
                    }
                },
        )
    }

    override fun visitCompoundUnaryCore(ctx: CParser.CompoundUnaryCoreContext): Value {
        val operator = UnaryType.parse(ctx.unary_operator().text)
        val operand = visit(ctx.cast_expression()).cast<Expression>()
        return Value.of(UnaryExpression(ctx.location, operator, operand))
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
                .fold(visit(ctx.primary_expression()).cast<Expression>()) { acc, suffix ->
                    when (suffix) {
                        is CParser.PostfixArrayAccessContext -> {
                            ArrayAccessExpression(ctx.location, acc, visit(suffix.index).cast<Expression>())
                        }

                        is CParser.PostfixFunctionCallContext -> {
                            val argumentList = suffix.args?.assignment_expression()?.map { visit(it).cast<Expression>() } ?: emptyList()
                            CallExpression(ctx.location, acc, argumentList)
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
        val ex = ctx.expression()?.let { ExpressionStatement(ctx.location, visit(it).cast<Expression>()) } ?: BlockStatement(ctx.location, emptyList())
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

    private fun buildLeftAssociativeBinaryExpression(
        ctx: ParserRuleContext,
        left: ParserRuleContext,
        operators: List<Token>,
        rights: List<ParserRuleContext>,
    ): Expression {
        var result = visit(left).cast<Expression>()
        for ((op, right) in operators.zip(rights)) {
            result = BinaryExpression(
                ctx.location,
                BinaryExpressionType.parse(op.text),
                result,
                visit(right).cast<Expression>(),
            )
        }
        return result
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
}
