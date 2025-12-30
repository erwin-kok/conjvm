package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.SourceLocation
import org.erwinkok.conjvm.ast.Symbol
import org.erwinkok.conjvm.ast.Type

class FunctionDefinitionStatement(
    location: SourceLocation,
    val returnType: Type,
    val name: String,
    val params: List<Symbol>,
    val statements: BlockStatement,
) : Statement(location) {
    override fun <R, C> accept(visitor: AstStatementVisitor<R, C>, ctx: C): R = visitor.visitFunctionDefinition(this, ctx)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is FunctionDefinitionStatement) {
            return false
        }
        if (returnType != other.returnType) return false
        if (name != other.name) return false
        if (params != other.params) return false
        if (statements != other.statements) return false

        return true
    }

    override fun hashCode(): Int {
        var result = returnType.hashCode()
        result = 31 * result + name.hashCode()
        result = 31 * result + params.hashCode()
        result = 31 * result + statements.hashCode()
        return result
    }

    override fun toString(): String {
        return name
    }
}
