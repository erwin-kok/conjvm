package org.erwinkok.conjvm.translation

import org.erwinkok.conjvm.ast.types.Field
import org.erwinkok.conjvm.ast.types.QualType
import org.erwinkok.conjvm.ast.types.Scope
import org.erwinkok.conjvm.ast.types.SymbolTable
import org.erwinkok.conjvm.ast.types.Type
import org.erwinkok.conjvm.ast.types.TypeSystem
import org.erwinkok.conjvm.ast.types.TypeVisitor
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.Parser
import org.erwinkok.conjvm.parser.SourceFile
import org.erwinkok.conjvm.tac.TacCodeWriter
import org.erwinkok.conjvm.tac.TacTranslation
import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Disabled
import org.junit.jupiter.api.Test
import java.io.StringWriter
import java.util.UUID

class TranslationTest {
    @Test
    fun translationTest() {
        val symbolTable = SymbolTable()
        val source = SourceFile.ofString("input.c", "void func(void) { int x = 4; }")
        val errorReporter = ErrorReporter()

        val compilationUnit = Parser(errorReporter).parseCompilationUnit(source)
        errorReporter.assertNoDiagnostics()
        requireNotNull(compilationUnit)

        val typeVisitor = TypeVisitor(symbolTable, errorReporter)
        typeVisitor.visit(compilationUnit)
        errorReporter.assertNoDiagnostics()

        val translatedCompilationUnit = AstTranslator(errorReporter).translate(compilationUnit, listOf(::ConvertForToWhileTranslation, ::AssignmentTranslation))
        errorReporter.assertNoDiagnostics()
        requireNotNull(translatedCompilationUnit)

        val translationVisitor = TacTranslation(errorReporter)
        translationVisitor.translateStatement(translatedCompilationUnit)
        errorReporter.assertNoDiagnostics()

        val writer = StringWriter()
        val tacCodeWriter = TacCodeWriter(writer)
        tacCodeWriter.printInstructions(translationVisitor.functions)
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
        val statement = Parser(reporter).parseCompilationUnit(source)
        reporter.assertNoDiagnostics()
    }

    @Test
    @Disabled
    fun translationTest3() {
        val symbolTable = SymbolTable()
        val errorReporter = ErrorReporter()
        val parser = Parser(errorReporter)
        val setup = readResource("setup.c")
        val x = parser.parseCompilationUnit(setup)
        errorReporter.assertNoDiagnostics()

        val source = readResource("input.c")
        val compilationUnit = parser.parseCompilationUnit(source)
        errorReporter.assertNoDiagnostics()
        requireNotNull(compilationUnit)

        val typeVisitor = TypeVisitor(symbolTable, errorReporter)
        prepareGlobalScope(typeVisitor.globalScope)
        typeVisitor.visit(compilationUnit)
        errorReporter.assertNoDiagnostics()

        val translatedCompilationUnit = AstTranslator(errorReporter).translate(compilationUnit, listOf(::ConvertForToWhileTranslation, ::AssignmentTranslation))
        errorReporter.assertNoDiagnostics()
        requireNotNull(translatedCompilationUnit)

        val translationVisitor = TacTranslation(errorReporter)
        translationVisitor.translateStatement(translatedCompilationUnit)
        errorReporter.assertNoDiagnostics()

        val expected = readResource("reference.c.gz")

        val writer = StringWriter()
        val tacCodeWriter = TacCodeWriter(writer)
        tacCodeWriter.printInstructions(translationVisitor.functions)
        val actual = writer.toString()

        assertEquals(expected.text, actual)
    }

    private fun prepareGlobalScope(scope: Scope) {
        scope.defineFunction("m68ki_exception_1010", TypeSystem.voidType, emptySet())
        scope.defineFunction("m68ki_exception_1111", TypeSystem.voidType, emptySet())
        scope.defineFunction("m68ki_write_8_fc", TypeSystem.voidType, emptySet())
        scope.defineFunction("m68ki_write_16_fc", TypeSystem.voidType, emptySet())
        scope.defineFunction("m68ki_write_32_fc", TypeSystem.voidType, emptySet())
        scope.defineFunction("m68040_fpu_op0", TypeSystem.voidType, emptySet())
        scope.defineFunction("m68040_fpu_op1", TypeSystem.voidType, emptySet())

        scope.defineVariable(
            "m68ki_cpu",
            QualType(
                Type.Struct(
                    UUID.randomUUID(),
                    "m68ki_cpu",
                    listOf(
                        Field("cpu_type", QualType(Type.Int(signed = false))),
                        Field("dar", QualType(Type.Array(QualType(Type.Int(signed = false)), 16))),
                        Field("ir", QualType(Type.Int(signed = false))),
                        Field("n_flag", QualType(Type.Int(signed = false))),
                        Field("x_flag", QualType(Type.Int(signed = false))),
                        Field("v_flag", QualType(Type.Int(signed = false))),
                        Field("c_flag", QualType(Type.Int(signed = false))),
                        Field("not_z_flag", QualType(Type.Int(signed = false))),
                    ),
                ),
                emptySet(),
            ),
            emptySet(),
        )
    }
}
