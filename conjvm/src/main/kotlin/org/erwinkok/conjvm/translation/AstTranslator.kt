package org.erwinkok.conjvm.translation

import org.erwinkok.conjvm.ast.statements.Statement
import org.erwinkok.conjvm.parser.ErrorReporter

typealias TranslationStep = (reporter: ErrorReporter) -> TranslationVisitor

class AstTranslator(val reporter: ErrorReporter) {
    inline fun <reified T : Statement> translate(compilationUnit: T, steps: List<TranslationStep>): T? {
        var translatedCompilationUnit: T? = null
        for (step in steps) {
            translatedCompilationUnit = translateBlock(compilationUnit, step)
        }
        return translatedCompilationUnit
    }

    inline fun <reified T : Statement> translateBlock(statement: T, translation: TranslationStep): T {
        val (ts, te) = translation(reporter).translate(statement)
        require(te == null)
        require(ts.size == 1)
        val translatedStatement = ts.first()
        require(translatedStatement is T)
        return translatedStatement
    }
}
