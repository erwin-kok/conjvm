package org.erwinkok.conjvm.ast.translation

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
import org.erwinkok.conjvm.ast.statements.SwitchStatement
import org.erwinkok.conjvm.ast.statements.WhileStatement
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.SourceLocation

class ConvertForToWhileTranslation(reporter: ErrorReporter) : BaseTranslationVisitor(reporter) {
    override fun translateFor(statement: ForStatement): TranslationResult {
        val allStatements = mutableListOf<Statement>()

        // Translate the for-loop initialization
        allStatements.addAll(translateForInit(statement.location, statement.init))

        // Translate the condition (or default to 'true')
        val (cts, cte) = translateCondition(statement.location, statement.condition)
        allStatements.addAll(cts)
        requireNotNull(cte)

        // Translate iterators
        val translatedIterators = translateIterators(statement.location, statement.iterators)

        // Rewrite the loop body to handle continue statements
        val rewrittenBody = rewriteContinues(statement.location, statement.statements, translatedIterators)

        val whileBodyStatements = mutableListOf<Statement>()
        whileBodyStatements.add(rewrittenBody)
        whileBodyStatements.addAll(translatedIterators)

        val whileStatement = WhileStatement(
            statement.location,
            cte,
            BlockStatement(statement.location, whileBodyStatements),
        )
        allStatements.add(whileStatement)
        return TranslationResult(listOf(BlockStatement(statement.location, allStatements)), null)
    }

    private fun translateForInit(location: SourceLocation, statement: ForInit?): List<Statement> {
        return when (statement) {
            is ForInitAssignmentExpression -> {
                val allStatements = mutableListOf<Statement>()
                statement.assignments.map {
                    val (ts, te) = translate(it)
                    requireNotNull(te)
                    allStatements.addAll(ts)
                    allStatements.add(ExpressionStatement(location, te))
                }
                allStatements
            }

            is ForInitVariableDeclaration -> {
                val (ts, te) = translate(statement.variableDeclaration)
                require(te == null)
                ts
            }

            null -> emptyList()
        }
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
        iterators?.forEach {
            val (ts, te) = translate(it)
            requireNotNull(te)
            allStatements.addAll(ts)
            allStatements.add(ExpressionStatement(location, te))
        }
        return allStatements
    }

    private fun rewriteContinues(location: SourceLocation, stmt: Statement, iterators: List<Statement>): Statement {
        if (iterators.isEmpty()) {
            return stmt
        }
        return when (stmt) {
            is ContinueStatement -> {
                BlockStatement(location, iterators + stmt)
            }

            is BlockStatement ->
                BlockStatement(
                    location,
                    stmt.statements.map { rewriteContinues(location, it, iterators) },
                )

            is IfThenStatement ->
                IfThenStatement(
                    location,
                    stmt.test,
                    toBlockStatement(rewriteContinues(location, stmt.thenBlock, iterators)),
                )

            is IfThenElseStatement ->
                IfThenElseStatement(
                    location,
                    stmt.test,
                    toBlockStatement(rewriteContinues(location, stmt.thenBlock, iterators)),
                    toBlockStatement(rewriteContinues(location, stmt.elseBlock, iterators)),
                )

            is WhileStatement,
            is ForStatement,
            is SwitchStatement,
            -> stmt

            else -> stmt
        }
    }

    private fun toBlockStatement(statement: Statement): BlockStatement {
        return statement as? BlockStatement ?: BlockStatement(statement.location, listOf(statement))
    }
}
