package org.erwinkok.conjvm.parser

data class SourceLocation(
    val source: SourceFile,
    val line: Int,
    val column: Int,
    val length: Int,
) {
    override fun toString(): String {
        return "($source, line: $line, column: $column)"
    }

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is SourceLocation) {
            return false
        }
        // SourceLocations always match
        return true
    }

    override fun hashCode(): Int {
        return javaClass.hashCode()
    }
}
