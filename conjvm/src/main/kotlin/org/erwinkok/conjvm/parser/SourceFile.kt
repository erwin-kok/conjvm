package org.erwinkok.conjvm.parser

import java.io.BufferedInputStream
import java.io.InputStream
import java.util.zip.GZIPInputStream

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

    override fun toString(): String {
        return "source: $name"
    }

    companion object {
        fun ofStream(name: String, inputStream: InputStream): SourceFile {
            val buffered = if (inputStream.markSupported()) {
                inputStream
            } else {
                BufferedInputStream(inputStream)
            }
            buffered.mark(2)
            val isGzip = buffered.read() == 0x1f && buffered.read() == 0x8b
            buffered.reset()
            val content = if (isGzip) {
                GZIPInputStream(buffered).readBytes()
            } else {
                buffered.readBytes()
            }
            return SourceFile(name, content.toString(Charsets.UTF_8))
        }

        fun ofString(name: String, content: String): SourceFile {
            return SourceFile(name, content)
        }
    }
}
