package org.erwinkok.conjvm.ast.types

enum class VariableType {
    INT,
    INT8,
    INT16,
    INT32,
    INT64,
    UINT,
    UINT8,
    UINT16,
    UINT32,
    UINT64,
    SINT,
    SINT8,
    SINT16,
    SINT32,
    SINT64,
    BITFIELD,
    VOID,
    ;

    override fun toString(): String {
        return when (this) {
            INT -> "int"
            INT8 -> "int8"
            INT16 -> "int16"
            INT32 -> "int32"
            INT64 -> "int64"
            UINT -> "uint"
            UINT8 -> "uint8"
            UINT16 -> "uint16"
            UINT32 -> "uint32"
            UINT64 -> "uint64"
            SINT -> "sint"
            SINT8 -> "sint8"
            SINT16 -> "sint16"
            SINT32 -> "sint32"
            SINT64 -> "sint64"
            BITFIELD -> "m68ki_bitfield_t"
            VOID -> "void"
        }
    }

    companion object {
        fun parse(type: String): VariableType {
            return when (type) {
                "int" -> INT
                "int8" -> INT8
                "int16" -> INT16
                "int32" -> INT32
                "int64" -> INT64
                "uint" -> UINT
                "uint8" -> UINT8
                "uint16" -> UINT16
                "uint32" -> UINT32
                "uint64" -> UINT64
                "sint" -> SINT
                "sint8" -> SINT8
                "sint16" -> SINT16
                "sint32" -> SINT32
                "sint64" -> SINT64
                "m68ki_bitfield_t" -> BITFIELD
                "void" -> VOID
                else -> error("Invalid variable type: $type")
            }
        }

        fun isTypedef(s: String): Boolean {
            return s == "int" ||
                s == "int8" ||
                s == "int16" ||
                s == "int32" ||
                s == "int64" ||
                s == "uint" ||
                s == "uint8" ||
                s == "uint16" ||
                s == "uint32" ||
                s == "uint64" ||
                s == "sint" ||
                s == "sint8" ||
                s == "sint16" ||
                s == "sint32" ||
                s == "sint64" ||
                s == "void" ||
                s == "m68ki_bitfield_t"
        }
    }
}
