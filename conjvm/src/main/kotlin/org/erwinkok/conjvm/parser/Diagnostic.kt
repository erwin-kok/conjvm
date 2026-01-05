package org.erwinkok.conjvm.parser

enum class Severity {
    WARNING,
    ERROR,
}

data class Diagnostic(
    val severity: Severity,
    val location: SourceLocation,
    val message: String,
)
