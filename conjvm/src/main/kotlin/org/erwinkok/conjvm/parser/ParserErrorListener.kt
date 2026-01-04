package org.erwinkok.conjvm.parser

import org.antlr.v4.runtime.BaseErrorListener
import org.antlr.v4.runtime.RecognitionException
import org.antlr.v4.runtime.Recognizer
import org.antlr.v4.runtime.Token

class ParserErrorListener(
    private val source: SourceFile,
    private val diagnostics: MutableList<Diagnostic>,
) : BaseErrorListener() {
    override fun syntaxError(recognizer: Recognizer<*, *>, offendingSymbol: Any?, line: Int, charPositionInLine: Int, msg: String, e: RecognitionException) {
        val token = offendingSymbol as? Token
        val length = if (token != null && token.stopIndex >= token.startIndex) {
            token.stopIndex - token.startIndex + 1
        } else {
            1
        }
        diagnostics += Diagnostic(
            severity = Severity.ERROR,
            message = msg,
            line = line,
            column = charPositionInLine,
            length = length,
            sourceName = source.name,
        )
    }
}
