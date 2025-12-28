package org.erwinkok.conjvm.ast.expressions

enum class BinaryExpressionType {
    LogicalOr,
    LogicalAnd,
    InclusiveOr,
    ExclusiveOr,
    And,
    Equals,
    NotEquals,
    Less,
    Greater,
    LessOrEqual,
    GreaterOrEqual,
    ShiftLeft,
    ShiftRight,
    Add,
    Subtract,
    Multiply,
    Divide,
    Modulo,
    ;

    override fun toString(): String {
        return when (this) {
            LogicalOr -> "||"
            LogicalAnd -> "&&"
            InclusiveOr -> "|"
            ExclusiveOr -> "^"
            And -> "&"
            Equals -> "=="
            NotEquals -> "!="
            Less -> "<"
            Greater -> ">"
            LessOrEqual -> "<="
            GreaterOrEqual -> ">="
            ShiftLeft -> "<<"
            ShiftRight -> ">>"
            Add -> "+"
            Subtract -> "-"
            Multiply -> "*"
            Divide -> "/"
            Modulo -> "%"
        }
    }

    companion object {
        fun parse(type: String): BinaryExpressionType {
            return when (type) {
                "||" -> LogicalOr
                "&&" -> LogicalAnd
                "|" -> InclusiveOr
                "^" -> ExclusiveOr
                "&" -> And
                "==" -> Equals
                "!=" -> NotEquals
                "<" -> Less
                ">" -> Greater
                "<=" -> LessOrEqual
                ">=" -> GreaterOrEqual
                "<<" -> ShiftLeft
                ">>" -> ShiftRight
                "+" -> Add
                "-" -> Subtract
                "*" -> Multiply
                "/" -> Divide
                "%" -> Modulo
                else -> error("Invalid binary expression type: $type")
            }
        }
    }
}
