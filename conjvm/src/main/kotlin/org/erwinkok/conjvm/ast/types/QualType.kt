package org.erwinkok.conjvm.ast.types

import org.erwinkok.conjvm.declarations.TypeQualifier

data class QualType(
    val type: Type,
    val qualifiers: Set<TypeQualifier> = emptySet(),
) {
    companion object {
        val ErrorType = QualType(Type.Error, emptySet())
    }

    val canonical: QualType by lazy { computeCanonical() }

    val isError: Boolean = this.type == Type.Error

    fun with(q: TypeQualifier) = copy(qualifiers = qualifiers + q)

    fun withoutQualifiers() = QualType(type, emptySet())

    fun isCompatibleWith(other: QualType): Boolean {
        val a = this.canonical
        val b = other.canonical
        return a.type.isCompatibleWith(b.type)
    }

    override fun toString(): String {
        val qualPrefix = if (qualifiers.isEmpty()) {
            ""
        } else {
            qualifiers.joinToString(" ") { it.name.lowercase() } + " "
        }
        return qualPrefix + type.toString()
    }

    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (other !is QualType) return false

        return this.canonical.type == other.canonical.type &&
            this.canonical.qualifiers == other.canonical.qualifiers
    }

    override fun hashCode(): Int {
        return canonical.type.hashCode() * 31 + canonical.qualifiers.hashCode()
    }

    private fun computeCanonical(): QualType {
        var current: QualType = this
        val seenNames = mutableSetOf<String>()
        var accumulatedQualifiers = current.qualifiers
        while (current.type is Type.Typedef) {
            val td = current.type

            // detect circular typedefs by typedef name
            if (td.name in seenNames) {
                throw TypeException("circular typedef detected for '${td.name}'")
            }
            seenNames.add(td.name)

            // merge underlying qualifiers
            accumulatedQualifiers += td.underlying.qualifiers

            // move to underlying type
            current = td.underlying
        }
        val canonicalType = canonicalizeInner(current.type)
        return QualType(canonicalType, accumulatedQualifiers)
    }

    private fun canonicalizeInner(type: Type): Type {
        return when (type) {
            is Type.Pointer -> Type.Pointer(type.pointee.canonical)
            is Type.Array -> Type.Array(type.elementType.canonical, type.size)
            is Type.Function -> Type.Function(type.returnType.canonical, type.parameters.map { it.canonical })
            is Type.Typedef -> error("Typedef should not appear during canonicalization")
            else -> type
        }
    }
}
