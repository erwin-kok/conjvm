package org.erwinkok.conjvm.types

import org.antlr.v4.runtime.ParserRuleContext
import org.erwinkok.conjvm.declarations.EntityTable
import org.erwinkok.conjvm.declarations.Scope
import org.erwinkok.conjvm.parser.SourceFile

data class TypeResolutionResult(
    val sourceFile: SourceFile,
    val entityTable: EntityTable,
    val rootScope: Scope,
    val parseTree: ParserRuleContext,
    val symbolTable: SymbolTable,
)
