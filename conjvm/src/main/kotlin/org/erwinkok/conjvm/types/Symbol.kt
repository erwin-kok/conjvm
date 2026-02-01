package org.erwinkok.conjvm.types

import org.erwinkok.conjvm.declarations.Entity
import org.erwinkok.conjvm.declarations.FunctionSpec
import org.erwinkok.conjvm.declarations.Linkage
import org.erwinkok.conjvm.declarations.Scope
import org.erwinkok.conjvm.declarations.StorageClass

data class TypedefSymbol(
    val name: String,
    val type: QualType,
    val scope: Scope,
    val entity: Entity.Typedef,
)

data class VariableSymbol(
    val name: String,
    val type: QualType,
    val storage: Set<StorageClass>,
    val linkage: Linkage,
    val scope: Scope,
    val entity: Entity.Variable,
) {
    val isDefinition: Boolean
        get() = entity.definition != null

    val isExtern: Boolean
        get() = storage.contains(StorageClass.EXTERN)

    val isStatic: Boolean
        get() = storage.contains(StorageClass.STATIC)
}

data class FunctionSymbol(
    val name: String,
    val returnType: QualType,
    val parameterTypes: List<QualType>,
    val storage: Set<StorageClass>,
    val linkage: Linkage,
    val scope: Scope,
    val entity: Entity.Function,
) {
    val isDefinition: Boolean
        get() = entity.definition != null

    val isInline: Boolean
        get() = entity.declarations.any {
            it.declarationSpecifier.functionSpecs.contains(FunctionSpec.INLINE)
        }
}

data class StructSymbol(
    val name: String?,
    val members: List<StructMember>,
    val isComplete: Boolean,
    val scope: Scope,
    val entity: Entity.Struct,
    val size: Long?,
    val alignment: Long?,
) {
    val isAnonymous: Boolean
        get() = name == null
}

data class EnumSymbol(
    val name: String?,
    val constants: Map<String, Long>,
    val underlyingType: QualType,
    val scope: Scope,
    val entity: Entity.Enum,
) {
    val isAnonymous: Boolean
        get() = name == null
}

data class EnumConstant(
    val name: String,
    val value: Long,
    val enumSymbol: EnumSymbol,
)
