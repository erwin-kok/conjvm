package org.erwinkok.conjvm.ast.types

data class QualType(val type: Type, val qualifiers: Set<TypeQualifier> = emptySet()) {
    companion object {
        val ErrorType = QualType(Type.Error, emptySet())
    }

    val canonical: QualType by lazy { computeCanonical() }

    fun with(q: TypeQualifier) = copy(qualifiers = qualifiers + q)

    fun withoutQualifiers() = QualType(type, emptySet())

    fun isCompatibleWith(other: QualType): Boolean {
        val a = canonical
        val b = other.canonical

        return when {
            a.type is Type.Pointer && b.type is Type.Pointer ->
                a.type.pointee.isCompatibleWith(b.type.pointee)

            else -> a.type == b.type
        }
    }

    fun isAssignableFrom(rhs: QualType): Boolean {
        val lhs = this.canonical
        val r = rhs.canonical
        if (lhs.type != r.type) return false
        if (TypeQualifier.CONST in r.qualifiers && TypeQualifier.CONST !in lhs.qualifiers) {
            return false
        }
        return true
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
            // Merge qualifiers: typedef's qualifiers only apply at top level if not pointer
            t = when (typedefType.underlying.type) {
                is Type.Pointer -> {
                    // qualifiers inside pointer remain with pointer
                    QualType(typedefType.underlying.type, t.qualifiers)
                }

                else -> {
                    // merge qualifiers for normal types
                    typedefType.underlying.copy(qualifiers = typedefType.underlying.qualifiers + t.qualifiers)
                }
            }
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
