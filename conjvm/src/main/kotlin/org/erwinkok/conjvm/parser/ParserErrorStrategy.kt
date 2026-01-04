package org.erwinkok.conjvm.parser

import org.antlr.v4.runtime.DefaultErrorStrategy
import org.antlr.v4.runtime.InputMismatchException
import org.antlr.v4.runtime.Parser
import org.antlr.v4.runtime.RecognitionException
import org.antlr.v4.runtime.Token
import org.antlr.v4.runtime.misc.ParseCancellationException

class ParserErrorStrategy : DefaultErrorStrategy() {
    override fun recover(recognizer: Parser, e: RecognitionException) {
        reportError(recognizer, e)
        throw ParseCancellationException(e)
    }

    override fun recoverInline(recognizer: Parser): Token {
        val e = InputMismatchException(recognizer)
        reportError(recognizer, e)
        throw ParseCancellationException(e)
    }

    override fun sync(recognizer: Parser) {
        // Disable automatic recovery
    }
}
