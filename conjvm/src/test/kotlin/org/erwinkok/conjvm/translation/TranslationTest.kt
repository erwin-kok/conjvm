package org.erwinkok.conjvm.translation

import org.erwinkok.conjvm.ast.TypeContext
import org.erwinkok.conjvm.ast.TypeVisitor
import org.erwinkok.conjvm.parser.Parser
import org.erwinkok.conjvm.tac.TacCodeWriter
import org.erwinkok.conjvm.tac.TacTranslation
import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Test
import java.io.StringWriter
import java.util.zip.GZIPInputStream

class TranslationTest {
    @Test
    fun translationTest() {
        val classLoader = TranslationTest::class.java.classLoader
        val inputStream = classLoader.getResourceAsStream("input.c.gz")
        requireNotNull(inputStream)
        GZIPInputStream(inputStream).use { inputGzip ->
            val compilationUnit = Parser.parseStream(inputGzip)

            TypeVisitor().visit(compilationUnit, TypeContext())

            var translatedCompilationUnit = Translator.translateStatement(compilationUnit, ConvertForToWhileTranslation())
            translatedCompilationUnit = Translator.translateStatement(translatedCompilationUnit, AssignmentTranslation())

            val translationVisitor = TacTranslation()
            translationVisitor.translateStatement(translatedCompilationUnit)

            val referenceStream = classLoader.getResourceAsStream("reference.c.gz")
            requireNotNull(referenceStream)
            GZIPInputStream(referenceStream).use { gzip ->
                val expected = String(gzip.readBytes())

                val writer = StringWriter()
                val tacCodeWriter = TacCodeWriter(writer)
                tacCodeWriter.printFunctions(translationVisitor.functions)
                val actual = writer.toString()

                assertEquals(expected, actual)
            }
        }
    }
}
