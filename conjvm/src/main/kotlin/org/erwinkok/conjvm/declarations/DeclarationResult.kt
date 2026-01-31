package org.erwinkok.conjvm.declarations

import org.antlr.v4.runtime.ParserRuleContext
import org.erwinkok.conjvm.parser.SourceFile

data class DeclarationResult(
    val sourceFile: SourceFile,
    val entityTable: EntityTable,
    val rootScope: Scope,
    val parseTree: ParserRuleContext,
)
