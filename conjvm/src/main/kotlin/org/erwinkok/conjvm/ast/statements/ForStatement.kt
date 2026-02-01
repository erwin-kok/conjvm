package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.expressions.AssignmentExpression
import org.erwinkok.conjvm.ast.expressions.Expression
import org.erwinkok.conjvm.parser.SourceLocation

sealed class ForInit

class ForInitAssignmentExpression(
    val assignments: List<AssignmentExpression>,
) : ForInit() {
    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is ForInitAssignmentExpression) {
            return false
        }

        if (assignments != other.assignments) return false

        return true
    }

    override fun hashCode(): Int {
        return assignments.hashCode()
    }
}

class ForInitVariableDeclaration(
    val variableDeclaration: VariableDeclarationStatement,
) : ForInit() {
    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is ForInitVariableDeclaration) {
            return false
        }

        if (variableDeclaration != other.variableDeclaration) return false

        return true
    }

    override fun hashCode(): Int {
        return variableDeclaration.hashCode()
    }
}

class ForStatement(
    location: SourceLocation,
    val init: ForInit?,
    val condition: Expression?,
    val iterators: List<Expression>?,
    val statements: BlockStatement,
) : Statement(location) {
    override fun <R> accept(visitor: AstStatementVisitor<R>): R = visitor.visitFor(this)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is ForStatement) {
            return false
        }

        if (init != other.init) return false
        if (condition != other.condition) return false
        if (iterators != other.iterators) return false
        if (statements != other.statements) return false

        return true
    }

    override fun hashCode(): Int {
        var result = init?.hashCode() ?: 0
        result = 31 * result + condition.hashCode()
        result = 31 * result + (iterators?.hashCode() ?: 0)
        result = 31 * result + statements.hashCode()
        return result
    }
}
