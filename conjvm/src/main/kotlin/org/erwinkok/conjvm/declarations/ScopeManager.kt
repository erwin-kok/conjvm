package org.erwinkok.conjvm.declarations

import org.antlr.v4.runtime.ParserRuleContext
import org.erwinkok.conjvm.CParser
import org.erwinkok.conjvm.parser.SourceLocation

class ScopeManager {
    private val scopeMap = mutableMapOf<ParserRuleContext, Scope>()
    private val typeNameMap = mutableMapOf<ParserRuleContext, TypeName>()

    val rootScope = Scope(ScopeKind.FILE, null)
    var currentScope = rootScope
        private set

    operator fun get(ctx: ParserRuleContext): Scope? {
        return scopeMap[ctx]
    }

    fun getTypeName(ctx: ParserRuleContext): TypeName? {
        return typeNameMap[ctx]
    }

    fun createNewScope(ctx: ParserRuleContext, kind: ScopeKind): Scope {
        val newScope = Scope(kind, currentScope)
        scopeMap[ctx] = newScope
        currentScope.children.add(newScope)
        currentScope = newScope
        return newScope
    }

    fun popScope() {
        val parent = currentScope.parent
        requireNotNull(parent)
        currentScope = parent
    }

    fun defineTypedef(location: SourceLocation, declarationSpecifier: DeclarationSpecifier, declarator: Declarator): DeclStub.Typedef {
        return currentScope.defineTypedef(location, declarationSpecifier, declarator)
    }

    fun defineFunction(location: SourceLocation, declarationSpecifier: DeclarationSpecifier, declarator: Declarator, parameters: List<Parameter>): DeclStub.Function {
        return currentScope.defineFunction(location, declarationSpecifier, declarator, parameters)
    }

    fun defineVariable(location: SourceLocation, declarationSpecifier: DeclarationSpecifier, declarator: Declarator): DeclStub.Variable {
        return currentScope.defineVariable(location, declarationSpecifier, declarator)
    }

    fun defineStructTag(location: SourceLocation, text: String?, memberScope: Scope): DeclTagStub.Struct {
        return currentScope.defineStructTag(location, text, memberScope)
    }

    fun defineEnumTag(location: SourceLocation, text: String?): DeclTagStub.Enum {
        return currentScope.defineEnumTag(location, text)
    }

    fun defineEnumerator(location: SourceLocation, name: String): DeclStub.Enumerator {
        return currentScope.defineEnumerator(location, name)
    }

    fun registerTypeName(ctx: CParser.Type_nameContext, typeName: TypeName) {
        typeNameMap[ctx] = typeName
    }
}
