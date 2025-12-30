package org.erwinkok.conjvm.ast

sealed class Type {
    object Int : Type()
    object Void : Type()
    object Error : Type()

    data class Ptr(val base: Type) : Type()
    data class Func(val returnType: Type, val params: List<Type>) : Type()
}

fun sameType(a: Type, b: Type): Boolean =
    when {
        a === b -> true
        a is Type.Ptr && b is Type.Ptr ->
            sameType(a.base, b.base)

        a is Type.Func && b is Type.Func ->
            sameType(a.returnType, b.returnType) &&
                a.params.size == b.params.size &&
                a.params.zip(b.params).all { sameType(it.first, it.second) }

        else -> false
    }
