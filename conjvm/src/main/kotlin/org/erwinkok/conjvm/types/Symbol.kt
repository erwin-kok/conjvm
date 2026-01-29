package org.erwinkok.conjvm.types

import org.erwinkok.conjvm.declarations.StorageClass

data class VariableSymbol(
    val name: String,
    val type: QualType,
    val storage: Set<StorageClass>,
)

data class FunctionSymbol(
    val name: String,
    val type: QualType,
    val storage: Set<StorageClass>,
)
