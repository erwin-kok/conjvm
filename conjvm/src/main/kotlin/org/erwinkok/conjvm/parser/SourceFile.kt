package org.erwinkok.conjvm.parser

import java.io.InputStream

class SourceFile private constructor(
    val name: String,
    val text: String,
) {
    private val lines = text.lines()

    fun line(line: Int): String {
        return lines.getOrNull(line - 1) ?: ""
    }

    fun lineCount(): Int {
        return lines.size
    }

    companion object {
        fun ofStream(name: String, inputStream: InputStream): SourceFile {
            return SourceFile(name, String(inputStream.readAllBytes()))
        }

        fun ofString(name: String, content: String): SourceFile {
            return SourceFile(name, content)
        }
    }
}
