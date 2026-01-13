package org.erwinkok.conjvm.declarations

import org.antlr.v4.runtime.ParserRuleContext

class ScopeManager {
    private val scopeMap = mutableMapOf<ParserRuleContext, Scope>()

    val rootScope = Scope(ScopeKind.FILE, null)
    var currentScope = rootScope
        private set

    operator fun get(ctx: ParserRuleContext): Scope? {
        return scopeMap[ctx]
    }
}
