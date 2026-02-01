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
        val symbolTable = SymbolTable()
        val typeResolver = TypeResolver(
            reporter = reporter,
            source = source,
            entityTable = declarationResult.entityTable,
            symbolTable = symbolTable,
        )
        declarationResult.entityTable.typedefs.forEach { (ctx, typedef) ->
            val symbol = typeResolver.resolveTypedef(typedef)
            symbolTable.addTypedef(ctx, symbol)
        }
        declarationResult.entityTable.variables.forEach { (ctx, variable) ->
            val symbol = typeResolver.resolveVariable(variable)
            symbolTable.addVariable(ctx, symbol)
        }
        declarationResult.entityTable.functions.forEach { (ctx, function) ->
            val symbol = typeResolver.resolveFunction(function)
            symbolTable.addFunction(ctx, symbol)
        }
        declarationResult.entityTable.structs.forEach { (ctx, struct) ->
            val symbol = typeResolver.resolveStruct(struct)
            symbolTable.addStruct(ctx, symbol)
        }
        declarationResult.entityTable.enums.forEach { (ctx, enum) ->
            val symbol = typeResolver.resolveEnum(enum)
            symbolTable.addEnum(ctx, symbol)
        }
        return TypeResolutionResult(
            sourceFile = declarationResult.sourceFile,
            entityTable = declarationResult.entityTable,
            rootScope = declarationResult.rootScope,
            parseTree = declarationResult.parseTree,
            symbolTable = symbolTable,
        )
    }
}
