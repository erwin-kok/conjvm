package org.erwinkok.conjvm.ast.expressions

enum class AssignmentOperator {
    Assign,
    PlusAssign,
    MinusAssign,
    MultiplyAssign,
    DivideAssign,
    ModuloAssign,
    AndAssign,
    OrAssign,
    XorAssign,
    LeftShiftAssign,
    RightShiftAssign,
    ;

    override fun toString(): String {
        return when (this) {
            Assign -> "="
            PlusAssign -> "+="
            MinusAssign -> "-="
            MultiplyAssign -> "*="
            DivideAssign -> "/="
            ModuloAssign -> "%="
            AndAssign -> "&="
            OrAssign -> "|="
            XorAssign -> "^="
            LeftShiftAssign -> "<<"
            RightShiftAssign -> ">>"
        }
    }

    companion object {
        fun parse(type: String): AssignmentOperator {
            return when (type) {
                "=" -> Assign
                "+=" -> PlusAssign
                "-=" -> MinusAssign
                "*=" -> MultiplyAssign
                "/=" -> DivideAssign
                "%=" -> ModuloAssign
                "&=" -> AndAssign
                "|=" -> OrAssign
                "^=" -> XorAssign
                "<<=" -> LeftShiftAssign
                ">>=" -> RightShiftAssign
                else -> error("Invalid binary expression type: $type")
            }
        }
    }
}
