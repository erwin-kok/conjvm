package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.SourceLocation

class CompilationUnitStatement(
    location: SourceLocation,
    val variableDeclarations: List<VariableDeclarationStatement>,
    val functionDefinitions: List<FunctionDefinitionStatement>,
) : Statement(location) {
    override fun <R, C> accept(visitor: AstStatementVisitor<R, C>, ctx: C): R = visitor.visitCompilationUnit(this, ctx)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is CompilationUnitStatement) {
            return false
        }
        if (variableDeclarations != other.variableDeclarations) return false
        if (functionDefinitions != other.functionDefinitions) return false

        return true
    }

    override fun hashCode(): Int {
        var result = variableDeclarations.hashCode()
        result = 31 * result + functionDefinitions.hashCode()
        return result
    }
}
