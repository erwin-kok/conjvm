package org.erwinkok.conjvm.types

import java.util.UUID

data class StructMember(
    val name: String,
    val type: QualType,
)

sealed class Type {
    // Error type for error recovery.
    object Error : Type()
    object Void : Type()
    object Bool : Type()

    // Floating point types
    object Float : Type()
    object Double : Type()
    object LongDouble : Type()

    // Integer types
    data class Char(val signed: Boolean) : Type()
    data class Short(val signed: Boolean) : Type()
    data class Int(val signed: Boolean) : Type()
    data class Long(val signed: Boolean) : Type()
    data class LongLong(val signed: Boolean) : Type()

    data class Pointer(val pointee: QualType) : Type()
    data class Array(val elementType: QualType, val size: kotlin.Long?) : Type()
    data class Function(val returnType: QualType, val parameters: List<QualType>) : Type()
    data class BitField(val base: QualType, val width: kotlin.Int) : Type()

    data class Struct(
        val id: UUID,
        val tag: String?,
        val members: List<StructMember>?, // null = incomplete type
    ) : Type() {
        override fun equals(other: Any?): Boolean {
            if (this === other) return true
            if (other !is Struct) return false
            return this.id == other.id
        }

        override fun hashCode(): kotlin.Int = id.hashCode()
    }

    data class Enum(
        val id: UUID,
        val tag: String?,
        val constants: Map<String, Long>?, // null = incomplete
    ) : Type() {
        override fun equals(other: Any?): Boolean {
            if (this === other) return true
            if (other !is Enum) return false
            return this.id == other.id
        }

        override fun hashCode(): kotlin.Int = id.hashCode()
    }

    data class Typedef(
        val name: String,
        val underlying: QualType,
    ) : Type() {
        override fun equals(other: Any?): Boolean {
            if (this === other) return true
            if (other !is Typedef) return false
            // Typedef equality is based on canonical type
            return this.underlying.canonical == other.underlying.canonical
        }

        override fun hashCode(): kotlin.Int = underlying.canonical.hashCode()
    }

    fun isCompatibleWith(other: Type): Boolean {
        if (this === other) return true
        return when (this) {
            // Primitive types
            is Char if other is Char -> this.signed == other.signed
            is Short if other is Short -> this.signed == other.signed
            is Int if other is Int -> this.signed == other.signed
            is Long if other is Long -> this.signed == other.signed
            is LongLong if other is LongLong -> this.signed == other.signed

            // Composite types
            is Pointer if other is Pointer -> pointerCompatible(this, other)
            is Array if other is Array -> arrayCompatible(this, other)
            is Function if other is Function -> functionCompatible(this, other)

            // Nominal types (compare by identity)
            is Struct if other is Struct -> this.id == other.id
            is Enum if other is Enum -> this.id == other.id

            // Typedefs should have been canonicalized already
            is Typedef -> error("Typedef should not appear in compatibility check")

            // Error types are compatible with everything
            is Error -> true

            else -> false
        }
    }

    override fun toString(): String = when (this) {
        is Error -> "<error>"
        is Void -> "void"
        is Bool -> "bool"

        is Float -> "float"
        is Double -> "double"
        is LongDouble -> "long double"

        is Char -> if (this.signed) "signed char" else "unsigned char"
        is Short -> if (this.signed) "short" else "unsigned short"
        is Int -> if (this.signed) "int" else "unsigned int"
        is Long -> if (this.signed) "long" else "unsigned long"
        is LongLong -> if (this.signed) "long long" else "unsigned long long"

        is Pointer -> "${this.pointee.type}*".let {
            if (this.pointee.qualifiers.isNotEmpty()) {
                this.pointee.qualifiers.joinToString(" ", postfix = " ") + it
            } else {
                it
            }
        }

        is Array -> {
            "${this.elementType.type}[${this.size?.toString() ?: ""}]"
        }

        is Function -> {
            val params = this.parameters.joinToString(", ") { it.type.toString() }
            "${this.returnType}($params)"
        }

        is BitField -> {
            "${this.base.type} : [${this.width}]"
        }

        is Struct -> this.tag?.let { "struct $it" } ?: "<anonymous struct>"
        is Enum -> this.tag?.let { "enum $it" } ?: "<anonymous enum>"

        is Typedef -> this.name
    }

    private fun pointerCompatible(a: Pointer, b: Pointer): Boolean {
        val pa = a.pointee.canonical
        val pb = b.pointee.canonical
        // void* is compatible with any object pointer
        if (pa.type == Void || pb.type == Void) {
            return true
        }
        return pa.isCompatibleWith(pb)
    }

    private fun arrayCompatible(a: Array, b: Array): Boolean {
        // Element types must be compatible
        if (!a.elementType.isCompatibleWith(b.elementType)) {
            return false
        }
        // Sizes: if both known, must match
        if (a.size != null && b.size != null && a.size != b.size) {
            return false
        }
        return true
    }

    private fun functionCompatible(a: Function, b: Function): Boolean {
        if (!a.returnType.isCompatibleWith(b.returnType)) {
            return false
        }
        if (a.parameters.isEmpty() || b.parameters.isEmpty()) {
            return true
        }

        if (a.parameters.size != b.parameters.size) {
            return false
        }
        return a.parameters.zip(b.parameters).all { (pa, pb) ->
            pa.isCompatibleWith(pb)
        }
    }
}
