package org.erwinkok.conjvm.translation

import org.erwinkok.conjvm.ast.types.Field
import org.erwinkok.conjvm.ast.types.QualType
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

class TranslationTest {
    @Test
    @Disabled
    fun translationTest() {
        val classLoader = TranslationTest::class.java.classLoader
        val inputStream = classLoader.getResourceAsStream("input.c")
        requireNotNull(inputStream)

        val symbolTable = SymbolTable()
        val source = SourceFile.ofString("input.c", "void func(void) { x = ; }") // SourceFile.ofStream("input.c", inputStream)
        val compilationUnit = Parser.parseSource(source, symbolTable)
        requireNotNull(compilationUnit)

        val typeVisitor = TypeVisitor(symbolTable, ErrorReporter())
        typeVisitor.globalScope.defineFunction("m68ki_exception_1010", TypeSystem.voidType, emptySet())
        typeVisitor.globalScope.defineFunction("m68ki_exception_1111", TypeSystem.voidType, emptySet())
        typeVisitor.globalScope.defineVariable(
            "m68ki_cpu",
            QualType(
                Type.Struct(
                    "m68ki_cpu",
                    listOf(
                        Field("cpu_type", QualType(Type.Int(signed = true))),
                        Field("n_flag", QualType(Type.Int(signed = true))),
                        Field("x_flag", QualType(Type.Int(signed = true))),
                        Field("v_flag", QualType(Type.Int(signed = true))),
                        Field("c_flag", QualType(Type.Int(signed = true))),
                        Field("not_z_flag", QualType(Type.Int(signed = true))),
                        Field("dar", QualType(Type.Int(signed = true))),
                        Field("ir", QualType(Type.Int(signed = true))),
                    ),
                ),
                emptySet(),
            ),
            emptySet(),
        )
        typeVisitor.visit(compilationUnit)

        var translatedCompilationUnit = Translator.translateStatement(compilationUnit, ConvertForToWhileTranslation())
        translatedCompilationUnit = Translator.translateStatement(translatedCompilationUnit, AssignmentTranslation())

        val translationVisitor = TacTranslation()
        translationVisitor.translateStatement(translatedCompilationUnit)

        val referenceStream = classLoader.getResourceAsStream("reference.c")
        requireNotNull(referenceStream)
        val expected = String(referenceStream.readBytes())

        val writer = StringWriter()
        val tacCodeWriter = TacCodeWriter(writer)
        tacCodeWriter.printFunctions(translationVisitor.functions)
        val actual = writer.toString()

        assertEquals(expected, actual)
    }
}
