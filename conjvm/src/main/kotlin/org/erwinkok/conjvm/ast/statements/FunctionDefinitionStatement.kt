package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.DeclarationSpecifier
import org.erwinkok.conjvm.ast.SourceLocation

class FunctionDefinitionStatement(
    location: SourceLocation,
    val declarationSpecifiers: List<DeclarationSpecifier>,
    val name: String,
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
        if (declarationSpecifiers != other.declarationSpecifiers) return false
        if (name != other.name) return false
        if (statements != other.statements) return false

        return true
    }

    override fun hashCode(): Int {
        var result = declarationSpecifiers.hashCode()
        result = 31 * result + name.hashCode()
        result = 31 * result + statements.hashCode()
        return result
    }

    override fun toString(): String {
        return name
    }
}
