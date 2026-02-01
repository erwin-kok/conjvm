package org.erwinkok.conjvm.ast

import org.erwinkok.conjvm.ast.statements.CompilationUnitStatement
import org.erwinkok.conjvm.ast.statements.Statement
import org.erwinkok.conjvm.compiler.CompilerPhase
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.SourceFile
import org.erwinkok.conjvm.types.TypeResolutionResult

class AstConstruction(
    override val reporter: ErrorReporter,
    override val source: SourceFile,
) : CompilerPhase {
    fun analyzeCompilationUnit(typeResolutionResult: TypeResolutionResult): AstResult {
        val compilationUnit = AstBuilder(reporter, source, typeResolutionResult).visit(typeResolutionResult.parseTree).cast<CompilationUnitStatement>()
        return AstResult(
            sourceFile = typeResolutionResult.sourceFile,
            astStatement = compilationUnit,
            symbolTable = typeResolutionResult.symbolTable,
        )
    }

    fun analyzeStatement(typeResolutionResult: TypeResolutionResult): AstResult {
        val statement = AstBuilder(reporter, source, typeResolutionResult).visit(typeResolutionResult.parseTree).cast<Statement>()
        return AstResult(
            sourceFile = typeResolutionResult.sourceFile,
            astStatement = statement,
            symbolTable = typeResolutionResult.symbolTable,
        )
    }
}
