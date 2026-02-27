package org.erwinkok.conjvm.translation

import org.erwinkok.conjvm.compiler.Compiler
import org.erwinkok.conjvm.error.ErrorReporter
import org.erwinkok.conjvm.tac.TacCodeWriter
import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Test
import java.io.StringWriter

class VariableTest {
    @Test
    fun translationTest1() {
        val reporter = ErrorReporter()
        val instructions = Compiler(reporter).compileStatement("{ int a; a=3; a = a + 1; a; }")
        reporter.assertNoDiagnostics()
        requireNotNull(instructions)
        val writer = StringWriter()
        val tacCodeWriter = TacCodeWriter(writer)
        tacCodeWriter.printInstructions(instructions)
        val actual = writer.toString()
        assertEquals(
            """
            |    StoreVar(a) = 3
            |    t1 = LoadVar(a)
            |    t2 = t1 + 1
            |    StoreVar(a) = t2
            |    t3 = LoadVar(a)
            """.trimMargin(),
            actual,
        )
    }

    @Test
    fun translationTest2() {
        val reporter = ErrorReporter()
        val instructions = Compiler(reporter).compileStatement("{ int a=3; int z=5; a+z; }")
        reporter.assertNoDiagnostics()
        requireNotNull(instructions)
        val writer = StringWriter()
        val tacCodeWriter = TacCodeWriter(writer)
        tacCodeWriter.printInstructions(instructions)
        val actual = writer.toString()
        assertEquals(
            """
            |    StoreVar(a) = 3
            |    StoreVar(z) = 5
            |    t1 = LoadVar(a)
            |    t2 = LoadVar(z)
            |    t3 = t1 + t2
            """.trimMargin(),
            actual,
        )
    }
}
