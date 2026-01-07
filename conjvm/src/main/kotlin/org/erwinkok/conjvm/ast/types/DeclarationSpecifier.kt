package org.erwinkok.conjvm.ast.types

enum class StorageClass {
    TYPEDEF,
    EXTERN,
    STATIC,
    AUTO,
    REGISTER,
}

sealed class TypeSpec {
    object VOID : TypeSpec()
    object CHAR : TypeSpec()
    object SHORT : TypeSpec()
    object INT : TypeSpec()
    object LONG : TypeSpec()
    object FLOAT : TypeSpec()
    object DOUBLE : TypeSpec()
    object SIGNED : TypeSpec()
    object UNSIGNED : TypeSpec()

    data class TypedefName(val name: String) : TypeSpec()
    data class Struct(val name: String?) : TypeSpec()
    data class Enum(val name: String?) : TypeSpec()
}

enum class TypeQualifier {
    CONST,
    VOLATILE,
    RESTRICT,
}

enum class FunctionSpec {
    INLINE,
}

data class DeclarationSpecifier(
    val storage: Set<StorageClass>,
    val typeSpecs: List<TypeSpec>,
    val qualifiers: Set<TypeQualifier>,
    val functionSpecs: Set<FunctionSpec>,
) {
    val hasTypedef: Boolean = storage.contains(StorageClass.TYPEDEF)
}
