package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.expressions.Expression
import org.erwinkok.conjvm.declarations.DeclarationSpecifier
import org.erwinkok.conjvm.declarations.Declarator
import org.erwinkok.conjvm.parser.SourceLocation

data class VariableDeclarator(val location: SourceLocation, val declarator: Declarator, val init: Expression?)

class VariableDeclarationStatement(
    location: SourceLocation,
    val declarationSpecifier: DeclarationSpecifier,
    val variableDeclarators: List<VariableDeclarator>,
) : Statement(location) {
    override fun <R> accept(visitor: AstStatementVisitor<R>): R = visitor.visitVariableDeclaration(this)

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
