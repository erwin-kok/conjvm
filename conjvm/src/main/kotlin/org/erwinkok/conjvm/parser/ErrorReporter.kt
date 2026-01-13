package org.erwinkok.conjvm.parser

import java.io.Writer

class ErrorReporter {
    private val diagnosticList = mutableListOf<Diagnostic>()

    val hasWarnings: Boolean
        get() = diagnosticList.any { it.severity == Severity.WARNING }

    val hasErrors: Boolean
        get() = diagnosticList.any { it.severity == Severity.ERROR || it.severity == Severity.EXCEPTION }

    val warnings: List<Diagnostic>
        get() = diagnosticList.filter { it.severity == Severity.WARNING }

    val errors: List<Diagnostic>
        get() = diagnosticList.filter { it.severity == Severity.ERROR || it.severity == Severity.EXCEPTION }

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

    fun reportException(location: SourceLocation, exception: Exception) {
        diagnosticList += Diagnostic(
            severity = Severity.EXCEPTION,
            location = location,
            message = "exception '${exception::class.simpleName}' occurred: ${exception.message ?: "<no message>"}",
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
        val sb = StringBuilder()
        val location = d.location
        sb.append("${location.source.name}:")
        if (location.line > 0) {
            sb.append("${location.line}:")
        } else {
            sb.append(":")
        }
        if (location.column > 0) {
            sb.append("${location.column + 1}: ")
        } else {
            sb.append(": ")
        }
        sb.appendLine(d.severity.name.lowercase())
        if (location.line > 0) {
            val lineText = location.source.line(location.line)
            sb.appendLine(lineText)
        }
        if (location.column > 0 && location.length > 0) {
            val underline = buildString {
                repeat(location.column) { append(' ') }
                repeat(maxOf(1, location.length)) { append("^") }
            }
            sb.appendLine(underline)
        }
        sb.appendLine(d.message)
        return sb.toString()
    }
}
