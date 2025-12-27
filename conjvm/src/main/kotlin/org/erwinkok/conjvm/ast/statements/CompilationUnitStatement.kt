package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.SourceLocation

class CompilationUnitStatement(location: SourceLocation, val functionDefinitionStatements: List<FunctionDefinitionStatement>) : Statement(location) {
    override fun <R, C> accept(visitor: AstStatementVisitor<R, C>, ctx: C): R = visitor.visitCompilationUnit(this, ctx)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is CompilationUnitStatement) {
            return false
        }
        return functionDefinitionStatements == other.functionDefinitionStatements
    }

    override fun hashCode(): Int {
        return functionDefinitionStatements.hashCode()
    }
}
