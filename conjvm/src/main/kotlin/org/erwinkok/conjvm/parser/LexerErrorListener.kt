package org.erwinkok.conjvm.parser

import org.antlr.v4.runtime.BaseErrorListener
import org.antlr.v4.runtime.RecognitionException
import org.antlr.v4.runtime.Recognizer

class LexerErrorListener(
    private val source: SourceFile,
    private val diagnostics: MutableList<Diagnostic>,
) : BaseErrorListener() {
    override fun syntaxError(recognizer: Recognizer<*, *>, offendingSymbol: Any?, line: Int, charPositionInLine: Int, msg: String, e: RecognitionException) {
        diagnostics += Diagnostic(
            severity = Severity.ERROR,
            message = msg,
            line = line,
            column = charPositionInLine,
            length = 1,
            sourceName = source.name,
        )
    }
}
