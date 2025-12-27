package org.erwinkok.conjvm.translation

import org.erwinkok.conjvm.ast.statements.BlockStatement
import org.erwinkok.conjvm.ast.statements.ExpressionStatement
import org.erwinkok.conjvm.ast.statements.ForInitAssignmentExpression
import org.erwinkok.conjvm.ast.statements.ForInitVariableDeclaration
import org.erwinkok.conjvm.ast.statements.ForStatement
import org.erwinkok.conjvm.ast.statements.Statement
import org.erwinkok.conjvm.ast.statements.WhileStatement

class ConvertForToWhileTranslation : BaseTranslationVisitor() {
    override fun translateFor(statement: ForStatement): TranslationResult {
        val allStatements = mutableListOf<Statement>()
        if (statement.init is ForInitAssignmentExpression) {
            allStatements.addAll(
                statement.init.assignments.map {
                    ExpressionStatement(statement.location, it)
                },
            )
        } else if (statement.init is ForInitVariableDeclaration) {
            allStatements.add(statement.init.variableDeclaration)
        }
        val whileStatements = mutableListOf<Statement>()
        whileStatements.addAll(statement.statements.statements)
        if (statement.iterators != null) {
            whileStatements.addAll(
                statement.iterators.map {
                    ExpressionStatement(statement.location, it)
                },
            )
        }
        val whileStatement = WhileStatement(
            statement.location,
            statement.test!!, // TODO
            BlockStatement(statement.location, whileStatements),
        )
        allStatements.add(whileStatement)
        return if (statement.init is ForInitVariableDeclaration) {
            TranslationResult(listOf(BlockStatement(statement.location, allStatements)), null)
        } else {
            TranslationResult(allStatements, null)
        }
    }
}
