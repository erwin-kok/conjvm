package org.erwinkok.conjvm.declarations

enum class StorageClass {
    TYPEDEF,
    EXTERN,
    STATIC,
    THREAD_LOCAL,
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
    object BOOL : TypeSpec()
    object COMPLEX : TypeSpec()

    data class TypedefName(val name: String) : TypeSpec()
    data class Struct(val name: String?) : TypeSpec()
    data class Enum(val name: String?) : TypeSpec()
}

enum class TypeQualifier {
    CONST,
    RESTRICT,
    VOLATILE,
    ATOMIC,
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
