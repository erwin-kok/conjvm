package org.erwinkok.conjvm.parser

import org.antlr.v4.runtime.CharStream
import org.antlr.v4.runtime.LexerNoViableAltException
import org.antlr.v4.runtime.misc.Interval
import org.erwinkok.conjvm.CLexer
import org.erwinkok.conjvm.ast.types.SymbolTable

class ErrorHandlingLexer(
    private val errorReporter: ErrorReporter,
    charStream: CharStream,
    symbolTable: SymbolTable,
) : CLexer(charStream, symbolTable) {
    override fun notifyListeners(e: LexerNoViableAltException) {
        val tokenText = _input.getText(Interval.of(_tokenStartCharIndex, _input.index()))
        val sourceLocation = ParserSourceLocation(sourceName, _tokenStartCharIndex, _tokenStartLine, _tokenStartCharPositionInLine + 1)
        errorReporter.reportWarning(sourceLocation, "unexpected character: '${getErrorDisplay(tokenText)}'")
    }
}
