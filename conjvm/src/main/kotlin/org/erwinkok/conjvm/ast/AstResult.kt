package org.erwinkok.conjvm.ast

import org.erwinkok.conjvm.ast.statements.Statement
import org.erwinkok.conjvm.parser.SourceFile
import org.erwinkok.conjvm.types.SymbolTable

data class AstResult(
    val sourceFile: SourceFile,
    val astStatement: Statement,
    val symbolTable: SymbolTable,
)
