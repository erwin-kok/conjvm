package org.erwinkok.conjvm.types

import org.erwinkok.conjvm.declarations.TypeQualifier

data class QualType(
    val type: Type,
    val qualifiers: Set<TypeQualifier> = emptySet(),
) {
    companion object {
        val ErrorType = QualType(Type.Error, emptySet())
    }

    val isError: Boolean get() = this.type == Type.Error
    val isConst: Boolean get() = TypeQualifier.CONST in qualifiers
    val isVolatile: Boolean get() = TypeQualifier.VOLATILE in qualifiers
    val isRestrict: Boolean get() = TypeQualifier.RESTRICT in qualifiers

    /**
     * Canonical form - all typedefs resolved, qualifiers accumulated.
     * Computed lazily and cached.
     */
    val canonical: QualType by lazy { computeCanonical() }

    // Add a qualifier to this type.
    fun with(q: TypeQualifier) = copy(qualifiers = qualifiers + q)

    // Remove all qualifiers from this type.
    fun withoutQualifiers() = QualType(type, emptySet())

    // Get the underlying type if this is a typedef, otherwise return this.
    fun unwrapTypedef(): QualType {
        return if (type is Type.Typedef) {
            type.underlying
        } else {
            this
        }
    }

    fun isCompatibleWith(other: QualType): Boolean {
        // Error types are compatible with everything
        if (this.isError || other.isError) {
            return true
        }
        val a = this.canonical
        val b = other.canonical
        return a.type.isCompatibleWith(b.type)
    }

    /**
     * Assignment compatibility (includes qualifier checking).
     * For assignment: target = source
     * - Types must be compatible
     * - Target must have at least the qualifiers of source
     */
    fun canAssignFrom(source: QualType): Boolean {
        if (!isCompatibleWith(source)) return false

        // Check qualifier compatibility
        // const int* can't be assigned to int*
        // but int* can be assigned to const int*
        val targetCanon = this.canonical
        val sourceCanon = source.canonical

        // For pointers, check pointee qualifiers
        if (targetCanon.type is Type.Pointer && sourceCanon.type is Type.Pointer) {
            val targetPointee = targetCanon.type.pointee
            val sourcePointee = sourceCanon.type.pointee

            // Target pointee must have at least source's qualifiers
            return sourcePointee.qualifiers.all { it in targetPointee.qualifiers }
        }

        return true
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

    /**
     * Compute the canonical form by:
     * 1. Unwrapping all typedefs
     * 2. Accumulating qualifiers along the way
     * 3. Recursively canonicalizing composite types
     */
    private fun computeCanonical(): QualType {
        var current: QualType = this
        val seenNames = mutableSetOf<String>()
        var accumulatedQualifiers = current.qualifiers

        // Unwrap typedefs
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
        // Recursively canonicalize the inner type
        val canonicalType = canonicalizeInner(current.type)
        return QualType(canonicalType, accumulatedQualifiers)
    }

    private fun canonicalizeInner(type: Type): Type {
        return when (type) {
            is Type.Pointer -> Type.Pointer(type.pointee.canonical)
            is Type.Array -> Type.Array(type.elementType.canonical, type.size)
            is Type.Function -> Type.Function(type.returnType.canonical, type.parameters.map { it.canonical })
            is Type.BitField -> Type.BitField(type.base.canonical, type.width)
            is Type.Typedef -> error("Typedef should have been unwrapped already")
            else -> type
        }
    }
}
