package org.erwinkok.conjvm.ast

data class SourceLocation(
    val startLine: Int,
    val startColumn: Int,
    val endLine: Int,
    val endColumn: Int,
) {
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
