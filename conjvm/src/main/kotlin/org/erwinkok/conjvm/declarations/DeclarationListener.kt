package org.erwinkok.conjvm.declarations

import org.antlr.v4.runtime.ParserRuleContext
import org.erwinkok.conjvm.CBaseListener
import org.erwinkok.conjvm.CParser
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.SourceFile
import org.erwinkok.conjvm.parser.SourceLocation
import org.erwinkok.conjvm.utils.ParserReporting

class DeclarationListener(
    override val reporter: ErrorReporter,
    override val source: SourceFile,
    private val entityTable: EntityTable,
) : CBaseListener(),
    ParserReporting {
    private val declarationParser = DeclarationParser(reporter, source)
    private val structDeclarationsStack = ArrayDeque<MutableList<StructDeclaration>>()
    private val enumeratorStack = ArrayDeque<MutableList<Enumerator>>()
    private val rootScope = Scope(ScopeKind.FILE, null)
    private var currentScope = rootScope

    override fun enterCompilationUnit(ctx: CParser.CompilationUnitContext) {
        entityTable.registerScope(ctx, rootScope)
    }

    override fun exitCompilationUnit(ctx: CParser.CompilationUnitContext) {
        require(structDeclarationsStack.isEmpty())
        require(enumeratorStack.isEmpty())
        require(currentScope === rootScope) { "scope mismatch at file exit" }
        require(currentScope === entityTable.getScope(ctx)) { "scope context mismatch" }
        resolveTentativeDefinitions(rootScope)
    }

    override fun enterFunction_definition(ctx: CParser.Function_definitionContext) {
        enterNewScope(ctx, ScopeKind.FUNCTION)
    }

    override fun exitFunction_definition(ctx: CParser.Function_definitionContext) {
        val declarationSpecifier = declarationParser.visit(ctx.declaration_specifiers()).cast<DeclarationSpecifier>()
        val declarator = declarationParser.visit(ctx.declarator()).cast<Declarator>()
        if (declarator is Declarator.FunctionDeclarator) {
            defineFunction(
                ctx = ctx,
                scope = currentScope,
                declarationSpecifier = declarationSpecifier,
                declarator = declarator,
                parameters = declarator.parameters,
                isDefinition = true,
            )?.let {
                entityTable.registerFunction(ctx, it)
            }
            declarator.parameters.forEach { param ->
                defineVariable(
                    ctx = ctx,
                    scope = currentScope,
                    declarationSpecifier = param.declarationSpecifier,
                    declarator = param.declarator,
                    initializer = null,
                )?.let {
                    entityTable.registerVariable(ctx, it)
                }
            }
        } else {
            defineFunction(
                ctx = ctx,
                scope = currentScope,
                declarationSpecifier = declarationSpecifier,
                declarator = declarator,
                parameters = emptyList(),
                isDefinition = true,
            )?.let {
                entityTable.registerFunction(ctx, it)
            }
        }
        exitScope(ctx, ScopeKind.FUNCTION)
    }

    override fun enterBlock_statement(ctx: CParser.Block_statementContext) {
        enterNewScope(ctx, ScopeKind.BLOCK)
    }

    override fun exitBlock_statement(ctx: CParser.Block_statementContext) {
        exitScope(ctx, ScopeKind.BLOCK)
    }

    override fun enterFor_statement(ctx: CParser.For_statementContext) {
        // Because the parse tree is not yet complete here, we do not yet know whether new variables are
        // declared or not (ForInitVarDeclContext).
        // Hence, we don't know whether to create a new scope or not. Therefore, always create a new scope.
        enterNewScope(ctx, ScopeKind.FOR)
    }

    override fun exitFor_statement(ctx: CParser.For_statementContext) {
        // Since we always create a scope, mark it synthetic when we didn't create new variables is null.
        if (ctx.init !is CParser.ForInitVarDeclContext) {
            currentScope.markAsSynthetic()
        }
        exitScope(ctx, ScopeKind.FOR)
    }

    override fun exitDeclaration(ctx: CParser.DeclarationContext) {
        val declarationSpecifier = declarationParser.visit(ctx.declaration_specifiers()).cast<DeclarationSpecifier>()
        val isTypedef = declarationSpecifier.hasTypedef
        val initDeclaratorList = ctx.init_declarator_list()
        if (initDeclaratorList != null) {
            val declarators = declarationParser.visit(initDeclaratorList).cast<List<InitDeclarator>>()
            declarators.forEach { (declarator, initializer) ->
                handleDeclarator(ctx, declarationSpecifier, declarator, initializer)
            }
        } else if (isTypedef) {
            handleTypedefWithoutInitDeclaratorList(ctx, declarationSpecifier)
        }
    }

    override fun exitType_name(ctx: CParser.Type_nameContext) {
        val declarationSpecifier = declarationParser.visit(ctx.specifier_qualifier_list()).cast<DeclarationSpecifier>()
        val declarator = ctx.abstract_declarator()?.let { declarationParser.visit(it).cast<Declarator>() } ?: Declarator.AnonymousDeclarator(ctx.location)
        entityTable.registerTypeName(ctx, TypeName(ctx.location, declarationSpecifier, declarator))
    }

    override fun enterStruct_specifier(ctx: CParser.Struct_specifierContext) {
        structDeclarationsStack.addLast(mutableListOf())
    }

    override fun exitStruct_specifier(ctx: CParser.Struct_specifierContext) {
        val structDeclarations = structDeclarationsStack.removeLast()
        val name = ctx.Identifier()?.text
        val struct = defineStruct(
            ctx = ctx,
            scope = currentScope,
            name = name,
            structDeclarations = structDeclarations,
        )
        entityTable.registerStruct(ctx, struct)
    }

    override fun exitStruct_declaration(ctx: CParser.Struct_declarationContext) {
        requireNotNull(structDeclarationsStack.lastOrNull())
        val declarationSpecifier = declarationParser.visit(ctx.specifier_qualifier_list()).cast<DeclarationSpecifier>()
        val declarators = ctx.struct_declarator_list()?.let { declarationParser.visit(it).cast<List<StructDeclarator>>() }
        if (declarators != null) {
            structDeclarationsStack.last().add(StructDeclaration(ctx.location, declarationSpecifier, declarators))
        }
    }

    override fun enterEnum_specifier(ctx: CParser.Enum_specifierContext) {
        enumeratorStack.addLast(mutableListOf())
    }

    override fun exitEnum_specifier(ctx: CParser.Enum_specifierContext) {
        val enumerators = enumeratorStack.removeLast()
        val name = ctx.Identifier()?.text
        val enum = defineEnum(
            ctx = ctx,
            scope = currentScope,
            name = name,
            enumerators = enumerators,
        )
        entityTable.registerEnum(ctx, enum)
    }

    override fun exitEnumerator(ctx: CParser.EnumeratorContext) {
        requireNotNull(enumeratorStack.lastOrNull())
        enumeratorStack.last().add(Enumerator(ctx.location, ctx.Identifier().text, ctx.constant_expression()))
    }

    fun isTypedefName(name: String): Boolean {
        return currentScope.isTypedefName(name)
    }

    private fun handleDeclarator(
        ctx: ParserRuleContext,
        declarationSpecifier: DeclarationSpecifier,
        declarator: Declarator,
        initializer: CParser.InitializerContext?,
    ) {
        val location = ctx.location
        validateDeclaration(location, declarationSpecifier, declarator)

        when (declarator) {
            is Declarator.FunctionDeclarator -> {
                if (initializer != null) {
                    reporter.reportError(location, "function should not carry an initializer")
                }
                defineFunction(
                    ctx = ctx,
                    scope = currentScope,
                    declarationSpecifier = declarationSpecifier,
                    declarator = declarator,
                    parameters = declarator.parameters,
                    isDefinition = false,
                )?.let {
                    entityTable.registerFunction(ctx, it)
                }
            }

            is Declarator.PointerDeclarator,
            is Declarator.ArrayDeclarator,
            is Declarator.IdentifierDeclarator,
            -> {
                val isTypedef = declarationSpecifier.hasTypedef
                if (isTypedef) {
                    if (initializer != null) {
                        reporter.reportError(location, "typedef should not carry an initializer")
                    }
                    defineTypedef(
                        ctx = ctx,
                        scope = currentScope,
                        declarationSpecifier = declarationSpecifier,
                        declarator = declarator,
                    )?.let {
                        entityTable.registerTypedef(ctx, it)
                    }
                } else {
                    defineVariable(
                        ctx = ctx,
                        scope = currentScope,
                        declarationSpecifier = declarationSpecifier,
                        declarator = declarator,
                        initializer = initializer,
                    )?.let {
                        entityTable.registerVariable(ctx, it)
                    }
                }
            }

            is Declarator.AnonymousDeclarator -> {
                reporter.reportError(location, "object declaration requires a name")
            }

            is Declarator.BitFieldDeclarator -> {
                reporter.reportError(location, "bit-field outside of struct")
            }
        }
    }

    private fun handleTypedefWithoutInitDeclaratorList(
        ctx: CParser.DeclarationContext,
        declarationSpecifier: DeclarationSpecifier,
    ) {
        // The C grammar specifies the following:
        //
        // declaration_specifiers init_declarator_list? ';'
        //
        // When something like "typedef unsigned int a, b;" is defined, no ambiguity occurs since "a, b" must be
        // part of "init_declarator_list". However, when there is only a single declarator, the declarator can be
        // treated as part of the declaration_specifiers since init_declarator_list might be null.
        val typedefName = declarationSpecifier.typeSpecs.filterIsInstance<TypeSpec.TypedefName>().lastOrNull()
        typedefName?.let {
            defineTypedef(
                ctx = ctx,
                scope = currentScope,
                declarationSpecifier = declarationSpecifier,
                declarator = Declarator.IdentifierDeclarator(ctx.location, it.name),
            )?.let {
                entityTable.registerTypedef(ctx, it)
            }
        }
    }

    private fun validateDeclaration(
        location: SourceLocation,
        declarationSpecifier: DeclarationSpecifier,
        declarator: Declarator,
    ) {
        // Multiple storage classes
        if (declarationSpecifier.storage.size > 1) {
            reporter.reportError(location, "multiple storage classes in declaration")
        }

        // Function can't have certain storage classes
        if (declarator is Declarator.FunctionDeclarator) {
            if (
                declarationSpecifier.storage.contains(StorageClass.REGISTER) ||
                declarationSpecifier.storage.contains(StorageClass.AUTO)
            ) {
                reporter.reportError(location, "invalid storage class for function")
            }
        }

        // typedef with additional storage class
        if (declarationSpecifier.hasTypedef && declarationSpecifier.storage.size > 1) {
            reporter.reportError(location, "typedef cannot be combined with other storage classes")
        }
    }

    private fun enterNewScope(ctx: ParserRuleContext, kind: ScopeKind): Scope {
        val newScope = Scope(kind, currentScope)
        currentScope.children.add(newScope)
        currentScope = newScope
        entityTable.registerScope(ctx, newScope)
        return newScope
    }

    private fun exitScope(ctx: ParserRuleContext, kind: ScopeKind) {
        require(currentScope.kind == kind) { "scope kind mismatch. Expected $kind, but got ${currentScope.kind}" }
        require(currentScope === entityTable.getScope(ctx)) { "scope context mismatch" }
        val parent = currentScope.parent
        requireNotNull(parent)
        currentScope = parent
    }

    private fun defineTypedef(
        ctx: ParserRuleContext,
        scope: Scope,
        declarationSpecifier: DeclarationSpecifier,
        declarator: Declarator,
    ): Entity.Typedef? {
        val typedef = Declaration.Typedef(ctx.location, scope, declarationSpecifier, declarator)
        val name = typedef.name
        if (name == null) {
            reporter.reportError(ctx.location, "Typedef should have a name")
            return null
        }
        val entity = scope.getOrCreateTypedefEntity(name)
        entity.declarations.add(typedef)
        return entity
    }

    private fun defineVariable(
        ctx: ParserRuleContext,
        scope: Scope,
        declarationSpecifier: DeclarationSpecifier,
        declarator: Declarator,
        initializer: CParser.InitializerContext?,
    ): Entity.Variable? {
        val variable = Declaration.Variable(ctx.location, scope, declarationSpecifier, declarator, initializer)
        val name = variable.name
        if (name == null) {
            reporter.reportError(ctx.location, "Variable should have a name")
            return null
        }
        val entity = scope.getOrCreateVariableEntity(name)
        if (entity.declarations.isEmpty()) {
            entity.linkage = determineLinkage(variable, scope.kind)
        } else {
            // Validate linkage consistency on redeclaration
            val newLinkage = determineLinkage(variable, scope.kind)
            if (!isLinkageCompatible(entity.linkage, newLinkage)) {
                reporter.reportError(
                    ctx.location,
                    "conflicting linkage for '$name'",
                )
            }
        }
        entity.declarations.add(variable)
        if (variable.initializer != null) {
            val definition = entity.definition
            if (definition != null) {
                reporter.reportError(
                    ctx.location,
                    "redefinition of variable '$name'; previous definition at ${definition.location}",
                )
                return null
            } else {
                entity.definition = variable
            }
        }
        return entity
    }

    private fun defineFunction(
        ctx: ParserRuleContext,
        scope: Scope,
        declarationSpecifier: DeclarationSpecifier,
        declarator: Declarator,
        parameters: List<Parameter>,
        isDefinition: Boolean,
    ): Entity.Function? {
        val function = Declaration.Function(ctx.location, scope, declarationSpecifier, declarator, parameters)
        val name = function.name
        if (name == null) {
            reporter.reportError(ctx.location, "Function should have a name")
            return null
        }
        val entity = scope.getOrCreateFunctionEntity(name)
        if (entity.declarations.isEmpty()) {
            entity.linkage = when {
                declarationSpecifier.storage.contains(StorageClass.STATIC) -> Linkage.INTERNAL
                declarationSpecifier.storage.contains(StorageClass.EXTERN) -> Linkage.EXTERNAL
                else -> Linkage.EXTERNAL // Functions default to external linkage
            }
        }
        entity.declarations.add(function)
        if (isDefinition) {
            val definition = entity.definition
            if (definition != null) {
                reporter.reportError(
                    ctx.location,
                    "redefinition of function '$name'; previous definition at ${definition.location}",
                )
            } else {
                entity.definition = function
            }
        }
        return entity
    }

    private fun defineStruct(
        ctx: ParserRuleContext,
        scope: Scope,
        name: String?,
        structDeclarations: List<StructDeclaration>,
    ): Entity.Struct {
        val struct = Declaration.Struct(ctx.location, scope, name, structDeclarations)
        val entity = scope.getOrCreateStructEntity(name)
        entity.declarations.add(struct)
        if (struct.isDefinition) {
            val definition = entity.definition
            if (definition != null) {
                reporter.reportError(
                    ctx.location,
                    "redefinition of struct '$name'; previous definition at ${definition.location}",
                )
            } else {
                entity.definition = struct
            }
        }
        return entity
    }

    private fun defineEnum(
        ctx: ParserRuleContext,
        scope: Scope,
        name: String?,
        enumerators: List<Enumerator>,
    ): Entity.Enum {
        val enum = Declaration.Enum(ctx.location, scope, name, enumerators)
        val entity = scope.getOrCreateEnumEntity(name)
        entity.declarations.add(enum)
        return entity
    }

    private fun defineLabel(
        ctx: ParserRuleContext,
        scope: Scope,
        name: String,
        isDefinition: Boolean,
    ): Entity.Label {
        val label = Declaration.Label(ctx.location, scope, name, isDefinition)
        val entity = scope.getOrCreateLabelEntity(name)
        entity.declarations.add(label)
        return entity
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

    /**
     * Handles tentative definitions per C17 §6.9.2:
     * A declaration with external linkage and no initializer
     * is a tentative definition at file scope.
     */
    fun resolveTentativeDefinitions(scope: Scope) {
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
}
