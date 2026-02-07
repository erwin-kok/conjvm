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
    ;

    override fun toString(): String {
        return when (this) {
            AddressOf -> "&"
            Dereference -> "*"
            Plus -> "+"
            Minus -> "-"
            BitwiseNot -> "~"
            LogicalNot -> "!"
            PrefixIncrement -> "++"
            PrefixDecrement -> "--"
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
