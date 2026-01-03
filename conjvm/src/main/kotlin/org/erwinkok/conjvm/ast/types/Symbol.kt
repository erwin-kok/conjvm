package org.erwinkok.conjvm.ast.types

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
