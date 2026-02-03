package org.erwinkok.conjvm.compiler

import org.erwinkok.conjvm.ast.AstBuilder
import org.erwinkok.conjvm.ast.AstConstruction
import org.erwinkok.conjvm.ast.statements.Statement
import org.erwinkok.conjvm.linking.Linker
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.Parser
import org.erwinkok.conjvm.parser.SourceFile
import org.erwinkok.conjvm.tac.TacTranslation
import org.erwinkok.conjvm.tac.instructions.TacFunctionDefinition
import org.erwinkok.conjvm.types.TypeResolution

class Compiler(
    private val reporter: ErrorReporter,
) {
    fun compile(sourceFiles: List<SourceFile>): Map<String, TacFunctionDefinition>? {
        val astResults = sourceFiles.map { sourceFile ->
            val declarationResult = Parser(reporter, sourceFile).parseCompilationUnit()
            if (declarationResult == null || reporter.hasErrors) {
                return null
            }
            val typeResolutionResult = TypeResolution(reporter, sourceFile).analyze(declarationResult)
            if (reporter.hasErrors) {
                return null
            }
            val astResult = AstConstruction(reporter, sourceFile).analyzeCompilationUnit(typeResolutionResult)
            if (reporter.hasErrors) {
                return null
            }
            astResult
        }
        val linkedProgram = Linker(reporter).link(astResults)
        if (reporter.hasErrors) {
            return null
        }

        // TODO: Take the variables and functions from the GlobalSymbolTable
        // For now: take the first ast directly from the linkedProgram
        val astResult = linkedProgram.units.first()
        val translationVisitor = TacTranslation(reporter)
        translationVisitor.translateStatement(astResult.astStatement)

        return translationVisitor.functions
    }

    fun compileStatement(statement: String): Statement? {
        val sourceFile = SourceFile.ofString("<statement>", statement)
        val declarationResult = Parser(reporter, sourceFile).parseStatement()
        if (declarationResult == null || reporter.hasErrors) {
            return null
        }
        val typeResolutionResult = TypeResolution(reporter, sourceFile).analyze(declarationResult)
        if (reporter.hasErrors) {
            return null
        }
        val astResult = AstConstruction(reporter, sourceFile).analyzeStatement(typeResolutionResult)
        return AstBuilder(reporter, sourceFile, typeResolutionResult).visit(declarationResult.parseTree).cast<Statement>()
    }
}
