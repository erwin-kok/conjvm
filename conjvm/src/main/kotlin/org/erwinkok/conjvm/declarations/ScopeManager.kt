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
    private val structMap = mutableMapOf<ParserRuleContext, Entity.Struct>()
    private val enumMap = mutableMapOf<ParserRuleContext, Entity.Enum>()
    private val labelMap = mutableMapOf<ParserRuleContext, Entity.Label>()

    private val typeNameMap = mutableMapOf<ParserRuleContext, TypeName>()

    val rootScope = Scope(ScopeKind.FILE, null)
    var currentScope = rootScope
        private set

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
            val entity = currentScope.getOrCreateTypedefEntity(name)
            entity.declarations.add(typedef)
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
            val entity = currentScope.getOrCreateVariableEntity(name)
            if (entity.declarations.isEmpty()) {
                entity.linkage = determineLinkage(variable, currentScope.kind)
            } else {
                // Validate linkage consistency on redeclaration
                val newLinkage = determineLinkage(variable, currentScope.kind)
                if (!isLinkageCompatible(entity.linkage, newLinkage)) {
                    reporter.reportError(
                        location,
                        "conflicting linkage for '$name'",
                    )
                }
            }
            entity.declarations.add(variable)
            variableMap[ctx] = entity
            if (variable.initializer != null) {
                val definition = entity.definition
                if (definition != null) {
                    reporter.reportError(
                        location,
                        "redefinition of variable '$name'; previous definition at ${definition.location}",
                    )
                } else {
                    entity.definition = variable
                }
            }
        }
        return variable
    }

    fun defineFunction(
        ctx: ParserRuleContext,
        location: SourceLocation,
        declarationSpecifier: DeclarationSpecifier,
        declarator: Declarator,
        parameters: List<Parameter>,
        isDefinition: Boolean,
    ): Declaration.Function {
        val function = Declaration.Function(location, currentScope, declarationSpecifier, declarator, parameters)
        val name = function.name
        if (name == null) {
            reporter.reportError(location, "Function should have a name")
        } else {
            val entity = currentScope.getOrCreateFunctionEntity(name)
            if (entity.declarations.isEmpty()) {
                entity.linkage = when {
                    declarationSpecifier.storage.contains(StorageClass.STATIC) -> Linkage.INTERNAL
                    declarationSpecifier.storage.contains(StorageClass.EXTERN) -> Linkage.EXTERNAL
                    else -> Linkage.EXTERNAL // Functions default to external linkage
                }
            }
            entity.declarations.add(function)
            functionMap[ctx] = entity
            if (isDefinition) {
                val definition = entity.definition
                if (definition != null) {
                    reporter.reportError(
                        location,
                        "redefinition of function '$name'; previous definition at ${definition.location}",
                    )
                } else {
                    entity.definition = function
                }
            }
        }
        return function
    }

    fun defineStruct(
        ctx: ParserRuleContext,
        location: SourceLocation,
        name: String?,
        structDeclarations: List<StructDeclaration>,
    ) {
        val struct = Declaration.Struct(location, currentScope, name, structDeclarations)
        val entity = currentScope.getOrCreateStructEntity(name)
        entity.declarations.add(struct)
        structMap[ctx] = entity
        if (struct.isDefinition) {
            val definition = entity.definition
            if (definition != null) {
                reporter.reportError(
                    location,
                    "redefinition of struct '$name'; previous definition at ${definition.location}",
                )
            } else {
                entity.definition = struct
            }
        }
    }

    fun defineEnum(
        ctx: ParserRuleContext,
        location: SourceLocation,
        name: String?,
        enumerators: List<Enumerator>,
    ) {
        val enum = Declaration.Enum(location, currentScope, name, enumerators)
        val entity = currentScope.getOrCreateEnumEntity(name)
        entity.declarations.add(enum)
        enumMap[ctx] = entity
    }

    fun defineLabel(
        ctx: ParserRuleContext,
        location: SourceLocation,
        name: String,
        isDefinition: Boolean,
    ) {
        val label = Declaration.Label(location, currentScope, name, isDefinition)
        val entity = currentScope.getOrCreateLabelEntity(name)
        entity.declarations.add(label)
        labelMap[ctx] = entity
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

    /**
     * Handles tentative definitions per C17 §6.9.2:
     * A declaration with external linkage and no initializer
     * is a tentative definition at file scope.
     */
    fun resolveTentativeDefinitions() {
        resolveTentativeDefinitions(rootScope)
    }

    private fun resolveTentativeDefinitions(scope: Scope) {
        if (scope.kind == ScopeKind.FILE) {
            scope.variables.forEach { entity ->
                if (entity.definition == null && entity.linkage == Linkage.EXTERNAL) {
                    val declaration = entity.declarations.firstOrNull()
                    if (declaration != null) {
                        val hasExtern = declaration.declarationSpecifier.storage
                            .contains(StorageClass.EXTERN)
                        if (!hasExtern) {
                            val syntheticDeclaration = Declaration.Variable(
                                location = declaration.location,
                                scope = scope,
                                declarationSpecifier = declaration.declarationSpecifier,
                                declarator = declaration.declarator,
                                initializer = null,
                                isSyntheticZeroInit = true,
                            )
                            entity.declarations.add(syntheticDeclaration)
                            entity.definition = syntheticDeclaration
                        }
                    }
                }
            }
        }
        scope.children.forEach { resolveTentativeDefinitions(it) }
    }

    private fun determineLinkage(decl: Declaration.Variable, scopeKind: ScopeKind): Linkage {
        return when {
            decl.declarationSpecifier.storage.contains(StorageClass.EXTERN) -> Linkage.EXTERNAL
            decl.declarationSpecifier.storage.contains(StorageClass.STATIC) -> Linkage.INTERNAL
            scopeKind == ScopeKind.FILE -> Linkage.EXTERNAL
            else -> Linkage.NONE
        }
    }

    private fun isLinkageCompatible(existing: Linkage, new: Linkage): Boolean {
        // C17 §6.2.2: If the same identifier appears with both internal and external
        // linkage in the same translation unit, the behavior is undefined.
        return when (existing) {
            new -> true
            Linkage.EXTERNAL if new == Linkage.NONE -> false
            Linkage.NONE if new == Linkage.EXTERNAL -> false
            Linkage.INTERNAL if new == Linkage.EXTERNAL -> false
            Linkage.EXTERNAL if new == Linkage.INTERNAL -> false
            else -> true
        }
    }
}
