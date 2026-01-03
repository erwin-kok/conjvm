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
import org.erwinkok.conjvm.ast.expressions.UnaryType
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

class TypeVisitor(
    private val symbols: SymbolTable,
) : AstStatementVisitor<Unit, TypeContext>,
    AstExpressionVisitor<ExpressionType, TypeContext> {
    private var currentReturn: Type = Type.Void
    private var scope = Scope()
    private val globalScope = scope

    val expressionTypeSystem = ExpressionTypeSystem(this)

    override fun visitCompilationUnit(statement: CompilationUnitStatement, ctx: TypeContext) {
        statement.variableDeclarations.forEach { defineGlobalVariable(it) }
        statement.functionDefinitions.forEach { defineGlobalFunction(it) }

        statement.functionDefinitions.forEach {
            visit(it, ctx)
        }
    }

    override fun visitFunctionDefinition(definition: FunctionDefinitionStatement, ctx: TypeContext) {
        // Save the old return type
        val oldReturn = currentReturn

        // Resolve the function's full type (including parameters)
        val funcType = resolveType(definition.declarationSpecifier, definition.declarator)
        TypeSystem.validateType(funcType, TypeUse.FUNCTION_RETURN)

        // Extract return type from the function type
        val returnType = when (val t = funcType.type) {
            is Type.Function -> t.returnType
            else -> error("Function declarator did not produce a function type")
        }
        currentReturn = returnType.type

        // Enter a new scope for the function body
        enterScope()

        // Define parameters in the scope
        val parameters = funcType.type.parameters
        val paramDeclarators = when (definition.declarator) {
            is Declarator.FunctionDeclarator -> definition.declarator.parameters
            else -> emptyList()
        }

        for ((paramDecl, paramType) in paramDeclarators.zip(parameters)) {
            // Some parameters may be unnamed (like `int f(int, int)`), skip defining them
            val paramName = paramDecl.declarator.name()
            scope.define(
                VariableSymbol(
                    name = paramName,
                    type = paramType,
                    storage = paramDecl.declarationSpecifier.storage,
                ),
            )
        }

        // Visit the function body (block statement)
        visit(definition.statements, ctx)

        // Leave the function scope and restore previous return type
        leaveScope()
        currentReturn = oldReturn
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
        val value = statement.value
        if (value == null) {
            if (currentReturn != Type.Void) {
                error("missing return value")
            }
        } else {
            val valueType = visit(value, ctx)
            if (!QualType(currentReturn).isAssignableFrom(valueType.type)) {
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
        defineVariableDeclaration(statement)
    }

    override fun visitWhile(statement: WhileStatement, ctx: TypeContext) {
        visit(statement.condition, ctx)
        visit(statement.statements, ctx)
    }

    override fun visitArrayAccess(expression: ArrayAccessExpression, ctx: TypeContext): ExpressionType {
        val base = typeOf(expression.base)
        val index = typeOf(expression.index)

        val baseType = TypeSystem.decay(base.type)
        val idxType = TypeSystem.decay(index.type)

        // Index must be integer
        if (!TypeSystem.isInteger(idxType)) return ExpressionType(QualType.ErrorType, false)

        // Base must be pointer or array
        val elementType = when (val bt = baseType.type) {
            is Type.Pointer -> bt.pointee
            is Type.Array -> bt.elementType
            else -> return ExpressionType(QualType.ErrorType, false)
        }

        // Access yields lvalue of element type
        return ExpressionType(elementType, isLValue = true)
    }

    override fun visitAssignment(expression: AssignmentExpression, ctx: TypeContext): ExpressionType {
        val lhs = typeOf(expression.leftExpression)
        val rhs = typeOf(expression.rightExpression)

        if (!lhs.isLValue) return ExpressionType(QualType.ErrorType, false)
        if (!TypeSystem.isAssignable(lhs.type, rhs.type)) {
            return ExpressionType(QualType.ErrorType, false)
        }

        // Result of assignment is rvalue of LHS type
        return ExpressionType(lhs.type, isLValue = false)
    }

    override fun visitBinary(expression: BinaryExpression, ctx: TypeContext): ExpressionType {
        val lhs = typeOf(expression.leftExpression)
        val rhs = typeOf(expression.rightExpression)
        val resultType = when {
            TypeSystem.isPointer(lhs.type) && TypeSystem.isInteger(rhs.type) ->
                TypeSystem.pointerArithmetic(lhs.type, rhs.type)

            TypeSystem.isPointer(rhs.type) && TypeSystem.isInteger(lhs.type) ->
                TypeSystem.pointerArithmetic(rhs.type, lhs.type)

            else ->
                TypeSystem.usualArithmeticConversion(lhs.type, rhs.type)
        }
        return ExpressionType(resultType, false)
    }

    override fun visitCall(expression: CallExpression, ctx: TypeContext): ExpressionType {
        val callee = typeOf(expression.function)
        val funcType = TypeSystem.asFunctionType(callee.type) ?: return ExpressionType(QualType.ErrorType, false)

        // Check argument count
        if (expression.arguments.size != funcType.parameters.size) {
            return ExpressionType(QualType.ErrorType, false)
        }

        // Check assignability for each argument
        for ((argExpr, paramType) in expression.arguments.zip(funcType.parameters)) {
            val argType = typeOf(argExpr).type
            if (!paramType.isAssignableFrom(argType)) {
                return ExpressionType(QualType.ErrorType, false)
            }
        }

        return ExpressionType(funcType.returnType, isLValue = false)
    }

    override fun visitCast(expression: CastExpression, ctx: TypeContext): ExpressionType {
        val target = resolveType(expression.targetType.declarationSpecifier, expression.targetType.abstractDeclarator).canonical
        TypeSystem.validateType(target, TypeUse.CAST)
        val exprType = typeOf(expression.expression).type.canonical

        // If target is void, any type can be cast
        if (target.type == Type.Void) {
            return ExpressionType(target, isLValue = false)
        }

        // Arithmetic casts: int → float, float → int, etc.
        if (TypeSystem.isArithmetic(target) && TypeSystem.isArithmetic(exprType)) {
            return ExpressionType(target, isLValue = false)
        }

        // Pointer casts
        if (TypeSystem.isPointer(target) && TypeSystem.isPointer(exprType)) {
            val tp = target.type as Type.Pointer
            val ep = exprType.type as Type.Pointer

            // Allow any pointer → pointer cast (like void* rules)
            // But track qualifiers: cannot drop const from pointee
            val combinedQuals = tp.pointee.qualifiers intersect ep.pointee.qualifiers

            val resultPointee = QualType(tp.pointee.type, combinedQuals)
            return ExpressionType(QualType(Type.Pointer(resultPointee)), isLValue = false)
        }

        // Integer → pointer or pointer → integer
        if ((TypeSystem.isPointer(target) && TypeSystem.isInteger(exprType)) ||
            (TypeSystem.isInteger(target) && TypeSystem.isPointer(exprType))
        ) {
            return ExpressionType(target, isLValue = false)
        }

        // Struct → struct cast not allowed in C
        if (target.type is Type.Struct || exprType.type is Type.Struct) {
            return ExpressionType(QualType.ErrorType, isLValue = false)
        }

        // Fallback: cast not allowed
        return ExpressionType(QualType.ErrorType, isLValue = false)
    }

    override fun visitConstantInt(expression: ConstantIntExpression, ctx: TypeContext): ExpressionType {
        return ExpressionType(TypeSystem.intType, isLValue = false)
    }

    override fun visitConstantLong(expression: ConstantLongExpression, ctx: TypeContext): ExpressionType {
        return ExpressionType(TypeSystem.longType, isLValue = false)
    }

    override fun visitConstantString(expression: ConstantStringExpression, ctx: TypeContext): ExpressionType {
        // String literals decay to pointer to char
        val charType = QualType(Type.Char(signed = true))
        val arrayType = QualType(Type.Array(charType, expression.value.length.toLong()))
        return ExpressionType(TypeSystem.decay(arrayType), isLValue = false)
    }

    override fun visitFieldAccess(expression: FieldAccessExpression, ctx: TypeContext): ExpressionType {
        val baseExpr = typeOf(expression.base)
        val baseType = TypeSystem.decay(baseExpr.type)
        val structType = when (val t = baseType.type) {
            is Type.Struct -> t
            is Type.Pointer -> (t.pointee.type as? Type.Struct)
            else -> null
        } ?: return ExpressionType(QualType.ErrorType, false)

        val field = structType.fields?.find { it.name == expression.field }
            ?: return ExpressionType(QualType.ErrorType, false)

        // Field access: lvalue if base is lvalue
        return ExpressionType(field.type, isLValue = baseExpr.isLValue)
    }

    override fun visitIdentifier(identifier: Identifier, ctx: TypeContext): ExpressionType {
        val symbol = scope.resolve(identifier.name)
        if (symbol == null) {
//            error("undeclared variable ${identifier.name}")
            return ExpressionType(QualType.ErrorType, false)
        }
        return ExpressionType(symbol.type, isLValue = true)
    }

    override fun visitParenthesized(expression: ParenthesizedExpression, ctx: TypeContext): ExpressionType {
        return visit(expression.expression, ctx)
    }

    override fun visitPostfixDecrement(expression: PostfixDecrementExpression, ctx: TypeContext): ExpressionType {
        return visit(expression.expression, ctx)
    }

    override fun visitPostfixIncrement(expression: PostfixIncrementExpression, ctx: TypeContext): ExpressionType {
        return visit(expression.expression, ctx)
    }

    override fun visitTernary(expression: TernaryExpression, ctx: TypeContext): ExpressionType {
        typeOf(expression.condition)
        val thenType = typeOf(expression.thenExpression)
        val elseType = typeOf(expression.elseExpression)

        val t1 = TypeSystem.decay(thenType.type)
        val t2 = TypeSystem.decay(elseType.type)

        // Case 1: both arithmetic → usual arithmetic conversions
        if (TypeSystem.isArithmetic(t1) && TypeSystem.isArithmetic(t2)) {
            return ExpressionType(
                TypeSystem.usualArithmeticConversion(t1, t2),
                isLValue = false,
            )
        }

        // Case 2: both pointers → pointer compatibility
        if (TypeSystem.isPointer(t1) && TypeSystem.isPointer(t2)) {
            val resultPointee: QualType = if (t1.isCompatibleWith(t2)) {
                // Result qualifiers = intersection of qualifiers of both
                val combinedQuals = t1.qualifiers intersect t2.qualifiers
                QualType((t1.type as Type.Pointer).pointee.type, combinedQuals)
            } else {
                return ExpressionType(QualType.ErrorType, isLValue = false)
            }
            return ExpressionType(QualType(Type.Pointer(resultPointee)), isLValue = false)
        }

        // Case 3: mixed pointer vs arithmetic → error
        if ((TypeSystem.isPointer(t1) && TypeSystem.isArithmetic(t2)) ||
            (TypeSystem.isArithmetic(t1) && TypeSystem.isPointer(t2))
        ) {
            return ExpressionType(QualType.ErrorType, isLValue = false)
        }

        // Case 4: lvalue propagation (rare)
        if (thenType.isLValue && elseType.isLValue && t1 == t2) {
            return ExpressionType(t1, isLValue = true)
        }

        // fallback: decay to rvalue
        return ExpressionType(t1, isLValue = false)
    }

    override fun visitUnary(expression: UnaryExpression, ctx: TypeContext): ExpressionType {
        val operand = typeOf(expression.operand)
        val t = operand.type
        return when (expression.type) {
            UnaryType.Address -> ExpressionType(TypeSystem.addressOf(t, operand.isLValue), isLValue = false)
            UnaryType.Indirection -> ExpressionType(TypeSystem.dereference(t), isLValue = true)
            UnaryType.Minus,
            UnaryType.Plus,
            UnaryType.LogicalNot,
            UnaryType.BitwiseNot,
            -> {
                // Arithmetic operators
                if (TypeSystem.isArithmetic(t)) {
                    ExpressionType(t, isLValue = false)
                } else {
                    ExpressionType(QualType.ErrorType, isLValue = false)
                }
            }

            UnaryType.MinusMinus,
            UnaryType.PlusPlus,
            -> {
                // Only lvalues of arithmetic type
                if (operand.isLValue && TypeSystem.isArithmetic(t)) {
                    ExpressionType(t, isLValue = false)
                } else {
                    ExpressionType(QualType.ErrorType, isLValue = false)
                }
            }
        }
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

    fun typeOf(expression: Expression): ExpressionType {
        return expressionTypeSystem.typeOf(expression)
    }

    private fun defineTypedef(name: String, type: QualType) {
        if (symbols.resolve(name) != null) {
            throw TypeException("typedef $name already defined")
        }
        symbols.defineTypedef(name, type)
    }

    private fun defineGlobalVariable(statement: VariableDeclarationStatement) {
        for (varDecl in statement.variableDeclarators) {
            val qt = resolveType(statement.declarationSpecifier, varDecl.declarator)
            TypeSystem.validateType(qt, TypeUse.OBJECT)
            val variableSymbol = VariableSymbol(
                varDecl.declarator.name(),
                qt,
                statement.declarationSpecifier.storage,
            )
            val oldSym = scope.resolve(variableSymbol.name)
            if (oldSym != null && oldSym != variableSymbol) {
                throw TypeException("variable re-definition of ${oldSym.name} is different from ${variableSymbol.name}")
            }
            globalScope.define(variableSymbol)
        }
    }

    private fun defineGlobalFunction(statement: FunctionDefinitionStatement) {
        val qt = resolveType(statement.declarationSpecifier, statement.declarator)
        TypeSystem.validateType(qt, TypeUse.OBJECT)
        val functionSymbol = FunctionSymbol(
            statement.declarator.name(),
            qt,
            statement.declarationSpecifier.storage,
            statement.statements,
        )
        val oldSym = scope.resolve(functionSymbol.name)
        if (oldSym != null && oldSym != functionSymbol) {
            throw TypeException("function re-definition of ${oldSym.name} is different from ${functionSymbol.name}")
        }
        globalScope.define(functionSymbol)
    }

    private fun defineVariableDeclaration(statement: VariableDeclarationStatement) {
        for (varDecl in statement.variableDeclarators) {
            val qt = resolveType(statement.declarationSpecifier, varDecl.declarator)
            TypeSystem.validateType(qt, TypeUse.OBJECT)
            val variableSymbol = VariableSymbol(
                varDecl.declarator.name(),
                qt,
                statement.declarationSpecifier.storage,
            )
            val oldSym = scope.resolve(variableSymbol.name)
            if (oldSym != null && oldSym != variableSymbol) {
                throw TypeException("variable re-definition of ${oldSym.name} is different from ${variableSymbol.name}")
            }
            scope.define(variableSymbol)
        }
    }

    private fun resolveType(declSpec: DeclarationSpecifier, declarator: Declarator?): QualType {
        val base = buildBaseType(declSpec)
        return declarator?.let { applyDeclarator(base, it) } ?: base
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
            val qt = symbols.resolve(name) ?: throw TypeException("unknown qualified name $name")
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
                QualType(Type.Pointer(inner), emptySet())
            }

            is Declarator.ArrayDeclarator -> {
                val inner = applyDeclarator(baseType, declarator.elementType)
                QualType(Type.Array(inner, evalSize(declarator.size)))
            }

            is Declarator.FunctionDeclarator -> {
                val returnType = applyDeclarator(baseType, declarator.declarator)
                val params = declarator.parameters.map { p ->
                    val qt = resolveType(p.declarationSpecifier, p.declarator)
                    TypeSystem.validateType(qt, TypeUse.FUNCTION_RETURN)
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
}
