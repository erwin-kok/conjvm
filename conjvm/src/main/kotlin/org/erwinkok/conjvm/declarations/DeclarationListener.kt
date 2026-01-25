package org.erwinkok.conjvm.declarations

import org.antlr.v4.runtime.ParserRuleContext
import org.erwinkok.conjvm.CBaseListener
import org.erwinkok.conjvm.CParser
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.SourceFile
import org.erwinkok.conjvm.utils.ParserReporting

class DeclarationListener(
    override val reporter: ErrorReporter,
    override val source: SourceFile,
    private val scopeManager: ScopeManager,
) : CBaseListener(),
    ParserReporting {
    private val declarationParser = DeclarationParser(reporter, source)
    private val structStack = ArrayDeque<Entity.Tag.Struct>()
    private val enumStack = ArrayDeque<Entity.Tag.Enum>()

    override fun enterCompilationUnit(ctx: CParser.CompilationUnitContext) {
        scopeManager.enterFileScope(ctx)
    }
    override fun exitCompilationUnit(ctx: CParser.CompilationUnitContext) {
        require(structStack.isEmpty())
        require(enumStack.isEmpty())
        scopeManager.exitFileScope(ctx)
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
                scopeManager.defineVariable(ctx.location, param.declarationSpecifier, param.declarator)
            }
        } else {
            scopeManager.defineFunction(ctx.location, declarationSpecifier, declarator, emptyList())
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
        enterNewScope(ctx, ScopeKind.FOR)
    }

    override fun exitFor_statement(ctx: CParser.For_statementContext) {
        if (ctx.init !is CParser.ForInitVarDeclContext) {
            require(scopeManager.currentScope.isEmpty)
            scopeManager.currentScope.isSynthetic = true
        }
        exitScope(ctx, ScopeKind.FOR)
    }

    override fun exitDeclaration(ctx: CParser.DeclarationContext) {
        val declarationSpecifier = declarationParser.visit(ctx.declaration_specifiers()).cast<DeclarationSpecifier>()
        val isTypedef = declarationSpecifier.hasTypedef
        val initDeclaratorList = ctx.init_declarator_list()
        if (initDeclaratorList != null) {
            val declarators = declarationParser.visit(initDeclaratorList).cast<List<Declarator>>()
            declarators.forEach { declarator ->
                when (declarator) {
                    is Declarator.FunctionDeclarator -> {
                        scopeManager.defineFunction(ctx.location, declarationSpecifier, declarator, declarator.parameters)
                    }

                    is Declarator.PointerDeclarator,
                    is Declarator.ArrayDeclarator,
                    is Declarator.IdentifierDeclarator,
                    is Declarator.AnonymousDeclarator,
                    is Declarator.BitFieldDeclarator,
                    -> {
                        if (isTypedef) {
                            scopeManager.defineTypedef(ctx.location, declarationSpecifier, declarator)
                        } else {
                            scopeManager.defineVariable(ctx.location, declarationSpecifier, declarator)
                        }
                    }
                }
            }
        } else if (isTypedef) {
            // The C grammar specifies the following:
            //
            // declaration_specifiers init_declarator_list? ';'
            //
            // When something like "typedef unsigned int a, b;" is defined, no ambiguity occurs since "a, b" must be
            // part of "init_declarator_list". However, when there is only a single declarator, the declarator can be
            // treated as part of the declaration_specifiers since init_declarator_list might be null.
            val typedefName = declarationSpecifier.typeSpecs.filterIsInstance<TypeSpec.TypedefName>().lastOrNull()
            typedefName?.let {
                scopeManager.defineTypedef(ctx.location, declarationSpecifier, Declarator.IdentifierDeclarator(ctx.location, it.name))
            }
        }
    }

    override fun exitType_name(ctx: CParser.Type_nameContext) {
        val declarationSpecifier = declarationParser.visit(ctx.specifier_qualifier_list()).cast<DeclarationSpecifier>()
        val declarator = ctx.abstract_declarator()?.let { declarationParser.visit(it).cast<Declarator>() } ?: Declarator.AnonymousDeclarator(ctx.location)
        scopeManager.registerTypeName(ctx, TypeName(ctx.location, declarationSpecifier, declarator))
    }

    override fun enterStruct_specifier(ctx: CParser.Struct_specifierContext) {
        val name = ctx.Identifier()?.text
        val memberScope = enterNewScope(ctx, ScopeKind.STRUCT)
        val structDecl = scopeManager.defineStructTag(ctx.location, name, memberScope)
        structStack.addLast(structDecl)
    }

    override fun exitStruct_specifier(ctx: CParser.Struct_specifierContext) {
        structStack.removeLast()
        if (ctx.struct_declaration_list() == null) {
            require(scopeManager.currentScope.isEmpty)
            scopeManager.currentScope.isSynthetic = true
        }
        exitScope(ctx, ScopeKind.STRUCT)
    }

    override fun exitStruct_declaration(ctx: CParser.Struct_declarationContext) {
        requireNotNull(structStack.lastOrNull())
        val declarationSpecifier = declarationParser.visit(ctx.specifier_qualifier_list()).cast<DeclarationSpecifier>()
        val declarators = ctx.struct_declarator_list()?.let { declarationParser.visit(it).cast<List<StructDeclarator>>() }
        if (declarators != null) {
            val structDecl = structStack.last()
            structDecl.addStructDeclaration(StructDeclaration(ctx.location, declarationSpecifier, declarators))
        }
    }

    override fun enterEnum_specifier(ctx: CParser.Enum_specifierContext) {
        val name = ctx.Identifier()?.text
        val enumDecl = scopeManager.defineEnumTag(ctx.location, name)
        enumStack.addLast(enumDecl)
    }

    override fun exitEnum_specifier(ctx: CParser.Enum_specifierContext) {
        enumStack.removeLast()
    }

    override fun exitEnumerator(ctx: CParser.EnumeratorContext) {
        requireNotNull(enumStack.lastOrNull())
        val enumerator = scopeManager.defineEnumerator(ctx.location, ctx.Identifier().text)
        val enumDecl = enumStack.last()
        enumDecl.addEnumerator(enumerator)
    }

    override fun exitTypedef_name(ctx: CParser.Typedef_nameContext) {
        super.enterTypedef_name(ctx)
    }

    fun isTypedefName(name: String): Boolean {
        return scopeManager.currentScope.lookupTypedef(name).isNotEmpty()
    }

    private fun enterNewScope(ctx: ParserRuleContext, kind: ScopeKind): Scope {
        return scopeManager.createNewScope(ctx, kind)
    }

    private fun exitScope(ctx: ParserRuleContext, kind: ScopeKind) {
        scopeManager.popScope(ctx, kind)
    }
}
