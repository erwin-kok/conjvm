package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.declarations.Entity
import org.erwinkok.conjvm.parser.SourceLocation

class VariableDeclarationStatement(
    location: SourceLocation,
    val variables: List<Entity.Variable>,
) : Statement(location) {
    override fun <R> accept(visitor: AstStatementVisitor<R>): R = visitor.visitVariableDeclaration(this)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is VariableDeclarationStatement) {
            return false
        }
        if (variables != other.variables) return false
        return true
    }

    override fun hashCode(): Int {
        return variables.hashCode()
    }
}
