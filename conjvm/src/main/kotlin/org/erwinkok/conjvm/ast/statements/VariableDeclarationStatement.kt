package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.Declarator
import org.erwinkok.conjvm.ast.SourceLocation
import org.erwinkok.conjvm.ast.VariableType
import org.erwinkok.conjvm.ast.expressions.Expression

data class VariableDeclarator(val location: SourceLocation, val declarator: Declarator, val init: Expression?) {
    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is VariableDeclarator) {
            return false
        }

        if (declarator != other.declarator) return false
        if (init != other.init) return false

        return true
    }

    override fun hashCode(): Int {
        var result = declarator.hashCode()
        result = 31 * result + (init?.hashCode() ?: 0)
        return result
    }
}

class VariableDeclarationStatement(
    location: SourceLocation,
    val type: VariableType?,
    val variableDeclarators: List<VariableDeclarator>,
) : Statement(location) {
    override fun <R, C> accept(visitor: AstStatementVisitor<R, C>, ctx: C): R = visitor.visitVariableDeclaration(this, ctx)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is VariableDeclarationStatement) {
            return false
        }

        if (type != other.type) return false
        if (variableDeclarators != other.variableDeclarators) return false

        return true
    }

    override fun hashCode(): Int {
        var result = type?.hashCode() ?: 0
        result = 31 * result + variableDeclarators.hashCode()
        return result
    }
}
