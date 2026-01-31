package org.erwinkok.conjvm.compiler

import org.erwinkok.conjvm.ast.AstBuilder
import org.erwinkok.conjvm.ast.statements.CompilationUnitStatement
import org.erwinkok.conjvm.ast.statements.Statement
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.Parser
import org.erwinkok.conjvm.parser.SourceFile
import org.erwinkok.conjvm.tac.TacTranslation
import org.erwinkok.conjvm.tac.instructions.TacFunctionDefinition
import org.erwinkok.conjvm.types.SymbolTable
import org.erwinkok.conjvm.types.TypeVisitor

class Compiler(
    private val reporter: ErrorReporter,
) {
    fun compile(sourceFiles: List<SourceFile>): List<Map<String, TacFunctionDefinition>>? {
        val result = sourceFiles.map { sourceFile ->
            val declarationResult = Parser(reporter, sourceFile).parseCompilationUnit()
            if (declarationResult == null || reporter.hasErrors) {
                return null
            }
            val astBuilder = AstBuilder(reporter, sourceFile, declarationResult.entityTable)
            val compilationUnit = astBuilder.visit(declarationResult.parseTree).cast<CompilationUnitStatement>()
            if (reporter.hasErrors) {
                return null
            }
            val typeVisitor = TypeVisitor(SymbolTable(), reporter)
            typeVisitor.visit(compilationUnit)
            if (reporter.hasErrors) {
                return null
            }
            val translationVisitor = TacTranslation(reporter)
            translationVisitor.translateStatement(compilationUnit)

            translationVisitor.functions
        }
        return result
    }

    fun compileStatement(statement: String): Statement? {
        val sourceFile = SourceFile.ofString("<statement>", statement)
        val declarationResult = Parser(reporter, sourceFile).parseStatement()
        if (declarationResult == null || reporter.hasErrors) {
            return null
        }
        val astBuilder = AstBuilder(reporter, sourceFile, declarationResult.entityTable)
        return astBuilder.visit(declarationResult.parseTree).cast<Statement>()
    }
}
