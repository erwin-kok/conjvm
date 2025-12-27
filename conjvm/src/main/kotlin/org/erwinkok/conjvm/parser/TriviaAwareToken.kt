package org.erwinkok.conjvm.parser

import org.antlr.v4.runtime.Token

data class TriviaAwareToken(
    val token: Token,
    val leading: List<Token>,
    val trailing: List<Token>,
) : Token by token
