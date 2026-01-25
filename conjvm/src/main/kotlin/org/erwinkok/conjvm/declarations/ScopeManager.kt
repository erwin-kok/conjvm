package org.erwinkok.conjvm.declarations

import org.antlr.v4.runtime.ParserRuleContext
import org.erwinkok.conjvm.CParser
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.SourceLocation

class ScopeManager(
    private val reporter: ErrorReporter,
) {
    private val scopeMap = mutableMapOf<ParserRuleContext, Scope>()
    private val variableMap = mutableMapOf<ParserRuleContext, Entity.Variable>()
    private val functionMap = mutableMapOf<ParserRuleContext, Entity.Function>()

    private val typeNameMap = mutableMapOf<ParserRuleContext, TypeName>()

    private val rootScope = Scope(ScopeKind.FILE, null)
    private var currentScope = rootScope

    fun enterFileScope(ctx: ParserRuleContext) {
        scopeMap[ctx] = rootScope
    }

    fun exitFileScope(ctx: ParserRuleContext) {
        require(currentScope === rootScope) { "scope mismatch at file exit" }
        require(currentScope === scopeMap[ctx]) { "scope context mismatch" }
    }

    fun createNewScope(ctx: ParserRuleContext, kind: ScopeKind): Scope {
        val newScope = Scope(kind, currentScope)
        currentScope.children.add(newScope)
        currentScope = newScope
        scopeMap[ctx] = newScope
        return newScope
    }

    fun popScope(ctx: ParserRuleContext, kind: ScopeKind) {
        require(currentScope.kind == kind) { "scope kind mismatch. Expected $kind, but got ${currentScope.kind}" }
        require(currentScope === scopeMap[ctx]) { "scope context mismatch" }
        val parent = currentScope.parent
        requireNotNull(parent)
        currentScope = parent
    }

    fun defineTypedef(
        location: SourceLocation,
        declarationSpecifier: DeclarationSpecifier,
        declarator: Declarator,
    ): Declaration.Typedef {
        val typedef = Declaration.Typedef(location, currentScope, declarationSpecifier, declarator)
        val name = typedef.name
        if (name == null) {
            reporter.reportError(location, "Typedef should have a name")
        } else {
            currentScope.addTypedefDeclaration(name, typedef)
        }
        return typedef
    }

    fun defineVariable(
        ctx: ParserRuleContext,
        location: SourceLocation,
        declarationSpecifier: DeclarationSpecifier,
        declarator: Declarator,
        initializer: CParser.InitializerContext?,
    ): Declaration.Variable {
        val variable = Declaration.Variable(location, currentScope, declarationSpecifier, declarator, initializer)
        val name = variable.name
        if (name == null) {
            reporter.reportError(location, "Variable should have a name")
        } else {
            variableMap[ctx] = currentScope.addVariableDeclaration(name, variable)
        }
        return variable
    }

    fun defineFunction(
        ctx: ParserRuleContext,
        location: SourceLocation,
        declarationSpecifier: DeclarationSpecifier,
        declarator: Declarator,
        parameters: List<Parameter>,
    ): Declaration.Function {
        val function = Declaration.Function(location, currentScope, declarationSpecifier, declarator, parameters)
        val name = function.name
        if (name == null) {
            reporter.reportError(location, "Function should have a name")
        } else {
            functionMap[ctx] = currentScope.addFunctionDeclaration(name, function)
        }
        return function
    }

    fun defineStruct(
        location: SourceLocation,
        name: String?,
        structDeclarations: List<StructDeclaration>,
    ) {
        val struct = Declaration.Struct(location, currentScope, name, structDeclarations)
        if (name != null) {
            currentScope.defineTag(name)
        }
    }

    fun defineEnum(
        location: SourceLocation,
        name: String?,
        enumerators: List<Enumerator>,
    ) {
        val enum = Declaration.Enum(location, currentScope, name, enumerators)
        if (name != null) {
            currentScope.defineTag(name)
        }
    }

    fun <T> withScope(ctx: ParserRuleContext, kind: ScopeKind, block: (Scope) -> T): T {
        val scope = scopeMap[ctx] ?: error("Missing scope for ${ctx::class.simpleName}")
        require(scope.kind == kind) { "scope kind mismatch" }
        val prev = currentScope
        currentScope = scope
        try {
            return block(scope)
        } finally {
            currentScope = prev
        }
    }

    fun assertNoScope(ctx: ParserRuleContext) {
        require(scopeMap[ctx] == null) { "Unexpected scope for ${ctx::class.simpleName}" }
    }

    fun markCurrentScopeSynthetic() {
        require(currentScope.isEmpty)
        currentScope.isSynthetic = true
    }

    fun registerTypeName(ctx: ParserRuleContext, typeName: TypeName) {
        typeNameMap[ctx] = typeName
    }

    fun getTypeName(ctx: ParserRuleContext): TypeName? {
        return typeNameMap[ctx]
    }

    fun isTypedefName(name: String): Boolean {
        return currentScope.isTypedefName(name)
    }

    operator fun get(ctx: ParserRuleContext): Scope? {
        return scopeMap[ctx]
    }

    fun resolveTentativeDefinitions() {
        rootScope.resolveTentativeDefinitions()
    }
}
