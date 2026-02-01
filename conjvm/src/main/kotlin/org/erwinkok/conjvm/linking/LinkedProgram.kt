package org.erwinkok.conjvm.linking

import org.erwinkok.conjvm.ast.AstResult

data class LinkedProgram(
    val units: List<AstResult>,
    val globalSymbolTable: GlobalSymbolTable,
)
