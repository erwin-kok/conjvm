package org.erwinkok.conjvm.parser

import org.antlr.v4.runtime.BufferedTokenStream
import org.antlr.v4.runtime.Lexer
import org.antlr.v4.runtime.Token
import org.antlr.v4.runtime.TokenSource

open class TriviaAwareTokenStream(
    tokenSource: TokenSource,
    val channel: Int = Token.DEFAULT_CHANNEL,
) : BufferedTokenStream(tokenSource) {
    private val cache = mutableMapOf<Int, Token>()

    override fun adjustSeekIndex(i: Int): Int {
        return nextTokenOnChannel(i, channel)
    }

    override fun LB(k: Int): Token? {
        if (k == 0 || (p - k) < 0) {
            return null
        }

        var i = p
        var n = 1

        // find k good tokens looking backwards
        while (n <= k && i > 0) {
            // skip off-channel tokens
            i = previousTokenOnChannel(i - 1, channel)
            n++
        }
        if (i < 0) {
            return null
        }
        return createTriviaTokenAtIndex(i)
    }

    override fun LT(k: Int): Token? {
        lazyInit()
        if (k == 0) {
            return null
        }
        if (k < 0) {
            return LB(-k)
        }
        var i = p
        var n = 1 // we know tokens[p] is a good one

        // find k good tokens
        while (n < k) {
            // skip off-channel tokens, but make sure to not look past EOF
            if (sync(i + 1)) {
                i = nextTokenOnChannel(i + 1, channel)
            }
            n++
        }
        return createTriviaTokenAtIndex(i)
    }

    fun getNumberOfOnChannelTokens(): Int {
        var n = 0
        fill()
        for (i in tokens.indices) {
            val t = tokens[i]
            if (t.channel == channel) {
                n++
            }
            if (t.type == Token.EOF) {
                break
            }
        }
        return n
    }

    private fun createTriviaTokenAtIndex(index: Int): Token {
        lazyInit()
        if (index < 0 || index >= tokens.count()) {
            throw IndexOutOfBoundsException("$index not in 0..${(tokens.count() - 1)}")
        }
        val tt = cache[index]
        if (tt != null) {
            return tt
        }

        val currentToken = tokens[index]
        require(currentToken.tokenIndex == index)
        val leading = getLeadingTriviaTokens(index)
        val trailing = getTrailingTriviaTokens(index)
        val triviaToken = TriviaAwareToken(currentToken, leading, trailing)
        cache[index] = triviaToken
        return triviaToken
    }

    private fun getLeadingTriviaTokens(tokenIndex: Int): List<Token> {
        if (tokenIndex == 0) {
            // obviously no tokens can appear before the first token
            return emptyList()
        }
        val trivias = mutableListOf<Token>()
        val currentToken = tokens[tokenIndex]
        val lineTrivias = mutableListOf<Token>()
        var currentLine = currentToken.line
        for (i in tokenIndex - 1 downTo 0 step 1) {
            sync(i)
            val token = tokens[i]
            if (token.type == Token.EOF) {
                break
            } else if (token.channel == Lexer.DEFAULT_TOKEN_CHANNEL) {
                break
            } else if (token.line != currentLine) {
                trivias.addAll(lineTrivias)
                lineTrivias.clear()
                currentLine = token.line
            }
            lineTrivias.add(token)
        }
        if (lineTrivias.isNotEmpty() && currentLine == currentToken.line) {
            // trivias.AddRange(lineTrivias)
        }
        if (trivias.isEmpty()) {
            return emptyList()
        }
        trivias.reverse()
        return trivias
    }

    private fun getTrailingTriviaTokens(tokenIndex: Int): List<Token> {
        sync(tokenIndex + 1)
        val trivias = mutableListOf<Token>()
        val currentToken = tokens[tokenIndex]
        for (i in tokenIndex + 1 until size()) {
            val token = tokens[i]
            if (token.type == Token.EOF) {
                break
            } else if (token.channel == Lexer.DEFAULT_TOKEN_CHANNEL) {
                break
            } else if (token.line != currentToken.line) {
                break
            }
            trivias.add(token)
            sync(i + 1)
        }
        return trivias
    }
}
