package org.erwinkok.conjvm.ast.types

data class Field(val name: String, val type: QualType)

sealed class Type {
    object Error : Type()

    object Void : Type() {
        override fun toString() = "void"
    }

    data class Char(val signed: Boolean) : Type()
    data class Short(val signed: Boolean) : Type()
    data class Int(val signed: Boolean) : Type() {
        override fun toString() = "int"
    }

    data class Long(val signed: Boolean) : Type()
    data class LongLong(val signed: Boolean) : Type()

    object Float : Type()
    object Double : Type()

    data class Struct(
        val tag: String?, // null = anonymous
        val fields: List<Field>?, // null = incomplete type
    ) : Type()

    data class Pointer(val pointee: QualType) : Type()
    data class Array(val elementType: QualType, val size: kotlin.Long?) : Type()
    data class Function(val returnType: QualType, val parameters: List<QualType>) : Type()
    data class Typedef(val name: String, val underlying: QualType) : Type() {
        override fun equals(other: Any?): Boolean {
            if (this === other) return true
            if (other !is Typedef) return false
            return this.underlying.canonical == other.underlying.canonical
        }

        override fun hashCode(): kotlin.Int = underlying.canonical.hashCode()
    }
}
