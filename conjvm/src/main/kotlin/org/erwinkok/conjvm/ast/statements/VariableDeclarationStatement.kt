package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.types.Declarator
import org.erwinkok.conjvm.ast.SourceLocation
import org.erwinkok.conjvm.ast.expressions.Expression
import org.erwinkok.conjvm.ast.types.DeclarationSpecifier

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
    val declarationSpecifier: DeclarationSpecifier,
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

        if (declarationSpecifier != other.declarationSpecifier) return false
        if (variableDeclarators != other.variableDeclarators) return false

        return true
    }

    override fun hashCode(): Int {
        var result = declarationSpecifier.hashCode()
        result = 31 * result + variableDeclarators.hashCode()
        return result
    }
}
