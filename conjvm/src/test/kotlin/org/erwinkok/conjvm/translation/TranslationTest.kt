package org.erwinkok.conjvm.translation

import org.erwinkok.conjvm.compiler.Compiler
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.Parser
import org.erwinkok.conjvm.parser.SourceFile
import org.erwinkok.conjvm.tac.TacCodeWriter
import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Disabled
import org.junit.jupiter.api.Test
import java.io.StringWriter

class TranslationTest {
    @Test
    fun translationTest() {
        val source = SourceFile.ofString("input.c", "void func(void) { int x = 4; }")
        val reporter = ErrorReporter()
        val functions = Compiler(reporter).compile(listOf(source))
        reporter.assertNoDiagnostics()
        requireNotNull(functions)
        val writer = StringWriter()
        val tacCodeWriter = TacCodeWriter(writer)
        tacCodeWriter.printInstructions(functions)
        val actual = writer.toString()

        assertEquals(
            """void func(void)
            |{
            |    StoreVar(x) = 4
            |}

            """.trimMargin(),
            actual,
        )
    }

    @Test
    @Disabled
    fun translationTest2() {
        val reporter = ErrorReporter()
        val source = SourceFile.ofString(
            "<statement>",
            """
            |typedef unsigned int A, B;
            |A x = 4;
            |int y = (x) & 0xf0;
            """.trimMargin(),
        )
        val statement = Compiler(reporter).compile(listOf(source))
        reporter.assertNoDiagnostics()
    }

    @Test
    @Disabled
    fun translationTest3() {
        val reporter = ErrorReporter()
        val source = readResource("input.c.gz")
        val parser = Parser(reporter, source)

        val functions = Compiler(reporter).compile(listOf(source))
        reporter.assertNoDiagnostics()
        requireNotNull(functions)

        val expected = readResource("reference.c.gz")

        val writer = StringWriter()
        val tacCodeWriter = TacCodeWriter(writer)
        tacCodeWriter.printInstructions(functions)
        val actual = writer.toString()

        assertEquals(expected.text, actual)
    }
}
