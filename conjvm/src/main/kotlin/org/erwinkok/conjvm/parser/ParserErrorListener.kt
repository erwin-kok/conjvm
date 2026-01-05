package org.erwinkok.conjvm.parser

import org.antlr.v4.runtime.BaseErrorListener
import org.antlr.v4.runtime.RecognitionException
import org.antlr.v4.runtime.Recognizer
import org.antlr.v4.runtime.Token

class ParserErrorListener(
    private val reporter: ErrorReporter,
    private val source: SourceFile,
) : BaseErrorListener() {
    override fun syntaxError(recognizer: Recognizer<*, *>, offendingSymbol: Any?, line: Int, charPositionInLine: Int, msg: String, e: RecognitionException) {
        val token = offendingSymbol as? Token
        val length = if (token != null && token.stopIndex >= token.startIndex) {
            token.stopIndex - token.startIndex + 1
        } else {
            1
        }
        val location = SourceLocation(
            source = source,
            line = line,
            column = charPositionInLine,
            length = length,
        )
        reporter.reportError(location, msg)
    }
}
