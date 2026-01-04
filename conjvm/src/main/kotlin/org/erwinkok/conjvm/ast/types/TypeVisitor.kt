package org.erwinkok.conjvm.ast.types

import org.erwinkok.conjvm.ast.AstExpressionVisitor
import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.SourceLocation
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
import org.erwinkok.conjvm.parser.ErrorReporter
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
            TypeSystem.validateType(funcType, TypeUse.FUNCTION_RETURN)
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
            val valueType = visit(value)
            if (valueType.isError()) {
                return
            }
            if (!currentReturn.isAssignableFrom(valueType.type)) {
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
        defineVariableDeclaration(statement)
    }

    override fun visitWhile(statement: WhileStatement) {
        visit(statement.condition)
        visit(statement.statements)
    }

    override fun visitArrayAccess(expression: ArrayAccessExpression): ExpressionType {
        val base = typeOf(expression.base)
        val index = typeOf(expression.index)

        if (base.isError() || index.isError()) {
            return ExpressionType(QualType.ErrorType, isLValue = false)
        }

        val baseType = TypeSystem.decay(base.type)
        val idxType = TypeSystem.decay(index.type)

        // Index must be integer
        if (!TypeSystem.isInteger(idxType)) {
            reporter.reportError(expression.location, "array index '${expression.index}' must be an integer")
            return ExpressionType(QualType.ErrorType, false)
        }

        // Base must be pointer or array
        val elementType = when (val bt = baseType.type) {
            is Type.Pointer -> bt.pointee
            else -> {
                reporter.reportError(expression.location, "'${expression.base}' element must be a pointer")
                return ExpressionType(QualType.ErrorType, false)
            }
        }

        // Access yields lvalue of element type
        return ExpressionType(elementType, isLValue = true)
    }

    override fun visitAssignment(expression: AssignmentExpression): ExpressionType {
        val lhs = typeOf(expression.leftExpression)
        val rhs = typeOf(expression.rightExpression)

        if (lhs.isError() || rhs.isError()) {
            return ExpressionType(QualType.ErrorType, isLValue = false)
        }

        if (!lhs.isLValue) {
            reporter.reportError(expression.location, "'${lhs.type}' must be a lvalue in assignment")
            return ExpressionType(QualType.ErrorType, false)
        }
        if (!TypeSystem.isAssignable(lhs.type, rhs.type)) {
            reporter.reportError(expression.location, "'${rhs.type}' is not assignable to '${lhs.type}' in '$expression'")
            return ExpressionType(QualType.ErrorType, false)
        }

        // Result of assignment is rvalue of LHS type
        return ExpressionType(lhs.type, isLValue = false)
    }

    override fun visitBinary(expression: BinaryExpression): ExpressionType {
        val lhs = typeOf(expression.leftExpression)
        val rhs = typeOf(expression.rightExpression)

        if (lhs.isError() || rhs.isError()) {
            return ExpressionType(QualType.ErrorType, isLValue = false)
        }

        val resultType = when {
            TypeSystem.isPointer(lhs.type) && TypeSystem.isInteger(rhs.type) ->
                TypeSystem.pointerArithmetic(lhs.type, rhs.type)

            TypeSystem.isPointer(rhs.type) && TypeSystem.isInteger(lhs.type) ->
                TypeSystem.pointerArithmetic(rhs.type, lhs.type)

            TypeSystem.isPointer(lhs.type) && TypeSystem.isPointer(rhs.type) ->
                TypeSystem.pointerDifference(lhs.type, rhs.type)

            else ->
                TypeSystem.usualArithmeticConversion(lhs.type, rhs.type)
        }
        if (resultType.isError()) {
            reporter.reportError(expression.location, "invalid operands to binary operator '$expression'")
            return ExpressionType(QualType.ErrorType, false)
        }
        return ExpressionType(resultType, false)
    }

    override fun visitCall(expression: CallExpression): ExpressionType {
        val callee = typeOf(expression.function)

        if (callee.isError()) {
            return ExpressionType(QualType.ErrorType, isLValue = false)
        }

        val funcType = TypeSystem.asFunctionType(callee.type) ?: return ExpressionType(QualType.ErrorType, false)

        // Check argument count
        if (expression.arguments.size != funcType.parameters.size) {
            reporter.reportError(expression.location, "arguments do not match in call")
            return ExpressionType(QualType.ErrorType, false)
        }

        // Check assignability for each argument
        for ((argExpr, paramType) in expression.arguments.zip(funcType.parameters)) {
            val arg = typeOf(argExpr)
            if (arg.isError()) {
                return ExpressionType(QualType.ErrorType, false)
            }
            val promotedArg = TypeSystem.integerPromote(TypeSystem.decay(arg.type))
            if (!paramType.isAssignableFrom(promotedArg)) {
                reporter.reportError(expression.location, "parameter $paramType is not assignable from $promotedArg")
                return ExpressionType(QualType.ErrorType, false)
            }
        }

        return ExpressionType(funcType.returnType, isLValue = false)
    }

    override fun visitCast(expression: CastExpression): ExpressionType {
        val operand = typeOf(expression.expression)
        if (operand.isError()) {
            return ExpressionType(QualType.ErrorType, isLValue = false)
        }

        val target = try {
            val target = resolveType(expression.targetType.declarationSpecifier, expression.targetType.abstractDeclarator).canonical
            TypeSystem.validateType(target, TypeUse.CAST)
            target
        } catch (e: TypeException) {
            reporter.reportError(expression.location, e.message ?: "unknown error message")
            return ExpressionType(QualType.ErrorType, isLValue = false)
        }

        expression.targetQualType = target

        val exprType = operand.type.canonical

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
        if (
            (TypeSystem.isPointer(target) && TypeSystem.isInteger(exprType)) ||
            (TypeSystem.isInteger(target) && TypeSystem.isPointer(exprType))
        ) {
            return ExpressionType(target, isLValue = false)
        }

        // Struct → struct cast not allowed in C
        if (target.type is Type.Struct || exprType.type is Type.Struct) {
            reporter.reportError(expression.location, "struct cast in '$expression' is not allowed")
            return ExpressionType(QualType.ErrorType, isLValue = false)
        }

        // Fallback: cast not allowed
        reporter.reportError(expression.location, "cast in '$expression' is not allowed")
        return ExpressionType(QualType.ErrorType, isLValue = false)
    }

    override fun visitConstantInt(expression: ConstantIntExpression): ExpressionType {
        return ExpressionType(TypeSystem.intType, isLValue = false)
    }

    override fun visitConstantLong(expression: ConstantLongExpression): ExpressionType {
        return ExpressionType(TypeSystem.longType, isLValue = false)
    }

    override fun visitConstantString(expression: ConstantStringExpression): ExpressionType {
        // String literals decay to pointer to char
        val charType = QualType(Type.Char(signed = true))
        val arrayType = QualType(Type.Array(charType, expression.value.length.toLong()))
        return ExpressionType(TypeSystem.decay(arrayType), isLValue = false)
    }

    override fun visitFieldAccess(expression: FieldAccessExpression): ExpressionType {
        val baseExpr = typeOf(expression.base)
        if (baseExpr.isError()) {
            return ExpressionType(QualType.ErrorType, isLValue = false)
        }

        val baseType = TypeSystem.decay(baseExpr.type)
        val structType = when (val t = baseType.type) {
            is Type.Struct -> t
            is Type.Pointer -> (t.pointee.type as? Type.Struct)
            else -> null
        }
        if (structType == null) {
            reporter.reportError(expression.location, "'${expression.base}' is not a struct")
            return ExpressionType(QualType.ErrorType, false)
        }
        val field = structType.fields?.find { it.name == expression.field }
        if (field == null) {
            reporter.reportError(expression.location, "could not find field '${expression.field}' in struct '${expression.base}'")
            return ExpressionType(QualType.ErrorType, false)
        }

        // Field access: lvalue if base is lvalue
        return ExpressionType(field.type, isLValue = baseExpr.isLValue)
    }

    override fun visitIdentifier(identifier: Identifier): ExpressionType {
        val localVar = scope.resolveVariable(identifier.name)
        if (localVar != null) {
            return ExpressionType(localVar.type, isLValue = true)
        }
        val globalFunc = globalScope.resolveFunction(identifier.name)
        if (globalFunc != null) {
            return ExpressionType(globalFunc.type, isLValue = false)
        }
        reporter.reportError(identifier.location, "undeclared identifier: '${identifier.name}'")
        return ExpressionType(QualType.ErrorType, isLValue = false)
    }

    override fun visitParenthesized(expression: ParenthesizedExpression): ExpressionType {
        return visit(expression.expression)
    }

    override fun visitPostfixDecrement(expression: PostfixDecrementExpression): ExpressionType {
        return visit(expression.expression)
    }

    override fun visitPostfixIncrement(expression: PostfixIncrementExpression): ExpressionType {
        return visit(expression.expression)
    }

    override fun visitTernary(expression: TernaryExpression): ExpressionType {
        val condType = typeOf(expression.condition)
        val thenType = typeOf(expression.thenExpression)
        val elseType = typeOf(expression.elseExpression)

        if (condType.isError() || thenType.isError() || elseType.isError()) {
            return ExpressionType(QualType.ErrorType, isLValue = false)
        }

        val t1 = TypeSystem.decay(thenType.type)
        val t2 = TypeSystem.decay(elseType.type)

        // both arithmetic → usual arithmetic conversions
        if (TypeSystem.isArithmetic(t1) && TypeSystem.isArithmetic(t2)) {
            return ExpressionType(
                TypeSystem.usualArithmeticConversion(t1, t2),
                isLValue = false,
            )
        }

        if (!TypeSystem.isArithmetic(condType.type) && !TypeSystem.isPointer(condType.type)) {
            reporter.reportError(expression.location, "condition of ?: must be scalar in '$expression'")
            return ExpressionType(QualType.ErrorType, false)
        }

        if (t1.type == Type.Void && t2.type == Type.Void) {
            return ExpressionType(TypeSystem.voidType, false)
        }

        // both pointers → pointer compatibility
        if (TypeSystem.isPointer(t1) && TypeSystem.isPointer(t2)) {
            val resultPointee: QualType = if (t1.isCompatibleWith(t2)) {
                // Result qualifiers = intersection of qualifiers of both
                val combinedQuals = t1.qualifiers intersect t2.qualifiers
                QualType((t1.type as Type.Pointer).pointee.type, combinedQuals)
            } else {
                reporter.reportError(expression.location, "pointers '${t1.type}' and '${t2.type}' are not compatible in '$expression'")
                return ExpressionType(QualType.ErrorType, isLValue = false)
            }
            return ExpressionType(QualType(Type.Pointer(resultPointee)), isLValue = false)
        }

        // mixed pointer vs arithmetic → error
        if ((TypeSystem.isPointer(t1) && TypeSystem.isArithmetic(t2)) ||
            (TypeSystem.isArithmetic(t1) && TypeSystem.isPointer(t2))
        ) {
            reporter.reportError(expression.location, "pointers '${t1.type}' and '${t2.type}' are not compatible in '$expression'")
            return ExpressionType(QualType.ErrorType, isLValue = false)
        }

        // lvalue propagation (rare)
        if (thenType.isLValue && elseType.isLValue && t1 == t2) {
            return ExpressionType(t1, isLValue = true)
        }

        // fallback: decay to rvalue
        return ExpressionType(t1, isLValue = false)
    }

    override fun visitUnary(expression: UnaryExpression): ExpressionType {
        val operand = typeOf(expression.operand)
        if (operand.isError()) {
            return ExpressionType(QualType.ErrorType, isLValue = false)
        }

        val t = operand.type
        return when (expression.type) {
            UnaryType.Address -> {
                val address = TypeSystem.addressOf(t, operand.isLValue)
                if (address.isError()) {
                    reporter.reportError(expression.location, "cannot take address of '$expression'")
                    ExpressionType(QualType.ErrorType, false)
                } else {
                    ExpressionType(address, false)
                }
            }

            UnaryType.Indirection -> {
                val deref = TypeSystem.dereference(t)
                if (deref.isError()) {
                    reporter.reportError(expression.location, "cannot dereference '$expression'")
                    ExpressionType(QualType.ErrorType, false)
                } else {
                    ExpressionType(
                        deref,
                        isLValue = deref.type !is Type.Void && deref.type !is Type.Function,
                    )
                }
            }

            UnaryType.Minus,
            UnaryType.Plus,
            UnaryType.LogicalNot,
            UnaryType.BitwiseNot,
            -> {
                // Arithmetic operators
                if (TypeSystem.isArithmetic(t)) {
                    ExpressionType(t, isLValue = false)
                } else {
                    reporter.reportError(expression.location, "'${t.type}' is not arithmetic in '$expression'")
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
                    reporter.reportError(expression.location, "'${t.type}' must be a lvalue and an arithmetic in '$expression'")
                    ExpressionType(QualType.ErrorType, isLValue = false)
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

    fun typeOf(expression: Expression): ExpressionType {
        return cache.getOrPut(expression) { visit(expression) }
    }

    private fun defineTypedef(location: SourceLocation, name: String, type: QualType) {
        if (symbols.resolve(name) != null) {
            reporter.reportError(location, "typedef '$name' already defined")
        }
        symbols.defineTypedef(name, type)
    }

    private fun defineGlobalVariable(statement: VariableDeclarationStatement) {
        for (varDecl in statement.variableDeclarators) {
            try {
                val qt = resolveType(statement.declarationSpecifier, varDecl.declarator)
                TypeSystem.validateType(qt, TypeUse.OBJECT)
                globalScope.defineVariable(varDecl.declarator.name(), qt, statement.declarationSpecifier.storage)
            } catch (e: TypeException) {
                reporter.reportError(statement.location, e.message ?: "unknown error message")
            }
        }
    }

    private fun defineGlobalFunction(statement: FunctionDefinitionStatement) {
        try {
            val qt = resolveType(statement.declarationSpecifier, statement.declarator)
            TypeSystem.validateType(qt, TypeUse.OBJECT)
            globalScope.defineFunction(statement.declarator.name(), qt, statement.declarationSpecifier.storage)
        } catch (e: TypeException) {
            reporter.reportError(statement.location, e.message ?: "unknown error message")
        }
    }

    private fun defineVariableDeclaration(statement: VariableDeclarationStatement) {
        for (varDecl in statement.variableDeclarators) {
            try {
                val qt = resolveType(statement.declarationSpecifier, varDecl.declarator)
                TypeSystem.validateType(qt, TypeUse.OBJECT)
                scope.defineVariable(varDecl.declarator.name(), qt, statement.declarationSpecifier.storage)
            } catch (e: TypeException) {
                reporter.reportError(statement.location, e.message ?: "unknown error message")
            }
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
                if (longCount > 0) {
                    throw TypeException("invalid type specifier: long double not supported yet")
                }
                Type.Double
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
                    TypeSystem.validateType(qt, TypeUse.PARAMETER)
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
        throw TypeException("array size '$size' must be a compile time constant")
    }
}
