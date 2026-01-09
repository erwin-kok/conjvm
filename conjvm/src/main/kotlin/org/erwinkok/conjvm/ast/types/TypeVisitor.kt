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
import org.erwinkok.conjvm.ast.statements.DoWhileStatement
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
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.SourceLocation
import java.util.IdentityHashMap

class TypeVisitor(
    private val symbols: SymbolTable,
    private val reporter: ErrorReporter,
) : AstStatementVisitor<Unit>,
    AstExpressionVisitor<ExpressionType> {
    private val cache = IdentityHashMap<Expression, ExpressionType>()
    private var currentReturn: QualType = TypeSystem.voidType
    private var scope = Scope()

    val globalScope = scope

    override fun visitCompilationUnit(statement: CompilationUnitStatement) {
        statement.variableDeclarations.forEach { defineGlobalVariable(it) }
        statement.functionDefinitions.forEach { defineGlobalFunction(it) }

        statement.functionDefinitions.forEach {
            visit(it)
        }
    }

    override fun visitFunctionDefinition(definition: FunctionDefinitionStatement) {
        // Save the old return type
        val oldReturn = currentReturn

        // Resolve the function's full type (including parameters)
        val funcType = try {
            val funcType = resolveType(definition.declarationSpecifier, definition.declarator)
            TypeSystem.validateWellFormed(funcType)
            funcType
        } catch (e: TypeException) {
            reporter.reportError(definition.location, e.message ?: "unknown error message")
            return
        }

        // Extract return type from the function type
        val returnType = when (val t = funcType.type) {
            is Type.Function -> t.returnType
            else -> {
                reporter.reportError(definition.location, "function declarator did not produce a function type")
                return
            }
        }
        currentReturn = returnType

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
            scope.defineVariable(paramName, paramType, paramDecl.declarationSpecifier.storage)
        }

        // Visit the function body (block statement)
        visit(definition.statements)

        // Leave the function scope and restore previous return type
        leaveScope()
        currentReturn = oldReturn
    }

    override fun visitBlock(statement: BlockStatement) {
        enterScope()
        statement.statements.forEach { visit(it) }
        leaveScope()
    }

    override fun visitBreak(statement: BreakStatement) {
        // Nothing
    }

    override fun visitContinue(statement: ContinueStatement) {
        // Nothing
    }

    override fun visitExpression(statement: ExpressionStatement) {
        visit(statement.expression)
    }

    override fun visitFor(statement: ForStatement) {
        statement.condition?.let { visit(it) }
        statement.iterators?.let { it.forEach { ex -> visit(ex) } }
        visit(statement.statements)
    }

    override fun visitGoto(statement: GotoStatement) {
        // Nothing
    }

    override fun visitIfThenElse(statement: IfThenElseStatement) {
        visit(statement.test)
        visit(statement.thenBlock)
        visit(statement.elseBlock)
    }

    override fun visitIfThen(statement: IfThenStatement) {
        visit(statement.test)
        visit(statement.thenBlock)
    }

    override fun visitLabeled(statement: LabeledStatement) {
        visit(statement.statement)
    }

    override fun visitReturn(statement: ReturnStatement) {
        val value = statement.value
        if (value == null) {
            if (currentReturn != TypeSystem.voidType) {
                reporter.reportError(statement.location, "missing return value")
            }
        } else {
            val valueType = typeOf(value).toRValue()
            if (valueType.isError) {
                return
            }
            if (!TypeSystem.isAssignable(currentReturn, valueType.type)) {
                reporter.reportError(statement.location, "return type mismatch")
            }
        }
    }

    override fun visitSwitch(statement: SwitchStatement) {
        visit(statement.test)
        statement.sections.forEach { visitSwitchCase(it) }
        statement.defaultSection?.let { visitDefaultCase(it) }
    }

    override fun visitVariableDeclaration(statement: VariableDeclarationStatement) {
        defineVariable(statement)
    }

    override fun visitWhile(statement: WhileStatement) {
        visit(statement.condition)
        visit(statement.statements)
    }

    override fun visitDoWhile(statement: DoWhileStatement) {
        visit(statement.condition)
        visit(statement.statements)
    }

    override fun visitArrayAccess(expression: ArrayAccessExpression): ExpressionType {
        val base = typeOf(expression.base).toRValue()
        val index = typeOf(expression.index)

        if (base.isError || index.isError) {
            return errorType(expression)
        }

        val baseType = base.type
        val idxType = TypeSystem.decay(index.type)

        // Index must be integer
        if (!TypeSystem.isInteger(idxType)) {
            reporter.reportError(expression.location, "array index '${expression.index}' must be an integer")
            return errorType(expression)
        }

        // Base must be pointer or array
        val elementType = when (val bt = baseType.type) {
            is Type.Pointer -> bt.pointee
            else -> {
                reporter.reportError(expression.location, "'${expression.base}' expression is not subscriptable")
                return errorType(expression)
            }
        }

        // Access yields lvalue of element type
        return expressionType(expression, elementType, true)
    }

    override fun visitAssignment(expression: AssignmentExpression): ExpressionType {
        val lhs = typeOf(expression.leftExpression)
        val rhs = typeOf(expression.rightExpression).toRValue()

        if (lhs.isError || rhs.isError) {
            return errorType(expression)
        }

        if (!lhs.isLValue) {
            reporter.reportError(expression.location, "'${lhs.type}' must be a lvalue in assignment")
            return errorType(expression)
        }
        if (!TypeSystem.isAssignable(lhs.type, rhs.type)) {
            reporter.reportError(expression.location, "'${rhs.type}' is not assignable to '${lhs.type}' in '$expression'")
            return errorType(expression)
        }

        // Result of assignment is rvalue of LHS type
        return expressionType(expression, lhs.type)
    }

    override fun visitBinary(expression: BinaryExpression): ExpressionType {
        val lhs = typeOf(expression.leftExpression).toRValue()
        val rhs = typeOf(expression.rightExpression).toRValue()

        if (lhs.isError || rhs.isError) {
            return errorType(expression)
        }

        val resultType = when {
            TypeSystem.isPointer(lhs.type) && TypeSystem.isInteger(rhs.type) -> TypeSystem.pointerArithmetic(lhs.type, rhs.type)
            TypeSystem.isPointer(rhs.type) && TypeSystem.isInteger(lhs.type) -> TypeSystem.pointerArithmetic(rhs.type, lhs.type)
            TypeSystem.isPointer(lhs.type) && TypeSystem.isPointer(rhs.type) -> TypeSystem.pointerDifference(lhs.type, rhs.type)
            else -> TypeSystem.usualArithmeticConversion(lhs.type, rhs.type)
        }
        if (resultType.isError) {
            reporter.reportError(expression.location, "invalid operands to binary operator '$expression'")
            return errorType(expression)
        }
        return expressionType(expression, resultType)
    }

    override fun visitCall(expression: CallExpression): ExpressionType {
        val callee = typeOf(expression.function).toRValue()

        if (callee.isError) {
            return errorType(expression)
        }

        val funcType = TypeSystem.asFunctionType(callee.type) ?: return errorType(expression)

        // Check argument count
        if (expression.arguments.size != funcType.parameters.size) {
            reporter.reportError(expression.location, "arguments do not match in call")
            return errorType(expression)
        }

        // Check assignability for each argument
        for ((argExpr, paramType) in expression.arguments.zip(funcType.parameters)) {
            val arg = typeOf(argExpr)
            if (arg.isError) {
                return errorType(expression)
            }
            val promotedArg = TypeSystem.integerPromote(TypeSystem.decay(arg.type))
            if (!TypeSystem.isAssignable(paramType, promotedArg)) {
                reporter.reportError(expression.location, "parameter $paramType is not assignable from $promotedArg")
                return errorType(expression)
            }
        }
        return expressionType(expression, funcType.returnType)
    }

    override fun visitCast(expression: CastExpression): ExpressionType {
        val operand = typeOf(expression.expression)
        if (operand.isError) {
            return errorType(expression)
        }

        val target = try {
            val target = resolveType(expression.targetType.declarationSpecifier, expression.targetType.abstractDeclarator).canonical
            TypeSystem.validateWellFormed(target)
            target
        } catch (e: TypeException) {
            reporter.reportError(expression.location, e.message ?: "unknown error message")
            return errorType(expression)
        }

        expression.targetQualType = target

        val exprType = operand.type.canonical

        // If target is void, any type can be cast
        if (target.type == Type.Void) {
            return expressionType(expression, target)
        }

        // Arithmetic casts: int → float, float → int, etc.
        if (TypeSystem.isArithmetic(target) && TypeSystem.isArithmetic(exprType)) {
            return expressionType(expression, target)
        }

        // Pointer casts
        if (TypeSystem.isPointer(target) && TypeSystem.isPointer(exprType)) {
            val tp = target.type as Type.Pointer
            val ep = exprType.type as Type.Pointer

            if (TypeQualifier.CONST in ep.pointee.qualifiers && TypeQualifier.CONST !in tp.pointee.qualifiers) {
                reporter.reportWarning(expression.location, "pointer casts are const")
            }

            val resultPointee = tp.pointee
            return expressionType(expression, QualType(Type.Pointer(resultPointee), target.qualifiers))
        }

        // Integer → pointer or pointer → integer
        if (
            (TypeSystem.isPointer(target) && TypeSystem.isInteger(exprType)) ||
            (TypeSystem.isInteger(target) && TypeSystem.isPointer(exprType))
        ) {
            return expressionType(expression, target)
        }

        // Struct → struct cast not allowed in C
        if (target.type is Type.Struct || exprType.type is Type.Struct) {
            reporter.reportError(expression.location, "struct cast in '$expression' is not allowed")
            return errorType(expression)
        }

        // Fallback: cast not allowed
        reporter.reportError(expression.location, "cast in '$expression' is not allowed")
        return errorType(expression)
    }

    override fun visitConstantInt(expression: ConstantIntExpression): ExpressionType {
        return expressionType(expression, TypeSystem.intType)
    }

    override fun visitConstantLong(expression: ConstantLongExpression): ExpressionType {
        return expressionType(expression, TypeSystem.longType)
    }

    override fun visitConstantString(expression: ConstantStringExpression): ExpressionType {
        // String literals decay to pointer to char
        val charType = QualType(Type.Char(true), setOf(TypeQualifier.CONST))
        val arrayType = QualType(Type.Array(charType, expression.value.length.toLong()))
        return expressionType(expression, TypeSystem.decay(arrayType))
    }

    override fun visitFieldAccess(expression: FieldAccessExpression): ExpressionType {
        val baseExpr = typeOf(expression.base)
        if (baseExpr.isError) {
            return errorType(expression)
        }

        val baseType = baseExpr.type
        val structType = when (val t = baseType.type) {
            is Type.Struct -> t
            is Type.Pointer -> (t.pointee.type as? Type.Struct)
            else -> null
        }
        if (structType == null) {
            reporter.reportError(expression.location, "'${expression.base}' is not a struct")
            return errorType(expression)
        }
        val field = structType.fields?.find { it.name == expression.field }
        if (field == null) {
            reporter.reportError(expression.location, "could not find field '${expression.field}' in struct '${expression.base}'")
            return errorType(expression)
        }

        // Field access: lvalue if base is lvalue
        return expressionType(expression, field.type, baseExpr.isLValue)
    }

    override fun visitIdentifier(identifier: Identifier): ExpressionType {
        val localVar = scope.resolveVariable(identifier.name)
        if (localVar != null) {
            return expressionType(identifier, localVar.type, true)
        }
        val globalFunc = globalScope.resolveFunction(identifier.name)
        if (globalFunc != null) {
            return expressionType(identifier, globalFunc.type)
        }
        reporter.reportError(identifier.location, "undeclared identifier: '${identifier.name}'")
        return errorType(identifier)
    }

    override fun visitParenthesized(expression: ParenthesizedExpression): ExpressionType {
        return visit(expression.expression)
    }

    override fun visitPostfixIncrement(expression: PostfixIncrementExpression): ExpressionType {
        val operand = typeOf(expression.expression)
        if (!operand.isLValue || !TypeSystem.isArithmetic(operand.type)) {
            reporter.reportError(expression.location, "'${operand.type}' must be an lvalue and arithmetic in '$expression'")
            return errorType(expression)
        }
        // Result of x++ is rvalue
        return expressionType(expression, operand.type, false)
    }

    override fun visitPostfixDecrement(expression: PostfixDecrementExpression): ExpressionType {
        val operand = typeOf(expression.expression)
        if (!operand.isLValue || !TypeSystem.isArithmetic(operand.type)) {
            reporter.reportError(expression.location, "'${operand.type}' must be an lvalue and arithmetic in '$expression'")
            return errorType(expression)
        }
        // Result of x-- is rvalue
        return expressionType(expression, operand.type, false)
    }

    override fun visitTernary(expression: TernaryExpression): ExpressionType {
        val condType = typeOf(expression.condition).toRValue()
        val thenType = typeOf(expression.thenExpression).toRValue()
        val elseType = typeOf(expression.elseExpression).toRValue()

        if (condType.isError || thenType.isError || elseType.isError) {
            return errorType(expression)
        }

        val t1 = thenType.type
        val t2 = elseType.type

        // both arithmetic → usual arithmetic conversions
        if (TypeSystem.isArithmetic(t1) && TypeSystem.isArithmetic(t2)) {
            return expressionType(expression, TypeSystem.usualArithmeticConversion(t1, t2))
        }

        if (!TypeSystem.isArithmetic(condType.type) && !TypeSystem.isPointer(condType.type)) {
            reporter.reportError(expression.location, "condition of ?: must be scalar in '$expression'")
            return errorType(expression)
        }

        if (t1.type == Type.Void && t2.type == Type.Void) {
            return expressionType(expression, TypeSystem.voidType)
        }

        // both pointers → pointer compatibility
        if (TypeSystem.isPointer(t1) && TypeSystem.isPointer(t2)) {
            if (t1.isCompatibleWith(t2)) {
                val p1 = t1.type as Type.Pointer
                val p2 = t2.type as Type.Pointer
                val mergedPointee = QualType(
                    p1.pointee.type,
                    p1.pointee.qualifiers + p2.pointee.qualifiers,
                )
                return expressionType(expression, QualType(Type.Pointer(mergedPointee)))
            } else {
                reporter.reportError(expression.location, "pointers '${t1.type}' and '${t2.type}' are not compatible in '$expression'")
                return errorType(expression)
            }
        }

        // mixed pointer vs arithmetic → error
        if ((TypeSystem.isPointer(t1) && TypeSystem.isArithmetic(t2)) || (TypeSystem.isArithmetic(t1) && TypeSystem.isPointer(t2))) {
            reporter.reportError(expression.location, "pointers '${t1.type}' and '${t2.type}' are not compatible in '$expression'")
            return errorType(expression)
        }

        // lvalue propagation (rare)
        if (thenType.isLValue && elseType.isLValue && t1 == t2) {
            return expressionType(expression, t1, true)
        }

        // fallback: decay to rvalue
        return expressionType(expression, t1)
    }

    override fun visitUnary(expression: UnaryExpression): ExpressionType {
        val operand = typeOf(expression.operand)

        if (operand.isError) {
            return errorType(expression)
        }

        val t = operand.type
        return when (expression.type) {
            UnaryType.Address -> {
                val address = TypeSystem.addressOf(t, operand.isLValue)
                if (address.isError) {
                    reporter.reportError(expression.location, "cannot take address of '$expression'")
                    errorType(expression)
                } else {
                    expressionType(expression, address)
                }
            }

            UnaryType.Indirection -> {
                val deref = TypeSystem.dereference(t)
                if (deref.isError) {
                    reporter.reportError(expression.location, "cannot dereference '$expression'")
                    errorType(expression)
                } else {
                    expressionType(expression, deref, deref.type !is Type.Void && deref.type !is Type.Function)
                }
            }

            UnaryType.Minus,
            UnaryType.Plus,
            -> {
                // Arithmetic operators
                if (TypeSystem.isArithmetic(t)) {
                    val promoted = TypeSystem.integerPromote(t)
                    expressionType(expression, promoted)
                } else {
                    reporter.reportError(expression.location, "'${t.type}' is not arithmetic in '$expression'")
                    errorType(expression)
                }
            }

            UnaryType.LogicalNot,
            UnaryType.BitwiseNot,
            -> {
                // Arithmetic operators
                if (TypeSystem.isArithmetic(t)) {
                    expressionType(expression, t)
                } else {
                    reporter.reportError(expression.location, "'${t.type}' is not arithmetic in '$expression'")
                    errorType(expression)
                }
            }

            UnaryType.MinusMinus,
            UnaryType.PlusPlus,
            -> {
                // Only lvalues of arithmetic type allowed
                if (operand.isLValue && TypeSystem.isArithmetic(t)) {
                    // Result is rvalue in C, not lvalue
                    expressionType(expression, t)
                } else {
                    reporter.reportError(expression.location, "'${t.type}' must be a lvalue and arithmetic in '$expression'")
                    errorType(expression)
                }
            }
        }
    }

    private fun visitSwitchCase(case: SwitchCaseStatement) {
        visit(case.test)
        visit(case.blockStatement)
    }

    private fun visitDefaultCase(default: SwitchDefaultStatement) {
        visit(default.blockStatement)
    }

    private fun enterScope() {
        scope = Scope(scope)
    }

    private fun leaveScope() {
        val parent = scope.parent
        requireNotNull(parent)
        scope = parent
    }

    private fun expressionType(expression: Expression, type: QualType, isLValue: Boolean = false): ExpressionType {
        val et = ExpressionType(type, isLValue)
        expression.expressionType = et
        return et
    }

    private fun errorType(expression: Expression): ExpressionType {
        return expressionType(expression, QualType.ErrorType)
    }

    private fun typeOf(expression: Expression): ExpressionType {
        return cache.getOrPut(expression) { visit(expression) }
    }

    private fun defineTypedef(location: SourceLocation, name: String, type: QualType) {
        if (symbols.resolve(name) != null) {
            reporter.reportError(location, "typedef '$name' already defined")
        }
        symbols.defineTypedef(name, type)
    }

    private fun defineGlobalVariable(statement: VariableDeclarationStatement) {
        defineVariableInScope(statement, globalScope)
    }

    private fun defineVariable(statement: VariableDeclarationStatement) {
        defineVariableInScope(statement, scope)
    }

    private fun defineVariableInScope(statement: VariableDeclarationStatement, s: Scope) {
        for (varDecl in statement.variableDeclarators) {
            try {
                val qt = resolveType(statement.declarationSpecifier, varDecl.declarator)
                if (statement.declarationSpecifier.storage.contains(StorageClass.TYPEDEF)) {
                    defineTypedef(statement.location, varDecl.declarator.name(), qt)
                } else {
                    TypeSystem.validateObjectType(qt)
                    s.defineVariable(varDecl.declarator.name(), qt, statement.declarationSpecifier.storage)
                }
            } catch (e: TypeException) {
                reporter.reportError(statement.location, e.message ?: "unknown error message")
            }
        }
    }

    private fun defineGlobalFunction(statement: FunctionDefinitionStatement) {
        try {
            val qt = resolveType(statement.declarationSpecifier, statement.declarator)
            TypeSystem.validateObjectType(qt)
            globalScope.defineFunction(statement.declarator.name(), qt, statement.declarationSpecifier.storage)
        } catch (e: TypeException) {
            reporter.reportError(statement.location, e.message ?: "unknown error message")
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
                    throw TypeException("invalid type specifier: void cannot be combined")
                }
                Type.Void
            }

            specs.contains(TypeSpec.FLOAT) -> {
                if (specs.any { it == TypeSpec.SIGNED || it == TypeSpec.UNSIGNED }) {
                    throw TypeException("invalid type specifier: float cannot be signed/unsigned")
                }
                Type.Float
            }

            specs.contains(TypeSpec.DOUBLE) -> {
                when (longCount) {
                    0 -> Type.Double
                    1 -> Type.LongDouble
                    else -> throw TypeException("invalid type specifier: too many long specifiers")
                }
            }

            specs.contains(TypeSpec.CHAR) -> {
                if (longCount > 0 || shortCount > 0) {
                    throw TypeException("invalid type specifier: char cannot be long/short")
                }
                Type.Char(signed)
            }

            shortCount > 0 -> {
                if (longCount > 0) {
                    throw TypeException("invalid type specifier: short and long together")
                }
                Type.Short(signed)
            }

            longCount == 1 -> Type.Long(signed)
            longCount == 2 -> Type.LongLong(signed)
            longCount > 2 -> throw TypeException("invalid type specifier: too many long specifiers")

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
                    TypeSystem.validateWellFormed(qt)
                    when (qt.type) {
                        is Type.Array -> QualType(Type.Pointer(qt.type.elementType))
                        is Type.Function -> QualType(Type.Pointer(qt))
                        else -> qt
                    }
                }
                QualType(Type.Function(returnType, params))
            }

            is Declarator.BitFieldDeclarator -> {
                QualType(Type.BitField(baseType, declarator.width))
            }
        }
    }

    private fun evalSize(size: Expression?): Long? {
        if (size == null) return null
        if (size is ConstantIntExpression) return size.value.toLong()
        if (size is ConstantLongExpression) return size.value
        throw TypeException("array size '$size' must be a compile time constant")
    }
}
