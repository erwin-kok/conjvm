package org.erwinkok.conjvm.parser

class DiagnosticRenderer(
    private val source: SourceFile,
) {
    fun render(d: Diagnostic): String {
        val lineText = source.line(d.line)
        val underline = buildString {
            repeat(d.column) { append(' ') }
            repeat(maxOf(1, d.length)) { append("^") }
        }
        return """
        ${d.sourceName}:${d.line}:${d.column + 1}: ${d.severity.name.lowercase()}
        $lineText
        $underline
        ${d.message}
        """.trimIndent()
    }
}
