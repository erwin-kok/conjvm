package org.erwinkok.conjvm.parser

enum class Severity {
    WARNING,
    ERROR,
}

data class Diagnostic(
    val severity: Severity,
    val message: String,
    val line: Int,
    val column: Int,
    val length: Int,
    val sourceName: String,
)
