package org.erwinkok.conjvm.translation

import org.erwinkok.conjvm.ast.SourceLocation
import org.erwinkok.conjvm.ast.expressions.ConstantLongExpression
import org.erwinkok.conjvm.ast.expressions.Expression
import org.erwinkok.conjvm.ast.statements.BlockStatement
import org.erwinkok.conjvm.ast.statements.ContinueStatement
import org.erwinkok.conjvm.ast.statements.ExpressionStatement
import org.erwinkok.conjvm.ast.statements.ForInit
import org.erwinkok.conjvm.ast.statements.ForInitAssignmentExpression
import org.erwinkok.conjvm.ast.statements.ForInitVariableDeclaration
import org.erwinkok.conjvm.ast.statements.ForStatement
import org.erwinkok.conjvm.ast.statements.IfThenElseStatement
import org.erwinkok.conjvm.ast.statements.IfThenStatement
import org.erwinkok.conjvm.ast.statements.Statement
import org.erwinkok.conjvm.ast.statements.WhileStatement

class ConvertForToWhileTranslation : BaseTranslationVisitor() {
    override fun translateFor(statement: ForStatement): TranslationResult {
        val allStatements = mutableListOf<Statement>()
        allStatements.addAll(translateForInit(statement.location, statement.init))

        val (cts, cte) = translateCondition(statement.location, statement.condition)
        allStatements.addAll(cts)
        requireNotNull(cte)

        val whileStatements = mutableListOf<Statement>()
        val translatedIterators = translateIterators(statement.location, statement.iterators)
        whileStatements.add(rewriteContinues(statement.location, statement.statements, statement.iterators))
        whileStatements.addAll(translatedIterators)

        val whileStatement = WhileStatement(statement.location, cte, BlockStatement(statement.location, whileStatements))
        allStatements.add(whileStatement)
        return TranslationResult(listOf(BlockStatement(statement.location, allStatements)), null)
    }

    private fun translateForInit(location: SourceLocation, statement: ForInit?): List<Statement> {
        val allStatements = mutableListOf<Statement>()
        if (statement is ForInitAssignmentExpression) {
            statement.assignments.map {
                val (ts, te) = translate(it)
                requireNotNull(te)
                allStatements.addAll(ts)
                allStatements.add(ExpressionStatement(location, te))
            }
        } else if (statement is ForInitVariableDeclaration) {
            val (ts, te) = translate(statement.variableDeclaration)
            require(te == null)
            allStatements.addAll(ts)
        }
        return allStatements
    }

    private fun translateCondition(location: SourceLocation, condition: Expression?): TranslationResult {
        if (condition != null) {
            val (ts, te) = translate(condition)
            return TranslationResult(ts, te)
        } else {
            return TranslationResult(emptyList(), ConstantLongExpression(location, 1L))
        }
    }

    private fun translateIterators(location: SourceLocation, iterators: List<Expression>?): List<Statement> {
        val allStatements = mutableListOf<Statement>()
        iterators?.map {
            val (ts, te) = translate(it)
            requireNotNull(te)
            allStatements.addAll(ts)
            allStatements.add(ExpressionStatement(location, te))
        }
        return allStatements
    }

    private fun rewriteContinues(location: SourceLocation, stmt: Statement, iterators: List<Expression>?): Statement {
        if (iterators.isNullOrEmpty()) {
            return stmt
        }
        return when (stmt) {
            is ContinueStatement -> {
                BlockStatement(
                    location,
                    buildList {
                        for (it in iterators) {
                            add(ExpressionStatement(location, it))
                        }
                        add(stmt)
                    },
                )
            }

            is BlockStatement ->
                BlockStatement(
                    location,
                    stmt.statements.map {
                        rewriteContinues(location, it, iterators)
                    },
                )

            is IfThenStatement ->
                IfThenStatement(
                    location,
                    stmt.test,
                    BlockStatement(location, listOf(rewriteContinues(location, stmt.thenBlock, iterators))),
                )

            is IfThenElseStatement ->
                IfThenElseStatement(
                    location,
                    stmt.test,
                    BlockStatement(location, listOf(rewriteContinues(location, stmt.thenBlock, iterators))),
                    BlockStatement(location, listOf(rewriteContinues(location, stmt.elseBlock, iterators))),
                )

            else -> stmt
        }
    }
}
