package org.erwinkok.conjvm.types

import org.erwinkok.conjvm.compiler.CompilerPhase
import org.erwinkok.conjvm.declarations.DeclarationResult
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.SourceFile

class TypeResolution(
    override val reporter: ErrorReporter,
    override val source: SourceFile,
) : CompilerPhase {
    fun analyze(declarationResult: DeclarationResult): TypeResolutionResult {
        return TypeResolutionResult(
            sourceFile = declarationResult.sourceFile,
            entityTable = declarationResult.entityTable,
            rootScope = declarationResult.rootScope,
            parseTree = declarationResult.parseTree,
            symbolTable = SymbolTable(),
        )
    }
}
