package org.erwinkok.conjvm.ast.expressions

enum class UnaryOperator {
    AddressOf,
    Dereference,
    Plus,
    Minus,
    BitwiseNot,
    LogicalNot,
    PlusPlus,
    MinusMinus,
    ;

    override fun toString(): String {
        return when (this) {
            AddressOf -> "&"
            Dereference -> "*"
            Plus -> "+"
            Minus -> "-"
            BitwiseNot -> "~"
            LogicalNot -> "!"
            PlusPlus -> "++"
            MinusMinus -> "--"
        }
    }

    companion object {
        fun parse(type: String): UnaryOperator {
            return when (type) {
                "&" -> AddressOf
                "*" -> Dereference
                "+" -> Plus
                "-" -> Minus
                "~" -> BitwiseNot
                "!" -> LogicalNot
                "++" -> PlusPlus
                "--" -> MinusMinus
                else -> error("Invalid unary expression type: $type")
            }
        }
    }
}
