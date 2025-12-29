package org.erwinkok.conjvm.ast

sealed class Type {
    object Int : Type()
    object Void : Type()
    object Error : Type()

    data class Ptr(val base: Type) : Type()
    data class Func(val returnType: Type, val params: List<Type>) : Type()
}
