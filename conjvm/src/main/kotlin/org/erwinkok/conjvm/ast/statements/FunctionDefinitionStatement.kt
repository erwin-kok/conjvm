package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.SourceLocation

class FunctionDefinitionStatement(location: SourceLocation, val name: String, val statements: BlockStatement) : Statement(location) {
    override fun <R, C> accept(visitor: AstStatementVisitor<R, C>, ctx: C): R = visitor.visitFunctionDefinition(this, ctx)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is FunctionDefinitionStatement) {
            return false
        }
        return name == other.name &&
            statements == other.statements
    }

    override fun hashCode(): Int {
        var result = name.hashCode()
        result = 31 * result + statements.hashCode()
        return result
    }

    override fun toString(): String {
        return name
    }
}
