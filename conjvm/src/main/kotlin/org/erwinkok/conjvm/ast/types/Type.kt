package org.erwinkok.conjvm.ast.types

import org.erwinkok.conjvm.ast.expressions.Expression

sealed class Type {
    object TError : Type()

    sealed class Builtin : Type() {
        object TVoid : Builtin()
        data class TInt(val signed: Boolean, val width: Int) : Builtin()
        object TFloat : Builtin()
        object TDouble : Builtin()
    }

    data class TPointer(val pointee: QualType) : Type()
    data class TArray(val element: QualType, val size: Expression?) : Type()
    data class TFunction(
        val returnType: QualType,
        val params: List<QualType>,
        val variadic: Boolean,
    ) : Type()

    data class TRecord(val name: TString?, val isUnion: Boolean) : Type()
    data class TEnum(val name: TString?) : Type()
    data class TTypedef(val name: TString, val underlying: QualType) : Type()

    //
    data class XXX(val x: String = "xxx") : Type()

    //
    object TInt : Type()
    object TLong : Type()
    object TString : Type()
    object TVoid : Type()

    data class TPtr(val base: Type) : Type()
    data class TFunc(val returnType: Type, val params: List<Type>) : Type()
}

fun sameType(a: Type, b: Type): Boolean {
    return when {
        a === b -> true
        a is Type.TPtr && b is Type.TPtr ->
            sameType(a.base, b.base)

        a is Type.TFunc && b is Type.TFunc ->
            sameType(a.returnType, b.returnType) &&
                a.params.size == b.params.size &&
                a.params.zip(b.params).all { sameType(it.first, it.second) }

        else -> false
    }
}
