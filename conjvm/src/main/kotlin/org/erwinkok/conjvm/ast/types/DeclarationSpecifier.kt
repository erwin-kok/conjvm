package org.erwinkok.conjvm.ast.types

typealias Qualifiers = Set<TypeQualifier>

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
    val storage: MutableSet<StorageClass> = mutableSetOf(),
    val typeSpecs: MutableList<TypeSpec> = mutableListOf(),
    val qualifiers: MutableSet<TypeQualifier> = mutableSetOf(),
    val functionSpecs: MutableSet<FunctionSpec> = mutableSetOf(),
)
