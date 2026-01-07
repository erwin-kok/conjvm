package org.erwinkok.conjvm.parser

import java.io.Writer

class ErrorReporter {
    private val diagnosticList = mutableListOf<Diagnostic>()

    val hasWarnings: Boolean
        get() = diagnosticList.any { it.severity == Severity.WARNING }

    val hasErrors: Boolean
        get() = diagnosticList.any { it.severity == Severity.ERROR }

    val warnings: List<Diagnostic>
        get() = diagnosticList.filter { it.severity == Severity.WARNING }

    val errors: List<Diagnostic>
        get() = diagnosticList.filter { it.severity == Severity.ERROR }

    fun reportWarning(location: SourceLocation, msg: String) {
        diagnosticList += Diagnostic(
            severity = Severity.WARNING,
            location = location,
            message = msg,
        )
    }

    fun reportError(location: SourceLocation, msg: String) {
        diagnosticList += Diagnostic(
            severity = Severity.ERROR,
            location = location,
            message = msg,
        )
    }

    fun writeDiagnostics(writer: Writer, list: List<Diagnostic> = diagnosticList) {
        list.forEach {
            writer.appendLine(render(it))
        }
    }

    fun printDiagnostics(list: List<Diagnostic> = diagnosticList) {
        list.forEach {
            println(render(it))
        }
    }

    override fun toString(): String {
        return "#${warnings.size} warnings, #${errors.size} errors"
    }

    private fun render(d: Diagnostic): String {
        val lineText = d.location.source.line(d.location.line)
        val underline = buildString {
            repeat(d.location.column) { append(' ') }
            repeat(maxOf(1, d.location.length)) { append("^") }
        }
        return """
        |${d.location.source.name}:${d.location.line}:${d.location.column + 1}: ${d.severity.name.lowercase()}
        |$lineText
        |$underline
        |${d.message}
        """.trimMargin()
    }
}
