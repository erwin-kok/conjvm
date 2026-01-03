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
import org.erwinkok.conjvm.ast.statements.SwitchCaseStatement
import org.erwinkok.conjvm.ast.statements.SwitchDefaultStatement
import org.erwinkok.conjvm.ast.statements.SwitchStatement
import org.erwinkok.conjvm.ast.statements.VariableDeclarationStatement
import org.erwinkok.conjvm.ast.statements.WhileStatement

class TypeContext

class TypeVisitor :
    AstStatementVisitor<Unit, TypeContext>,
    AstExpressionVisitor<Type, TypeContext> {
    private var currentReturn: Type = Type.Void
    private val typedefTable = mutableMapOf<String, QualType>()
    private var scope = Scope()

    init {
        typedefTable["uint"] = QualType(Type.Int(false))
        typedefTable["uint16"] = QualType(Type.Short(false))
        typedefTable["uint32"] = QualType(Type.Int(false))
        typedefTable["uint64"] = QualType(Type.Long(false))

        typedefTable["sint"] = QualType(Type.Int(true))
        typedefTable["sint16"] = QualType(Type.Short(true))
        typedefTable["sint32"] = QualType(Type.Int(true))
        typedefTable["sint64"] = QualType(Type.Long(true))

        typedefTable["m68ki_bitfield_t"] = QualType(Type.Struct("m68ki_bitfield_t", emptyList()))
    }

    override fun visitCompilationUnit(statement: CompilationUnitStatement, ctx: TypeContext) {
        statement.variableDeclarations.forEach {
            defineVariableDeclaration(it)
        }
        statement.functionDefinitions.forEach {
            defineFunctionDefinition(it)
        }
        statement.functionDefinitions.forEach {
            visit(it, ctx)
        }
    }

    override fun visitFunctionDefinition(definition: FunctionDefinitionStatement, ctx: TypeContext) {
        val oldReturn = currentReturn
//        currentReturn = definition.returnType
//
        enterScope()
//        definition.params.forEach {
//            Scope.current.define(Symbol(it.name, it.type))
//        }

        visit(definition.statements, ctx)
        leaveScope()

//        currentReturn = oldReturn
    }

    override fun visitBlock(statement: BlockStatement, ctx: TypeContext) {
        enterScope()
        statement.statements.forEach { visit(it, ctx) }
        leaveScope()
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
            if (currentReturn != Type.Void) {
                error("missing return value")
            }
        } else {
//            val t = visit(statement.value, ctx)
//            if (!sameType(t, currentReturn)) {
//                error("return type mismatch")
//            }
        }
    }

    override fun visitSwitch(statement: SwitchStatement, ctx: TypeContext) {
        visit(statement.test, ctx)
        statement.sections.forEach { visitSwitchCase(it, ctx) }
        statement.defaultSection?.let { visitDefaultCase(it, ctx) }
    }

    override fun visitVariableDeclaration(statement: VariableDeclarationStatement, ctx: TypeContext) {
        defineVariableDeclaration(statement)
    }

    override fun visitWhile(statement: WhileStatement, ctx: TypeContext) {
        visit(statement.condition, ctx)
        visit(statement.statements, ctx)
    }

    override fun visitArrayAccess(expression: ArrayAccessExpression, ctx: TypeContext): Type {
        // TODO("Not yet implemented")
        return Type.Error
    }

    override fun visitAssignment(expression: AssignmentExpression, ctx: TypeContext): Type {
        // TODO("Not yet implemented")
        return Type.Error
    }

    override fun visitBinary(expression: BinaryExpression, ctx: TypeContext): Type {
        // TODO("Not yet implemented")
        return Type.Error
    }

    override fun visitCall(expression: CallExpression, ctx: TypeContext): Type {
        // TODO("Not yet implemented")
        return Type.Error
    }

    override fun visitCast(expression: CastExpression, ctx: TypeContext): Type {
        return visit(expression.expression, ctx)
    }

    override fun visitConstantInt(expression: ConstantIntExpression, ctx: TypeContext): Type {
        val type = Type.Int(true)
        expression.expressionType = type
        return type
    }

    override fun visitConstantLong(expression: ConstantLongExpression, ctx: TypeContext): Type {
        val type = Type.Int(true)
        expression.expressionType = type
        return type
    }

    override fun visitConstantString(expression: ConstantStringExpression, ctx: TypeContext): Type {
        // TODO("Not yet implemented")
        return Type.Error
    }

    override fun visitFieldAccess(expression: FieldAccessExpression, ctx: TypeContext): Type {
        // TODO("Not yet implemented")
        return Type.Error
    }

    override fun visitIdentifier(identifier: Identifier, ctx: TypeContext): Type {
//        val symbol = Scope.current.lookup(identifier.name)
//        return if (symbol == null) {
//        error("undeclared variable ${identifier.name}")
//            Type.Error
//        } else {
//            identifier.expressionType = symbol.type
//            symbol.type
//        }
        return Type.Error
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
        return Type.Error
    }

    override fun visitUnary(expression: UnaryExpression, ctx: TypeContext): Type {
        // TODO("Not yet implemented")
        return Type.Error
    }

    private fun visitSwitchCase(case: SwitchCaseStatement, ctx: TypeContext) {
        visit(case.test, ctx)
        visit(case.blockStatement, ctx)
    }

    private fun visitDefaultCase(default: SwitchDefaultStatement, ctx: TypeContext) {
        visit(default.blockStatement, ctx)
    }

    private fun enterScope() {
        scope = Scope(scope)
    }

    private fun leaveScope() {
        val parent = scope.parent
        requireNotNull(parent)
        scope = parent
    }

    private fun assignable(left: QualType, right: QualType): Boolean {
        return left.canonical.isCompatibleWith(right.canonical)
    }

    private fun lookupVariable(name: String): VariableSymbol {
        val sym = scope.resolve(name)
        return sym as? VariableSymbol ?: throw TypeException("unknown variable '$name'")
    }

    private fun lookupFunction(name: String): FunctionSymbol {
        val sym = scope.resolve(name)
        return sym as? FunctionSymbol ?: throw TypeException("unknown function '$name'")
    }

    private fun defineVariableDeclaration(stmt: VariableDeclarationStatement) {
        for (varDecl in stmt.variableDeclarators) {
            val qt = resolveType(stmt.declarationSpecifier, varDecl.declarator)
            val variableSymbol = VariableSymbol(
                varDecl.declarator.name(),
                qt,
                stmt.declarationSpecifier.storage,
            )
            val oldSym = scope.resolve(variableSymbol.name)
            if (oldSym != null && oldSym != variableSymbol) {
                throw TypeException("variable re-definition of ${oldSym.name} is different from ${variableSymbol.name}")
            }
            scope.define(variableSymbol)
        }
    }

    private fun defineFunctionDefinition(stmt: FunctionDefinitionStatement) {
        require(stmt.declarationSpecifier != null)
        val qt = resolveType(stmt.declarationSpecifier, stmt.declarator)
        val functionSymbol = FunctionSymbol(
            stmt.declarator.name(),
            qt,
            stmt.declarationSpecifier.storage,
            stmt.statements,
        )
        val oldSym = scope.resolve(functionSymbol.name)
        if (oldSym != null && oldSym != functionSymbol) {
            throw TypeException("function re-definition of ${oldSym.name} is different from ${functionSymbol.name}")
        }
        scope.define(functionSymbol)
    }

    private fun resolveType(declSpec: DeclarationSpecifier, declarator: Declarator?): QualType {
        val base = buildBaseType(declSpec)
        val fullType = declarator?.let { applyDeclarator(base, it) } ?: base
        validateType(fullType)
        return fullType
    }

    private fun buildBaseType(declSpec: DeclarationSpecifier): QualType {
        val specs = declSpec.typeSpecs

        // Typedef handling
        val typedefs = specs.filterIsInstance<TypeSpec.TypedefName>()
        if (typedefs.isNotEmpty()) {
            if (typedefs.size != 1) {
                throw TypeException("multiple typedef names in declaration")
            }
            if (specs.size > 1) {
                throw TypeException("typedef name mixed with type specifiers")
            }
            val name = typedefs.single().name
            val qt = typedefTable[name] ?: throw TypeException("unknown typedef '$name'")
            return qt.copy(qualifiers = qt.qualifiers + declSpec.qualifiers)
        }
        // Determine signed/unsigned
        val signed = specs.contains(TypeSpec.SIGNED) || !specs.contains(TypeSpec.UNSIGNED)
        // Count integer modifiers
        val longCount = specs.count { it == TypeSpec.LONG }
        val shortCount = specs.count { it == TypeSpec.SHORT }
        val baseType = when {
            specs.contains(TypeSpec.VOID) -> {
                if (specs.size > 1) {
                    throw TypeException("invalid type specifier: ${"void cannot be combined"}")
                }
                Type.Void
            }

            specs.contains(TypeSpec.FLOAT) -> {
                if (specs.any { it == TypeSpec.SIGNED || it == TypeSpec.UNSIGNED }) {
                    throw TypeException("invalid type specifier: ${"float cannot be signed/unsigned"}")
                }
                Type.Float
            }

            specs.contains(TypeSpec.DOUBLE) -> {
                if (longCount > 0) {
                    throw TypeException("invalid type specifier: ${"long double not supported yet"}")
                }
                Type.Double
            }

            specs.contains(TypeSpec.CHAR) -> {
                if (longCount > 0 || shortCount > 0) {
                    throw TypeException("invalid type specifier: ${"char cannot be long/short"}")
                }
                Type.Char(signed)
            }

            shortCount > 0 -> {
                if (longCount > 0) {
                    throw TypeException("invalid type specifier: ${"short and long together"}")
                }
                Type.Short(signed)
            }

            longCount == 1 -> Type.Long(signed)
            longCount == 2 -> Type.LongLong(signed)
            longCount > 2 -> throw TypeException("invalid type specifier: ${"too many long specifiers"}")

            else -> Type.Int(signed) // default int
        }
        return QualType(baseType, declSpec.qualifiers)
    }

    private fun applyDeclarator(baseType: QualType, declarator: Declarator): QualType {
        return when (declarator) {
            is Declarator.IdentifierDeclarator -> {
                baseType
            }

            is Declarator.PointerDeclarator -> {
                val inner = applyDeclarator(baseType, declarator.pointee)
                QualType(Type.Pointer(inner), declarator.qualifiers)
            }

            is Declarator.ArrayDeclarator -> {
                val inner = applyDeclarator(baseType, declarator.elementType)
                QualType(Type.Array(inner, evalSize(declarator.size)))
            }

            is Declarator.FunctionDeclarator -> {
                val returnType = applyDeclarator(baseType, declarator.declarator)
                val params = declarator.parameters.map { p ->
                    val qt = resolveType(p.declarationSpecifier, p.declarator)
                    when (qt.type) {
                        is Type.Array -> QualType(Type.Pointer(qt.type.elementType))
                        is Type.Function -> QualType(Type.Pointer(qt))
                        else -> qt
                    }
                }
                QualType(Type.Function(returnType, params))
            }
        }
    }

    private fun evalSize(size: Expression?): Long? {
        if (size == null) return null
        if (size is ConstantIntExpression) return size.value.toLong()
        if (size is ConstantLongExpression) return size.value
        throw TypeException("array size must be a compile time constant")
    }

    private fun validateType(qt: QualType) {
        if (TypeQualifier.RESTRICT in qt.qualifiers && qt.type !is Type.Pointer) {
            throw TypeException("restrict qualifier requires pointer type")
        }
        if (qt.type is Type.Function && qt.qualifiers.isNotEmpty()) {
            throw TypeException("function type may not be qualified")
        }
        if (qt.type is Type.Void) {
            throw TypeException("object declared with type void")
        }
        validateRecursive(qt.type)
    }

    private fun validateRecursive(type: Type) {
        when (type) {
            is Type.Pointer -> {
                validateRecursive(type.pointee.type)
            }

            is Type.Array -> {
                if (type.elementType.type is Type.Function) {
                    throw TypeException("array of functions is illegal")
                }
                validateRecursive(type.elementType.type)
            }

            is Type.Function -> {
                if (type.returnType.type is Type.Array) {
                    throw TypeException("function returning array is illegal")
                }
                validateRecursive(type.returnType.type)
            }

            else -> {}
        }
    }
}
