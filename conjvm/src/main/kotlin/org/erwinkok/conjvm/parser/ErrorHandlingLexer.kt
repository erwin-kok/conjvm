package org.erwinkok.conjvm.parser

import org.antlr.v4.runtime.CharStream
import org.antlr.v4.runtime.LexerNoViableAltException
import org.antlr.v4.runtime.misc.Interval
import org.erwinkok.conjvm.CLexer

class ErrorHandlingLexer(
    private val errorReporter: ErrorReporter,
    charStream: CharStream,
) : CLexer(charStream) {
    override fun notifyListeners(e: LexerNoViableAltException) {
        val tokenText = _input.getText(Interval.of(_tokenStartCharIndex, _input.index()))
        val sourceLocation = ParserSourceLocation(sourceName, _tokenStartCharIndex, _tokenStartLine, _tokenStartCharPositionInLine + 1)
        errorReporter.reportWarning(sourceLocation, "unexpected character: '${getErrorDisplay(tokenText)}'")
    }
}
