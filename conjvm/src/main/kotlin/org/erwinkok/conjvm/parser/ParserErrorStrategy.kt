package org.erwinkok.conjvm.parser

import org.antlr.v4.runtime.DefaultErrorStrategy
import org.antlr.v4.runtime.InputMismatchException
import org.antlr.v4.runtime.NoViableAltException
import org.antlr.v4.runtime.Parser
import org.antlr.v4.runtime.RecognitionException
import org.antlr.v4.runtime.Token
import org.antlr.v4.runtime.misc.ParseCancellationException
import org.erwinkok.conjvm.CParser

class ParserErrorStrategy(
    private val errorReporter: ErrorReporter,
) : DefaultErrorStrategy() {
    override fun recover(recognizer: Parser, e: RecognitionException) {
        val token = e.offendingToken
        val message = if (token == null) {
            "No parse token found."
        } else if (e is InputMismatchException) {
            "Error[${token.line}:${token.startIndex}]: unexpected token [${getTokenErrorDisplay(token)}] was expecting one of [${e.getExpectedTokens().toString(recognizer.vocabulary)}]."
        } else if (e is NoViableAltException) {
            if (token.type == CParser.EOF) {
                "Error: unexpected end of script."
            } else {
                "Error[${token.line}: ${token.startIndex}]: invalid sequence of tokens near [${getTokenErrorDisplay(token)}]."
            }
        } else {
            "Error[${token.line}: ${token.startIndex}]: unexpected token near [${getTokenErrorDisplay(token)}]."
        }
        val location = ParserSourceLocation(token)
        errorReporter.reportError(location, message)
        throw ParseCancellationException(e)
    }

    override fun recoverInline(recognizer: Parser): Token {
        val token = recognizer.currentToken
        val message = "Error[${token.line}: ${token.startIndex}]: unexpected token [${getTokenErrorDisplay(token)}] was expecting one of [${recognizer.expectedTokens.toString(recognizer.vocabulary)}]."
        val location = ParserSourceLocation(token)
        errorReporter.reportError(location, message)
        return token
    }

    override fun sync(recognizer: Parser) {
        //
    }
}
