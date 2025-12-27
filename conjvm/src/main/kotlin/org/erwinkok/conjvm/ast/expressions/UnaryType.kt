package org.erwinkok.conjvm.ast.expressions

enum class UnaryType {
    Address, // &
    Indirection, // *
    Plus, // +
    Minus, // -
    BitwiseNot, // ~
    LogicalNot, // !
    PlusPlus, // ++
    MinusMinus, // --
    ;

    override fun toString(): String {
        return when (this) {
            Address -> "&"
            Indirection -> "*"
            Plus -> "+"
            Minus -> "-"
            BitwiseNot -> "~"
            LogicalNot -> "!"
            PlusPlus -> "++"
            MinusMinus -> "--"
        }
    }
}
