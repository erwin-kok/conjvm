package org.erwinkok.conjvm.parser

import org.antlr.v4.runtime.ParserRuleContext
import org.antlr.v4.runtime.Token

class SemanticReporter(
    protected val diagnostics: MutableList<Diagnostic>,
    protected val source: SourceFile,
) {
    protected fun error(token: Token, message: String) {
        diagnostics += Diagnostic(
            severity = Severity.ERROR,
            message = message,
            line = token.line,
            column = token.charPositionInLine,
            length = token.text?.length ?: 1,
            sourceName = source.name,
        )
    }

    protected fun warning(token: Token, message: String) {
        diagnostics += Diagnostic(
            severity = Severity.WARNING,
            message = message,
            line = token.line,
            column = token.charPositionInLine,
            length = token.text?.length ?: 1,
            sourceName = source.name,
        )
    }

    protected fun error(ctx: ParserRuleContext, message: String) {
        val start = ctx.start
        val stop = ctx.stop ?: start
        val length = stop.stopIndex - start.startIndex + 1
        diagnostics += Diagnostic(
            severity = Severity.ERROR,
            message = message,
            line = start.line,
            column = start.charPositionInLine,
            length = length,
            sourceName = source.name,
        )
    }

    protected fun warning(ctx: ParserRuleContext, message: String) {
        val start = ctx.start
        val stop = ctx.stop ?: start
        val length = stop.stopIndex - start.startIndex + 1
        diagnostics += Diagnostic(
            severity = Severity.WARNING,
            message = message,
            line = start.line,
            column = start.charPositionInLine,
            length = length,
            sourceName = source.name,
        )
    }
}
