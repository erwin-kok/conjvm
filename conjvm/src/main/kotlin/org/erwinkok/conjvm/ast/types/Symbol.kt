package org.erwinkok.conjvm.ast.types

import org.erwinkok.conjvm.ast.statements.BlockStatement

sealed class Symbol {
    abstract val name: String
    abstract val type: QualType
    abstract val storage: Set<StorageClass>

    val canonicalType: QualType get() = type.canonical
}

data class VariableSymbol(
    override val name: String,
    override val type: QualType,
    override val storage: Set<StorageClass>,
) : Symbol()

data class FunctionSymbol(
    override val name: String,
    override val type: QualType,
    override val storage: Set<StorageClass>,
    val body: BlockStatement?,
) : Symbol()
