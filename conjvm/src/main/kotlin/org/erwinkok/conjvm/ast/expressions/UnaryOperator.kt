package org.erwinkok.conjvm.ast.expressions

enum class UnaryOperator {
    AddressOf,
    Dereference,
    Plus,
    Minus,
    BitwiseNot,
    LogicalNot,
    PrefixIncrement,
    PrefixDecrement,
    PostfixIncrement,
    PostfixDecrement,
    ;

    override fun toString(): String {
        return when (this) {
            AddressOf -> "&"
            Dereference -> "*"
            Plus -> "+"
            Minus -> "-"
            BitwiseNot -> "~"
            LogicalNot -> "!"
            PrefixIncrement, PostfixIncrement -> "++"
            PrefixDecrement, PostfixDecrement -> "--"
        }
    }

    companion object {
        fun parse(type: String): UnaryOperator? {
            return when (type) {
                "&" -> AddressOf
                "*" -> Dereference
                "+" -> Plus
                "-" -> Minus
                "~" -> BitwiseNot
                "!" -> LogicalNot
                "++" -> PrefixIncrement
                "--" -> PrefixDecrement
                else -> null
            }
        }
    }
}
