package org.erwinkok.conjvm.declarations

import org.erwinkok.conjvm.CBaseListener
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.SourceFile
import org.erwinkok.conjvm.utils.ParserReporting

class DeclarationListener(
    override val reporter: ErrorReporter,
    override val source: SourceFile,
    private val scopeManager: ScopeManager,
) : CBaseListener(),
    ParserReporting {
    private val declarationParser = DeclarationParser(reporter, source)

    fun isTypedefName(s: String): Boolean {
        return "uint" == s ||
            "uint8" == s ||
            "uint16" == s ||
            "uint32" == s ||
            "uint64" == s ||
            "sint" == s ||
            "sint8" == s ||
            "sint16" == s ||
            "sint32" == s ||
            "sint64" == s ||
            "int" == s ||
            "int8" == s ||
            "int16" == s ||
            "int32" == s ||
            "int64" == s ||
            "m68ki_bitfield_t" == s
    }
}
