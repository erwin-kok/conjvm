package org.erwinkok.conjvm.declarations

import org.antlr.v4.runtime.ParserRuleContext
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.SourceLocation

class ScopeManager(
    private val reporter: ErrorReporter,
) {
    private val scopeMap = mutableMapOf<ParserRuleContext, Scope>()
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
    ): Entity.Typedef {
        return currentScope.defineTypedef(location, declarationSpecifier, declarator)
    }

    fun defineFunction(
        location: SourceLocation,
        declarationSpecifier: DeclarationSpecifier,
        declarator: Declarator,
        parameters: List<Parameter>,
    ): Entity.Function {
        return currentScope.defineFunction(location, declarationSpecifier, declarator, parameters)
    }

    fun defineVariable(
        location: SourceLocation,
        declarationSpecifier: DeclarationSpecifier,
        declarator: Declarator,
    ): Entity.Variable {
        return currentScope.defineVariable(location, declarationSpecifier, declarator)
    }

    fun defineStructTag(
        location: SourceLocation,
        text: String?,
        memberScope: Scope,
    ): Entity.Tag.Struct {
        return currentScope.defineStructTag(location, text, memberScope)
    }

    fun defineEnumTag(
        location: SourceLocation,
        text: String?,
    ): Entity.Tag.Enum {
        return currentScope.defineEnumTag(location, text)
    }

    fun defineEnumerator(
        location: SourceLocation,
        name: String,
    ): Entity.Enumerator {
        return currentScope.defineEnumerator(location, name)
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
