package org.erwinkok.conjvm.declarations

import org.antlr.v4.runtime.ParserRuleContext

class EntityTable {
    private val scopeCtxMap = mutableMapOf<ParserRuleContext, Scope>()
    private val typeNameCtxMap = mutableMapOf<ParserRuleContext, TypeName>()

    private val typedefCtxMap = mutableMapOf<ParserRuleContext, Entity.Typedef>()
    private val variableCtxMap = mutableMapOf<ParserRuleContext, MutableList<Entity.Variable>>()
    private val functionCtxMap = mutableMapOf<ParserRuleContext, Entity.Function>()
    private val structCtxMap = mutableMapOf<ParserRuleContext, Entity.Struct>()
    private val enumCtxMap = mutableMapOf<ParserRuleContext, Entity.Enum>()
    private val labelCtxMap = mutableMapOf<ParserRuleContext, Entity.Label>()

    private val typedefsByName = mutableMapOf<String, Entity.Typedef>()
    private val structsByName = mutableMapOf<String, Entity.Struct>()
    private val enumsByName = mutableMapOf<String, Entity.Enum>()

    val typedefs: Map<ParserRuleContext, Entity.Typedef>
        get() = typedefCtxMap
    val variables: Map<ParserRuleContext, List<Entity.Variable>>
        get() = variableCtxMap
    val functions: Map<ParserRuleContext, Entity.Function>
        get() = functionCtxMap
    val structs: Map<ParserRuleContext, Entity.Struct>
        get() = structCtxMap
    val enums: Map<ParserRuleContext, Entity.Enum>
        get() = enumCtxMap
    val labels: Map<ParserRuleContext, Entity.Label>
        get() = labelCtxMap

    // ========================================================================
    // REGISTER METHODS
    // ========================================================================

    fun registerScope(ctx: ParserRuleContext, scope: Scope) {
        scopeCtxMap[ctx] = scope
    }

    fun registerTypeName(ctx: ParserRuleContext, typeName: TypeName) {
        typeNameCtxMap[ctx] = typeName
    }

    fun registerTypedef(ctx: ParserRuleContext, entity: Entity.Typedef) {
        typedefCtxMap[ctx] = entity
        typedefsByName[entity.name] = entity
    }

    fun registerVariable(ctx: ParserRuleContext, entity: Entity.Variable) {
        variableCtxMap.computeIfAbsent(ctx) { mutableListOf() }.add(entity)
    }

    fun registerFunction(ctx: ParserRuleContext, entity: Entity.Function) {
        functionCtxMap[ctx] = entity
    }

    fun registerStruct(ctx: ParserRuleContext, entity: Entity.Struct) {
        structCtxMap[ctx] = entity
        if (entity.name != null) {
            structsByName[entity.name] = entity
        }
    }

    fun registerEnum(ctx: ParserRuleContext, entity: Entity.Enum) {
        enumCtxMap[ctx] = entity
        if (entity.name != null) {
            enumsByName[entity.name] = entity
        }
    }

    fun registerLabel(ctx: ParserRuleContext, entity: Entity.Label) {
        labelCtxMap[ctx] = entity
    }

    // ========================================================================
    // GET BY PARSER CONTEXT METHODS
    // ========================================================================

    fun getScope(ctx: ParserRuleContext): Scope? {
        return scopeCtxMap[ctx]
    }

    fun getTypeName(ctx: ParserRuleContext): TypeName? {
        return typeNameCtxMap[ctx]
    }

    fun getTypeDef(ctx: ParserRuleContext): Entity.Typedef? {
        return typedefCtxMap[ctx]
    }

    fun getVariables(ctx: ParserRuleContext): List<Entity.Variable>? {
        return variableCtxMap[ctx]
    }

    fun getFunction(ctx: ParserRuleContext): Entity.Function? {
        return functionCtxMap[ctx]
    }

    fun getStruct(ctx: ParserRuleContext): Entity.Struct? {
        return structCtxMap[ctx]
    }

    fun getEnum(ctx: ParserRuleContext): Entity.Enum? {
        return enumCtxMap[ctx]
    }

    fun getLabel(ctx: ParserRuleContext): Entity.Label? {
        return labelCtxMap[ctx]
    }

    // ========================================================================
    // GET BY NAME METHODS
    // ========================================================================

    fun getTypedefByName(name: String): Entity.Typedef? {
        return typedefsByName[name]
    }

    fun getStructByName(name: String): Entity.Struct {
        return structsByName[name] ?: throw DeclarationException("Undefined struct: $name")
    }

    fun getEnumByName(name: String): Entity.Enum {
        return enumsByName[name] ?: throw DeclarationException("Undefined enum: $name")
    }
}
