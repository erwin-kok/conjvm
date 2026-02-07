package org.erwinkok.conjvm.declarations

import org.erwinkok.conjvm.ast.expressions.Expression
import org.erwinkok.conjvm.types.QualType
import org.erwinkok.conjvm.types.StructMember
import java.util.UUID

enum class Linkage {
    NONE,
    INTERNAL,
    EXTERNAL,
}

data class EnumConstant(
    val name: String,
    val value: Long,
    val enumEntity: Entity.Enum,
)

sealed interface Entity {
    val scope: Scope
    val name: String?

    class Typedef(
        override val scope: Scope,
        override val name: String,
    ) : Entity {
        val declarations = mutableListOf<Declaration.Typedef>()
        var type: QualType? = null
    }

    class Variable(
        override val scope: Scope,
        override val name: String,
    ) : Entity {
        val declarations = mutableListOf<Declaration.Variable>()
        var definition: Declaration.Variable? = null
        var linkage = Linkage.NONE
        var type: QualType? = null
        var initializer: Expression? = null
        val isDefinition: Boolean
            get() = definition != null
        val isExtern: Boolean
            get() = definition?.declarationSpecifier?.storage?.contains(StorageClass.EXTERN) == true
        val isStatic: Boolean
            get() = definition?.declarationSpecifier?.storage?.contains(StorageClass.STATIC) == true
    }

    class Function(
        override val scope: Scope,
        override val name: String,
    ) : Entity {
        val declarations = mutableListOf<Declaration.Function>()
        var definition: Declaration.Function? = null
        var linkage = Linkage.EXTERNAL
        var returnType: QualType? = null
        var parameterTypes: List<QualType>? = null
        val isDefinition: Boolean
            get() = definition != null
        val isInline: Boolean
            get() = declarations.any {
                it.declarationSpecifier.functionSpecs.contains(FunctionSpec.INLINE)
            }
    }

    class Struct(
        override val scope: Scope,
        override val name: String?,
        val id: UUID,
    ) : Entity {
        val declarations = mutableListOf<Declaration.Struct>()
        var definition: Declaration.Struct? = null
        var members: List<StructMember>? = null
        var size: Long? = null
        var alignment: Long? = null
        val isComplete: Boolean
            get() = members != null
    }

    class Enum(
        override val scope: Scope,
        override val name: String?,
        val id: UUID,
    ) : Entity {
        val declarations = mutableListOf<Declaration.Enum>()
        var definition: Declaration.Enum? = null
        var constants: Map<String, Long>? = null
        var underlyingType: QualType? = null
        val isComplete: Boolean
            get() = constants != null
    }

    class Label(
        override val scope: Scope,
        override val name: String?,
    ) : Entity {
        val declarations = mutableListOf<Declaration.Label>()
        val isDefined: Boolean
            get() = declarations.any { it.isDefined }
    }
}
