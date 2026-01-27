package org.erwinkok.conjvm.declarations

import org.antlr.v4.runtime.ParserRuleContext

class EntityTable {
    private val scopeMap = mutableMapOf<ParserRuleContext, Scope>()
    private val typeNameMap = mutableMapOf<ParserRuleContext, TypeName>()

    private val typedefMap = mutableMapOf<ParserRuleContext, Entity.Typedef>()
    private val variableMap = mutableMapOf<ParserRuleContext, Entity.Variable>()
    private val functionMap = mutableMapOf<ParserRuleContext, Entity.Function>()
    private val structMap = mutableMapOf<ParserRuleContext, Entity.Struct>()
    private val enumMap = mutableMapOf<ParserRuleContext, Entity.Enum>()
    private val labelMap = mutableMapOf<ParserRuleContext, Entity.Label>()

    fun registerScope(ctx: ParserRuleContext, scope: Scope) {
        scopeMap[ctx] = scope
    }

    fun getScope(ctx: ParserRuleContext): Scope? {
        return scopeMap[ctx]
    }

    fun registerTypeName(ctx: ParserRuleContext, typeName: TypeName) {
        typeNameMap[ctx] = typeName
    }

    fun getTypeName(ctx: ParserRuleContext): TypeName? {
        return typeNameMap[ctx]
    }

    fun registerTypedef(ctx: ParserRuleContext, entity: Entity.Typedef) {
        typedefMap[ctx] = entity
    }

    fun registerVariable(ctx: ParserRuleContext, entity: Entity.Variable) {
        variableMap[ctx] = entity
    }

    fun registerFunction(ctx: ParserRuleContext, entity: Entity.Function) {
        functionMap[ctx] = entity
    }

    fun registerStruct(ctx: ParserRuleContext, entity: Entity.Struct) {
        structMap[ctx] = entity
    }

    fun registerEnum(ctx: ParserRuleContext, entity: Entity.Enum) {
        enumMap[ctx] = entity
    }

    fun registerLabel(ctx: ParserRuleContext, entity: Entity.Label) {
        labelMap[ctx] = entity
    }

    fun <T> withScope(ctx: ParserRuleContext, kind: ScopeKind, block: (Scope) -> T): T {
        val scope = scopeMap[ctx] ?: error("Missing scope for ${ctx::class.simpleName}")
        require(scope.kind == kind) { "scope kind mismatch" }
        return block(scope)
    }

    fun assertNoScope(ctx: ParserRuleContext) {
        require(scopeMap[ctx] == null) { "Unexpected scope for ${ctx::class.simpleName}" }
    }
}
