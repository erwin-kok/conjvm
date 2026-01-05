package org.erwinkok.conjvm.parser

import org.antlr.v4.runtime.BaseErrorListener
import org.antlr.v4.runtime.RecognitionException
import org.antlr.v4.runtime.Recognizer

class LexerErrorListener(
    private val reporter: ErrorReporter,
    private val source: SourceFile,
) : BaseErrorListener() {
    override fun syntaxError(recognizer: Recognizer<*, *>, offendingSymbol: Any?, line: Int, charPositionInLine: Int, msg: String, e: RecognitionException) {
        val location = SourceLocation(
            source = source,
            line = line,
            column = charPositionInLine,
            length = 1,
        )
        reporter.reportError(location, msg)
    }
}
