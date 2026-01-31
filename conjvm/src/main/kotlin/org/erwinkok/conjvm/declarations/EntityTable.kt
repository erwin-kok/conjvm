package org.erwinkok.conjvm.declarations

import org.antlr.v4.runtime.ParserRuleContext

class EntityTable {
    private val scopeMap = mutableMapOf<ParserRuleContext, Scope>()
    private val typeNameMap = mutableMapOf<ParserRuleContext, TypeName>()

    private val typedefMap = mutableMapOf<ParserRuleContext, Entity.Typedef>()
    private val variableMap = mutableMapOf<ParserRuleContext, Entity.Variable>()
    private val functionMap = mutableMapOf<ParserRuleContext, Entity.Function>()
    private val structCtxMap = mutableMapOf<ParserRuleContext, Entity.Struct>()
    private val enumCtxMap = mutableMapOf<ParserRuleContext, Entity.Enum>()
    private val labelMap = mutableMapOf<ParserRuleContext, Entity.Label>()

    private val structMap = mutableMapOf<String, Entity.Struct>()
    private val enumMap = mutableMapOf<String, Entity.Enum>()

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

    fun registerStruct(ctx: ParserRuleContext, name: String?, entity: Entity.Struct) {
        structCtxMap[ctx] = entity
        if (name != null) {
            structMap[name] = entity
        }
    }

    fun getStructByName(name: String): Entity.Struct? {
        return structMap[name]
    }

    fun registerEnum(ctx: ParserRuleContext, name: String?, entity: Entity.Enum) {
        enumCtxMap[ctx] = entity
        if (name != null) {
            enumMap[name] = entity
        }
    }

    fun getEnumByName(name: String): Entity.Enum? {
        return enumMap[name]
    }

    fun registerLabel(ctx: ParserRuleContext, entity: Entity.Label) {
        labelMap[ctx] = entity
    }
}
