package org.erwinkok.conjvm.translation

import org.antlr.v4.runtime.misc.ParseCancellationException
import org.erwinkok.conjvm.ast.statements.BlockStatement
import org.erwinkok.conjvm.ast.statements.ExpressionStatement
import org.erwinkok.conjvm.ast.types.QualType
import org.erwinkok.conjvm.ast.types.SymbolTable
import org.erwinkok.conjvm.ast.types.Type
import org.erwinkok.conjvm.ast.types.TypeVisitor
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

fun QualType.debugString(): String {
    val q = qualifiers.sorted().joinToString(" ") { it.name.lowercase() }
    val base = when (val t = type) {
        is Type.Pointer -> "${t.pointee.debugString()}*"
        is Type.Array -> "${t.elementType.debugString()}[${t.size ?: ""}]"
        is Type.Function -> "fn(${t.parameters.joinToString(", ") { it.debugString() }}) -> ${t.returnType.debugString()}"
        else -> t.toString()
    }
    return if (q.isEmpty()) base else "$q $base"
}

fun parseBlock(inputText: String): QualType {
    val reporter = ErrorReporter()
    try {
        val source = SourceFile.ofString("<statement>", "{$inputText}")
        val symbolTable = SymbolTable()
        val statement = Parser(reporter, symbolTable).parseStatement(source)
        reporter.assertNoDiagnostics()
        require(statement is BlockStatement)
        val typeVisitor = TypeVisitor(symbolTable, reporter)
        typeVisitor.visit(statement)
        val last = statement.statements.lastOrNull()
        requireNotNull(last)
        require(last is ExpressionStatement)
        val expressionType = last.expression.expressionType
        requireNotNull(expressionType) { "expression type is not filled in '${last.expression::class.simpleName}'" }
        return expressionType.type.canonical
    } catch (_: ParseCancellationException) {
        reporter.assertNoDiagnostics()
        error("unable to parse statement")
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
    val symbolTable = SymbolTable()
    val parser = Parser(reporter, symbolTable)
    val inputSource = SourceFile.ofString("test", inputText)
    val statement = parser.parseStatement(inputSource)
    requireNotNull(statement)
    val translatedStatement = AstTranslator(reporter).translate(statement, translationVisitor)
    val expectedSource = SourceFile.ofString("expected", expectedText)
    val expectedStatement = parser.parseStatement(expectedSource)
    assertEquals(expectedStatement, translatedStatement)
    reporter.assertNoDiagnostics()
}
