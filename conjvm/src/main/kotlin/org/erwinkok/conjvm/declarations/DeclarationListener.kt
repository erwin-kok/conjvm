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
    private val scopeManager: ScopeManager,
) : CBaseListener(),
    ParserReporting {
    private val declarationParser = DeclarationParser(reporter, source)
    private val structDeclarationsStack = ArrayDeque<MutableList<StructDeclaration>>()
    private val enumeratorStack = ArrayDeque<MutableList<Enumerator>>()

    override fun enterCompilationUnit(ctx: CParser.CompilationUnitContext) {
        scopeManager.enterFileScope(ctx)
    }

    override fun exitCompilationUnit(ctx: CParser.CompilationUnitContext) {
        require(structDeclarationsStack.isEmpty())
        require(enumeratorStack.isEmpty())
        scopeManager.exitFileScope(ctx)
        scopeManager.resolveTentativeDefinitions()
    }

    override fun enterFunction_definition(ctx: CParser.Function_definitionContext) {
        enterNewScope(ctx, ScopeKind.FUNCTION)
    }

    override fun exitFunction_definition(ctx: CParser.Function_definitionContext) {
        val declarationSpecifier = declarationParser.visit(ctx.declaration_specifiers()).cast<DeclarationSpecifier>()
        val declarator = declarationParser.visit(ctx.declarator()).cast<Declarator>()
        if (declarator is Declarator.FunctionDeclarator) {
            scopeManager.defineFunction(ctx.location, declarationSpecifier, declarator, declarator.parameters)
            declarator.parameters.forEach { param ->
                scopeManager.defineVariable(
                    location = ctx.location,
                    declarationSpecifier = param.declarationSpecifier,
                    declarator = param.declarator,
                )
            }
        } else {
            scopeManager.defineFunction(
                location = ctx.location,
                declarationSpecifier = declarationSpecifier,
                declarator = declarator,
                parameters = emptyList(),
            )
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
            scopeManager.markCurrentScopeSynthetic()
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
        scopeManager.registerTypeName(ctx, TypeName(ctx.location, declarationSpecifier, declarator))
    }

    override fun enterStruct_specifier(ctx: CParser.Struct_specifierContext) {
        structDeclarationsStack.addLast(mutableListOf())
    }

    override fun exitStruct_specifier(ctx: CParser.Struct_specifierContext) {
        val structDeclarations = structDeclarationsStack.removeLast()
        val name = ctx.Identifier()?.text
        scopeManager.defineStruct(ctx.location, name, structDeclarations)
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
        scopeManager.defineEnum(ctx.location, name, enumerators)
    }

    override fun exitEnumerator(ctx: CParser.EnumeratorContext) {
        requireNotNull(enumeratorStack.lastOrNull())
        enumeratorStack.last().add(Enumerator(ctx.location, ctx.Identifier().text, ctx.constant_expression()))
    }

    fun isTypedefName(name: String): Boolean {
        return scopeManager.isTypedefName(name)
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
                scopeManager.defineFunction(
                    location = location,
                    declarationSpecifier = declarationSpecifier,
                    declarator = declarator,
                    parameters = declarator.parameters,
                )
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
                    scopeManager.defineTypedef(
                        location = location,
                        declarationSpecifier = declarationSpecifier,
                        declarator = declarator,
                    )
                } else {
                    scopeManager.defineVariable(
                        location = location,
                        declarationSpecifier = declarationSpecifier,
                        declarator = declarator,
                    )
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
            scopeManager.defineTypedef(
                location = ctx.location,
                declarationSpecifier = declarationSpecifier,
                declarator = Declarator.IdentifierDeclarator(ctx.location, it.name),
            )
        }
    }

    private fun validateDeclaration(
        location: SourceLocation,
        declarationSpecifier: DeclarationSpecifier,
        declarator: Declarator,
    ) {
    }

    private fun enterNewScope(ctx: ParserRuleContext, kind: ScopeKind): Scope {
        return scopeManager.createNewScope(ctx, kind)
    }

    private fun exitScope(ctx: ParserRuleContext, kind: ScopeKind) {
        scopeManager.popScope(ctx, kind)
    }
}
