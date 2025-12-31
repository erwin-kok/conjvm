package org.erwinkok.conjvm.ast.types

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
import org.erwinkok.conjvm.ast.statements.SwitchCaseStatement
import org.erwinkok.conjvm.ast.statements.SwitchDefaultStatement
import org.erwinkok.conjvm.ast.statements.SwitchStatement
import org.erwinkok.conjvm.ast.statements.VariableDeclarationStatement
import org.erwinkok.conjvm.ast.statements.WhileStatement

class TypeContext

class TypeVisitor :
    AstStatementVisitor<Unit, TypeContext>,
    AstExpressionVisitor<Type, TypeContext> {
    private var currentReturn: Type = Type.TVoid

    private val typedefTable = mutableMapOf<String, QualType>()

    init {
        typedefTable["uint"] = QualType(Type.Builtin.TInt(false, 32))
        typedefTable["uint16"] = QualType(Type.Builtin.TInt(false, 16))
        typedefTable["uint32"] = QualType(Type.Builtin.TInt(false, 32))
        typedefTable["uint64"] = QualType(Type.Builtin.TInt(false, 64))

        typedefTable["sint"] = QualType(Type.Builtin.TInt(true, 32))
        typedefTable["sint16"] = QualType(Type.Builtin.TInt(true, 16))
        typedefTable["sint32"] = QualType(Type.Builtin.TInt(true, 32))
        typedefTable["sint64"] = QualType(Type.Builtin.TInt(true, 64))

        typedefTable["m68ki_bitfield_t"] = QualType(Type.XXX())
    }

    override fun visitCompilationUnit(statement: CompilationUnitStatement, ctx: TypeContext) {
        statement.functionDefinitions.forEach {
            declareFunction(it)
        }
        statement.functionDefinitions.forEach {
            visit(it, ctx)
        }
    }

    override fun visitFunctionDefinition(definition: FunctionDefinitionStatement, ctx: TypeContext) {
        val oldReturn = currentReturn
        currentReturn = definition.returnType

        Scope.enter()
        definition.params.forEach {
            Scope.current.define(Symbol(it.name, it.type))
        }

        visit(definition.statements, ctx)
        Scope.leave()

        currentReturn = oldReturn
    }

    override fun visitBlock(statement: BlockStatement, ctx: TypeContext) {
        Scope.enter()
        statement.statements.forEach { visit(it, ctx) }
        Scope.leave()
    }

    override fun visitBreak(statement: BreakStatement, ctx: TypeContext) {
        // Nothing
    }

    override fun visitContinue(statement: ContinueStatement, ctx: TypeContext) {
        // Nothing
    }

    override fun visitExpression(statement: ExpressionStatement, ctx: TypeContext) {
        visit(statement.expression, ctx)
    }

    override fun visitFor(statement: ForStatement, ctx: TypeContext) {
        statement.condition?.let { visit(it, ctx) }
        statement.iterators?.let { it.forEach { ex -> visit(ex, ctx) } }
        visit(statement.statements, ctx)
    }

    override fun visitGoto(statement: GotoStatement, ctx: TypeContext) {
        // Nothing
    }

    override fun visitIfThenElse(statement: IfThenElseStatement, ctx: TypeContext) {
        visit(statement.test, ctx)
        visit(statement.thenBlock, ctx)
        visit(statement.elseBlock, ctx)
    }

    override fun visitIfThen(statement: IfThenStatement, ctx: TypeContext) {
        visit(statement.test, ctx)
        visit(statement.thenBlock, ctx)
    }

    override fun visitLabeled(statement: LabeledStatement, ctx: TypeContext) {
        visit(statement.statement, ctx)
    }

    override fun visitReturn(statement: ReturnStatement, ctx: TypeContext) {
        if (statement.value == null) {
            if (currentReturn != Type.TVoid) {
                error("missing return value")
            }
        } else {
            val t = visit(statement.value, ctx)
            if (!sameType(t, currentReturn)) {
                error("return type mismatch")
            }
        }
    }

    override fun visitSwitch(statement: SwitchStatement, ctx: TypeContext) {
        visit(statement.test, ctx)
        statement.sections.forEach { visitSwitchCase(it, ctx) }
        statement.defaultSection?.let { visitDefaultCase(it, ctx) }
    }

    override fun visitVariableDeclaration(statement: VariableDeclarationStatement, ctx: TypeContext) {
        // TODO("Not yet implemented")
    }

    override fun visitWhile(statement: WhileStatement, ctx: TypeContext) {
        visit(statement.condition, ctx)
        visit(statement.statements, ctx)
    }

    override fun visitArrayAccess(expression: ArrayAccessExpression, ctx: TypeContext): Type {
        // TODO("Not yet implemented")
        return Type.TError
    }

    override fun visitAssignment(expression: AssignmentExpression, ctx: TypeContext): Type {
        // TODO("Not yet implemented")
        return Type.TError
    }

    override fun visitBinary(expression: BinaryExpression, ctx: TypeContext): Type {
        // TODO("Not yet implemented")
        return Type.TError
    }

    override fun visitCall(expression: CallExpression, ctx: TypeContext): Type {
        // TODO("Not yet implemented")
        return Type.TError
    }

    override fun visitCast(expression: CastExpression, ctx: TypeContext): Type {
        return visit(expression.expression, ctx)
    }

    override fun visitConstantInt(expression: ConstantIntExpression, ctx: TypeContext): Type {
        expression.expressionType = Type.TInt
        return Type.TInt
    }

    override fun visitConstantLong(expression: ConstantLongExpression, ctx: TypeContext): Type {
        expression.expressionType = Type.TLong
        return Type.TLong
    }

    override fun visitConstantString(expression: ConstantStringExpression, ctx: TypeContext): Type {
        expression.expressionType = Type.TString
        return Type.TString
    }

    override fun visitFieldAccess(expression: FieldAccessExpression, ctx: TypeContext): Type {
        // TODO("Not yet implemented")
        return Type.TError
    }

    override fun visitIdentifier(identifier: Identifier, ctx: TypeContext): Type {
        val symbol = Scope.current.lookup(identifier.name)
        return if (symbol == null) {
//            error("undeclared variable ${identifier.name}")
            Type.TError
        } else {
            identifier.expressionType = symbol.type
            symbol.type
        }
    }

    override fun visitParenthesized(expression: ParenthesizedExpression, ctx: TypeContext): Type {
        return visit(expression.expression, ctx)
    }

    override fun visitPostfixDecrement(expression: PostfixDecrementExpression, ctx: TypeContext): Type {
        return visit(expression.expression, ctx)
    }

    override fun visitPostfixIncrement(expression: PostfixIncrementExpression, ctx: TypeContext): Type {
        return visit(expression.expression, ctx)
    }

    override fun visitTernary(expression: TernaryExpression, ctx: TypeContext): Type {
        // TODO("Not yet implemented")
        return Type.TError
    }

    override fun visitUnary(expression: UnaryExpression, ctx: TypeContext): Type {
        // TODO("Not yet implemented")
        return Type.TError
    }

    private fun declareFunction(function: FunctionDefinitionStatement) {
        Scope.current.define(Symbol(function.name, Type.TFunc(function.returnType, function.params.map { it.type })))
    }

    private fun visitSwitchCase(case: SwitchCaseStatement, ctx: TypeContext) {
        visit(case.test, ctx)
        visit(case.blockStatement, ctx)
    }

    private fun visitDefaultCase(default: SwitchDefaultStatement, ctx: TypeContext) {
        visit(default.blockStatement, ctx)
    }

    private fun buildBaseType(declSpec: DeclarationSpecifier): QualType {
        val typedefs = declSpec.typeSpecs.filterIsInstance<TypeSpec.TypedefName>()
        if (typedefs.isNotEmpty()) {
            if (typedefs.size != 1) {
                throw TypeException("multiple typedef names in declaration")
            }
            if (declSpec.typeSpecs.size > 1) {
                throw TypeException("typedef name mixed with type specifiers")
            }
            val name = typedefs.single().name
            val qt = typedefTable[name] ?: throw TypeException("unknown typedef '$name'")
            return qt.copy(qualifiers = declSpec.qualifiers)
        }
        val signed = !declSpec.typeSpecs.contains(TypeSpec.UNSIGNED)
        val base = when {
            declSpec.typeSpecs.contains(TypeSpec.VOID) -> Type.Builtin.TVoid
            declSpec.typeSpecs.contains(TypeSpec.FLOAT) -> Type.Builtin.TFloat
            declSpec.typeSpecs.contains(TypeSpec.DOUBLE) -> Type.Builtin.TDouble
            else -> {
                val longCount = declSpec.typeSpecs.count { it == TypeSpec.LONG }
                val width = when (longCount) {
                    0 -> 32
                    1 -> 32
                    2 -> 64
                    else -> throw TypeException("too many longs in declaration specifier")
                }
                Type.Builtin.TInt(signed, width)
            }
        }
        return QualType(base, declSpec.qualifiers)
    }
}
