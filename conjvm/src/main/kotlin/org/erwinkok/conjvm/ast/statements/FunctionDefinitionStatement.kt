package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.SourceLocation
import org.erwinkok.conjvm.ast.types.DeclarationSpecifier
import org.erwinkok.conjvm.ast.types.Declarator

class FunctionDefinitionStatement(
    location: SourceLocation,
    val declarationSpecifier: DeclarationSpecifier,
    val declarator: Declarator,
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
        if (declarationSpecifier != other.declarationSpecifier) return false
        if (declarator != other.declarator) return false
        if (statements != other.statements) return false

        return true
    }

    override fun hashCode(): Int {
        var result = declarationSpecifier.hashCode()
        result = 31 * result + declarator.hashCode()
        result = 31 * result + statements.hashCode()
        return result
    }
}
