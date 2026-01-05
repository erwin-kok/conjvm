package org.erwinkok.conjvm.translation

import org.erwinkok.conjvm.ast.types.SymbolTable
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.Parser
import org.erwinkok.conjvm.parser.SourceFile
import org.junit.jupiter.api.Assertions.assertEquals

fun ErrorReporter.assertNoDiagnostics() {
    require(!hasWarnings) {
        "warnings: ${warnings.size}"
        printDiagnostics(warnings)
    }
    require(!hasErrors) {
        "errors: ${errors.size}"
        printDiagnostics(errors)
    }
}

fun readResource(name: String): SourceFile {
    val classLoader = TranslationTest::class.java.classLoader
    val inputStream = classLoader.getResourceAsStream(name)
    requireNotNull(inputStream)
    return SourceFile.ofStream(name, inputStream)
}

class NoOp(reporter: ErrorReporter) : BaseTranslationVisitor(reporter)

fun assertTranslatedAstEquals(inputText: String, expectedText: String, translationVisitor: List<TranslationStep> = listOf(::NoOp)) {
    val reporter = ErrorReporter()
    val parser = Parser(reporter)
    val inputSource = SourceFile.ofString("test", inputText)
    val statement = parser.parseBlock(inputSource, SymbolTable())
    requireNotNull(statement)
    val translatedStatement = AstTranslator(reporter).translate(statement, translationVisitor)
    val expectedSource = SourceFile.ofString("expected", expectedText)
    val expectedStatement = parser.parseBlock(expectedSource, SymbolTable())
    assertEquals(expectedStatement, translatedStatement)
}
