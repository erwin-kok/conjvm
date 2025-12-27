package org.erwinkok.conjvm.translation

import org.erwinkok.conjvm.ast.statements.Statement

object Translator {
    inline fun <reified T : Statement> translateStatement(statement: T, translationVisitor: TranslationVisitor): T {
        val (ts, te) = translationVisitor.translate(statement)
        require(te == null)
        require(ts.size == 1)
        val translatedStatement = ts.first()
        require(translatedStatement is T)
        return translatedStatement
    }
}
