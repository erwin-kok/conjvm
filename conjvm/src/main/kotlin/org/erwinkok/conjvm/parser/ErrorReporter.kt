package org.erwinkok.conjvm.parser

import org.erwinkok.conjvm.ast.SourceLocation
import java.io.File

class ErrorReporter {
    companion object {
        private const val TabSize = 4
    }

    enum class ErrorSeverity {
        Warning,
        Error,
        FatalError,
    }

    fun reportSyntaxError(location: ParserSourceLocation, message: String) {
        report(message, location, ErrorSeverity.FatalError)
    }

    fun reportError(location: ParserSourceLocation, message: String) {
        report(message, location, ErrorSeverity.Error)
    }

    fun reportWarning(location: ParserSourceLocation, message: String) {
        report(message, location, ErrorSeverity.Warning)
    }

    fun reportWarning(location: SourceLocation, message: String) {
        writeMessage(message)
    }

    fun reportError(location: SourceLocation, message: String) {
        writeMessage(message)
    }

    private fun report(message: String, loc: ParserSourceLocation, severity: ErrorSeverity) {
        val line = loc.line
        val path = loc.sourceName
        val codeLine = if (line > 0) {
            try {
                File(path).readLines().drop(line - 1).firstOrNull()
            } catch (_: Exception) {
                null
            }
        } else {
            null
        }
        writeMessage(formatErrorMessage(message, severity, path, line, loc.column, codeLine))
    }

    private fun formatErrorMessage(message: String, severity: ErrorSeverity, file: String?, line: Int, column: Int, lineSource: String?): String {
        val sb = StringBuilder()
        if (file != null) {
            sb.append(file)
        } else {
            sb.append("unknown")
        }
        sb.append(':')
        if (file != null) {
            sb.append(line)
        } else {
            sb.append(0)
        }
        sb.append(": ")

        sb.append(severity)
        sb.append(": ")

        sb.append(message)
        sb.appendLine()
        if (lineSource != null) {
            var target = ""
            var position = column
            for (c in lineSource) {
                if ((c == '\r') || (c == '\n')) {
                    break
                } else if (c == '\t') {
                    repeat(TabSize) {
                        target += " "
                    }
                    position += TabSize - 1 // The '\t' itself was already counted
                } else {
                    target += c
                }
            }
            sb.append(target)
            sb.appendLine()
            if (column > 0) {
                repeat(position - 1) {
                    sb.append('-')
                }
                sb.append('^')
                sb.appendLine()
            }
        }
        return sb.toString()
    }

    private fun writeMessage(errorMessage: String) {
        println(errorMessage)
    }
}
