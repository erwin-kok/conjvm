package org.erwinkok.conjvm.ast

data class SourceLocation(
    val startLine: Int,
    val startColumn: Int,
    val endLine: Int,
    val endColumn: Int,
)
