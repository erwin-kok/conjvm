package org.erwinkok.conjvm.types

import org.erwinkok.conjvm.compiler.CompilerPhase
import org.erwinkok.conjvm.declarations.DeclarationResult
import org.erwinkok.conjvm.declarations.Scope
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.SourceFile

class TypeResolution(
    override val reporter: ErrorReporter,
    override val source: SourceFile,
) : CompilerPhase {
    fun analyze(declarationResult: DeclarationResult): TypeResolutionResult {
        val typeResolver = TypeResolver(
            reporter = reporter,
            source = source,
            entityTable = declarationResult.entityTable,
            rootScope = declarationResult.rootScope,
        )
        resolveTypesInScope(declarationResult.rootScope, typeResolver)
        return TypeResolutionResult(
            sourceFile = declarationResult.sourceFile,
            rootScope = declarationResult.rootScope,
            entityTable = declarationResult.entityTable,
            parseTree = declarationResult.parseTree,
        )
    }

    private fun resolveTypesInScope(scope: Scope, typeResolver: TypeResolver) {
        scope.localEnums.forEach { entity ->
            typeResolver.resolveEnum(entity)
            scope.registerEnumConstants(entity)
        }
        scope.localStructs.forEach { entity ->
            typeResolver.resolveStruct(entity)
        }
        scope.localTypedefs.forEach { entity ->
            typeResolver.resolveTypedef(entity)
        }
        scope.localVariables.forEach { entity ->
            typeResolver.resolveVariable(entity)
        }
        scope.localFunctions.forEach { entity ->
            typeResolver.resolveFunction(entity)
        }
        scope.children.forEach { child ->
            resolveTypesInScope(child, typeResolver)
        }
    }
}
