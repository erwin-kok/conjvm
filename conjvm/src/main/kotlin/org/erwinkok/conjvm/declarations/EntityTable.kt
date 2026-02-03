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

    private val typedefsByName = mutableMapOf<String, Entity.Typedef>()
    private val structsByName = mutableMapOf<String, Entity.Struct>()
    private val enumsByName = mutableMapOf<String, Entity.Enum>()

    val typedefs: Map<ParserRuleContext, Entity.Typedef>
        get() = typedefMap
    val variables: Map<ParserRuleContext, Entity.Variable>
        get() = variableMap
    val functions: Map<ParserRuleContext, Entity.Function>
        get() = functionMap
    val structs: Map<ParserRuleContext, Entity.Struct>
        get() = structCtxMap
    val enums: Map<ParserRuleContext, Entity.Enum>
        get() = enumCtxMap
    val labels: Map<ParserRuleContext, Entity.Label>
        get() = labelMap

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

    fun registerVariable(ctx: ParserRuleContext, entity: Entity.Variable) {
        variableMap[ctx] = entity
    }

    fun registerFunction(ctx: ParserRuleContext, entity: Entity.Function) {
        functionMap[ctx] = entity
    }

    fun registerTypedef(ctx: ParserRuleContext, entity: Entity.Typedef) {
        typedefMap[ctx] = entity
        typedefsByName[entity.name] = entity
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
        labelMap[ctx] = entity
    }

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
