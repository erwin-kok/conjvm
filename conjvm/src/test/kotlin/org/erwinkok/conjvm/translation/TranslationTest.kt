package org.erwinkok.conjvm.translation

import org.erwinkok.conjvm.parser.Parser
import org.erwinkok.conjvm.tac.TacCodeWriter
import org.erwinkok.conjvm.tac.TacTranslation
import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Test
import java.io.StringWriter

class TranslationTest {
    @Test
    fun translationTest() {
        val classLoader = TranslationTest::class.java.classLoader
        val inputStream = classLoader.getResourceAsStream("input.c")
        requireNotNull(inputStream)

        val compilationUnit = Parser.parseStream(inputStream)

        var translatedCompilationUnit = Translator.translateStatement(compilationUnit, ConvertForToWhileTranslation())
        translatedCompilationUnit = Translator.translateStatement(translatedCompilationUnit, AssignmentTranslation())

        val translationVisitor = TacTranslation()
        translationVisitor.translateStatement(translatedCompilationUnit)

        val referenceStream = classLoader.getResourceAsStream("reference.c")
        requireNotNull(referenceStream)
        val reference = String(referenceStream.readAllBytes())

        val writer = StringWriter()
        val tacCodeWriter = TacCodeWriter(writer)
        tacCodeWriter.printFunctions(translationVisitor.functions)

        val actual = writer.toString()

        assertEquals(reference, actual)
    }
}
