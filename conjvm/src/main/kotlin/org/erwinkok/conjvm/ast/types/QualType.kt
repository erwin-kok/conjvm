package org.erwinkok.conjvm.ast.types

data class QualType(val type: Type, val qualifiers: Set<TypeQualifier> = emptySet()) {

    val canonical: QualType by lazy { computeCanonical() }

    fun with(q: TypeQualifier) = copy(qualifiers = qualifiers + q)

    fun isCompatibleWith(other: QualType): Boolean {
        val a = this.canonical
        val b = other.canonical

        if (a.qualifiers != b.qualifiers) return false
        return a.type == b.type
    }

    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (other !is QualType) return false

        return this.canonical.type == other.canonical.type &&
            this.canonical.qualifiers == other.canonical.qualifiers
    }

    override fun hashCode(): Int = canonical.type.hashCode() * 31 + canonical.qualifiers.hashCode()

    private fun computeCanonical(): QualType {
        var t = this
        val seen = mutableSetOf<Type>()
        while (t.type is Type.Typedef) {
            val typedefType = t.type
            if (!seen.add(typedefType)) {
                throw TypeException("circular typedef detected for '${typedefType.name}'")
            }
            // Merge qualifiers from typedef with outer qualifiers
            t = typedefType.underlying.copy(qualifiers = typedefType.underlying.qualifiers + t.qualifiers)
        }
        return t.copy(type = canonicalInner(t.type))
    }

    private fun canonicalInner(type: Type): Type {
        return when (type) {
            is Type.Pointer -> Type.Pointer(type.pointee.canonical)
            is Type.Array -> Type.Array(type.elementType.canonical, type.size)
            is Type.Function -> Type.Function(type.returnType.canonical, type.parameters.map { it.canonical })
            is Type.Typedef -> throw TypeException("Typedef not unwrapped in QualType.canonical()")
            else -> type
        }
    }
}
