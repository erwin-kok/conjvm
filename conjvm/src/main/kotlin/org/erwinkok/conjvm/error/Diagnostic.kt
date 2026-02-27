package org.erwinkok.conjvm.error

import org.erwinkok.conjvm.parser.SourceLocation

enum class Severity {
    WARNING,
    ERROR,
    EXCEPTION,
}

data class Diagnostic(
    val severity: Severity,
    val location: SourceLocation,
    val message: String,
)
