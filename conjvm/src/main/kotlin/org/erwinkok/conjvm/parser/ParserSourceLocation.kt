package org.erwinkok.conjvm.parser

import org.antlr.v4.runtime.Token

data class ParserSourceLocation(
    val sourceName: String?,
    val index: Int,
    val line: Int,
    val column: Int,
) {
    constructor(token: Token) : this(token.inputStream?.sourceName, token.startIndex, token.line, token.charPositionInLine + 1)
}
