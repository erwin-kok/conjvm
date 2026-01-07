package org.erwinkok.conjvm.ast.types

import java.util.UUID

class SymbolTable {
    private val typedefs = mutableSetOf<String>()
    private val structTags = mutableSetOf<String>()
    private val enumTags = mutableSetOf<String>()

    private val typedefTable = mutableMapOf<String, QualType>()

    init {
        typedefTable["uint"] = QualType(Type.Int(false))
        typedefTable["uint8"] = QualType(Type.Char(false))
        typedefTable["uint16"] = QualType(Type.Short(false))
        typedefTable["uint32"] = QualType(Type.Int(false))
        typedefTable["uint64"] = QualType(Type.LongLong(false))

        typedefTable["sint"] = QualType(Type.Int(true))
        typedefTable["sint8"] = QualType(Type.Char(true))
        typedefTable["sint16"] = QualType(Type.Short(true))
        typedefTable["sint32"] = QualType(Type.Int(true))
        typedefTable["sint64"] = QualType(Type.LongLong(true))

        typedefTable["int"] = QualType(Type.Int(true))
        typedefTable["int8"] = QualType(Type.Char(true))
        typedefTable["int16"] = QualType(Type.Short(true))
        typedefTable["int32"] = QualType(Type.Int(true))
        typedefTable["int64"] = QualType(Type.Long(true))

        typedefTable["m68ki_bitfield_t"] = QualType(Type.Struct(UUID.randomUUID(), "m68ki_bitfield_t", emptyList()))
    }

    fun defineTypedef(name: String) {
        typedefs.add(name)
    }

    fun defineStructTag(name: String) {
        structTags.add(name)
    }

    fun defineEnumTag(name: String) {
        enumTags.add(name)
    }

    fun defineTypedef(name: String, type: QualType) {
        typedefTable[name] = type
    }

    fun resolve(name: String): QualType? {
        return typedefTable[name]
    }

    fun isTypedef(name: String): Boolean {
        return typedefTable.containsKey(name)
    }
}
