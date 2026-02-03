package org.erwinkok.conjvm.ast

import org.erwinkok.conjvm.ast.statements.Statement
import org.erwinkok.conjvm.declarations.Scope
import org.erwinkok.conjvm.parser.SourceFile

data class AstResult(
    val sourceFile: SourceFile,
    val astStatement: Statement,
    val rootScope: Scope,
)
