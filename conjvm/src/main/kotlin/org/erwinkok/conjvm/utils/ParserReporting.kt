package org.erwinkok.conjvm.utils

import org.antlr.v4.runtime.ParserRuleContext
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.SourceFile
import org.erwinkok.conjvm.parser.SourceFileLocation
import org.erwinkok.conjvm.parser.SourceLocation

interface ParserReporting {
    val reporter: ErrorReporter
    val source: SourceFile

    val ParserRuleContext.location: SourceLocation
        get() {
            return SourceFileLocation(
                source = source,
                line = this.start.line,
                column = this.start.charPositionInLine,
                length = this.start.text?.length ?: 1,
            )
        }
}
