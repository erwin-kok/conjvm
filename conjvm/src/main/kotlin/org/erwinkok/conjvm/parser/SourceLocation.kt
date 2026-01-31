package org.erwinkok.conjvm.parser

interface SourceLocation {
    fun render(severity: Severity, message: String): String
}

data class SourceFileLocation(
    val source: SourceFile,
    val line: Int,
    val column: Int,
    val length: Int,
) : SourceLocation {
    override fun render(severity: Severity, message: String): String {
        val sb = StringBuilder()
        sb.append("${source.name}:")
        if (line > 0) {
            sb.append("$line:")
        } else {
            sb.append(":")
        }
        if (column > 0) {
            sb.append("${column + 1}: ")
        } else {
            sb.append(": ")
        }
        sb.appendLine(severity.name.lowercase())
        if (line > 0) {
            val lineText = source.line(line)
            sb.appendLine(lineText)
        }
        if (column > 0 && length > 0) {
            val underline = buildString {
                repeat(column) { append(' ') }
                repeat(maxOf(1, length)) { append("^") }
            }
            sb.appendLine(underline)
        }
        sb.appendLine(message)
        return sb.toString()
    }

    override fun toString(): String {
        return "($source, line: $line, column: $column)"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is SourceFileLocation) {
            return false
        }
        // SourceLocations always match
        return true
    }

    override fun hashCode(): Int {
        return javaClass.hashCode()
    }
}

object UnknownLocation : SourceLocation {
    override fun render(severity: Severity, message: String): String {
        return "${severity.name.lowercase()}: $message"
    }

    override fun toString(): String {
        return "(unknown location)"
    }
}
