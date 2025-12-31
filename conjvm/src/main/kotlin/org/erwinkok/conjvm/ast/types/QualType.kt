package org.erwinkok.conjvm.ast.types

data class QualType(
    val type: Type,
    val qualifiers: Qualifiers = emptySet(),
) {
    fun with(q: TypeQualifier) = copy(qualifiers = qualifiers + q)
}
