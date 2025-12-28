package org.erwinkok.conjvm.translation

import org.erwinkok.conjvm.ast.expressions.AssignmentExpression
import org.erwinkok.conjvm.ast.expressions.BinaryExpression
import org.erwinkok.conjvm.ast.expressions.BinaryExpressionType
import org.erwinkok.conjvm.ast.expressions.CallExpression
import org.erwinkok.conjvm.ast.expressions.Expression
import org.erwinkok.conjvm.ast.expressions.ParenthesizedExpression
import org.erwinkok.conjvm.ast.expressions.PostfixDecrementExpression
import org.erwinkok.conjvm.ast.expressions.PostfixIncrementExpression
import org.erwinkok.conjvm.ast.statements.BlockStatement
import org.erwinkok.conjvm.ast.statements.ExpressionStatement
import org.erwinkok.conjvm.ast.statements.Statement
import org.erwinkok.conjvm.ast.statements.VariableDeclarationStatement
import org.erwinkok.conjvm.ast.statements.VariableDeclarator

class AssignmentTranslation : BaseTranslationVisitor() {
    override fun translateAssignment(expression: AssignmentExpression): TranslationResult {
        val lte = translate(expression.leftExpression)
        val rte = translate(expression.rightExpression)
        requireNotNull(lte.expression)
        requireNotNull(rte.expression)
        val ex = translateCompoundAssignmentExpression(expression, lte.expression, rte.expression)
        return TranslationResult(
            lte.statements + rte.statements + ExpressionStatement(expression.location, ex),
            lte.expression,
        )
    }

    override fun translateExpression(statement: ExpressionStatement): TranslationResult {
        val allStatements = mutableListOf<Statement>()
        val expression = statement.expression
        val (ts, te) = translate(expression)
        requireNotNull(te)
        allStatements.addAll(ts)
        if (te is CallExpression || te is PostfixIncrementExpression || te is PostfixDecrementExpression) {
            allStatements.add(ExpressionStatement(statement.location, te))
        }
        return TranslationResult(allStatements, null)
    }

    override fun translateCall(expression: CallExpression): TranslationResult {
        val allStatements = mutableListOf<Statement>()
        val arguments = expression.arguments.map {
            val (ts, te) = translate(it)
            allStatements.addAll(ts)
            requireNotNull(te)
            if (te is ParenthesizedExpression) {
                te.expression
            } else {
                te
            }
        }
        return TranslationResult(
            allStatements,
            CallExpression(expression.location, expression.name, arguments),
        )
    }

    override fun translateBlock(statement: BlockStatement): TranslationResult {
        val allStatements = mutableListOf<Statement>()
        statement.statements.map {
            val (ts, te) = translate(it)
            allStatements.addAll(ts)
            require(te == null)
        }
        return TranslationResult(
            listOf(BlockStatement(statement.location, allStatements)),
            null,
        )
    }

    override fun translateParenthesized(expression: ParenthesizedExpression): TranslationResult {
        val e = expression.expression
        return if (e is AssignmentExpression) {
            val (ts, te) = translate(e)
            requireNotNull(te)
            return TranslationResult(ts, ParenthesizedExpression(expression.location, te))
        } else {
            TranslationResult(emptyList(), expression)
        }
    }

    override fun translateVariableDeclaration(statement: VariableDeclarationStatement): TranslationResult {
        val allStatements = mutableListOf<Statement>()
        for (variableDeclarator in statement.variableDeclarators) {
            if (variableDeclarator.init != null) {
                val (assignStatements, expression) = translate(variableDeclarator.init)
                allStatements.addAll(assignStatements)
                val variableDeclarator = VariableDeclarator(
                    location = variableDeclarator.location,
                    declarator = variableDeclarator.declarator,
                    init = expression,
                )
                allStatements.add(VariableDeclarationStatement(location = statement.location, type = statement.type, variableDeclarators = listOf(variableDeclarator)))
            } else {
                val variableDeclarator = VariableDeclarator(
                    location = variableDeclarator.location,
                    declarator = variableDeclarator.declarator,
                    init = null,
                )
                allStatements.add(VariableDeclarationStatement(location = statement.location, type = statement.type, variableDeclarators = listOf(variableDeclarator)))
            }
        }
        return TranslationResult(allStatements, null)
    }

    private fun translateCompoundAssignmentExpression(expression: AssignmentExpression, leftExpression: Expression, rightExpression: Expression): AssignmentExpression {
        if (expression.op == "=") {
            return AssignmentExpression(expression.location, expression.op, leftExpression, rightExpression)
        }
        val binOp = when (expression.op) {
            "+=" -> BinaryExpressionType.Add
            "-=" -> BinaryExpressionType.Subtract
            "&=" -> BinaryExpressionType.And
            "|=" -> BinaryExpressionType.InclusiveOr
            "^=" -> BinaryExpressionType.ExclusiveOr
            "*=" -> BinaryExpressionType.Multiply
            "/=" -> BinaryExpressionType.Divide
            "%=" -> BinaryExpressionType.Modulo
            ">>=" -> BinaryExpressionType.ShiftRight
            "<<=" -> BinaryExpressionType.ShiftLeft
            else -> error("Unexpected operator: ${expression.op}")
        }
        val rhs = BinaryExpression(expression.location, binOp, leftExpression, rightExpression)
        return AssignmentExpression(expression.location, "=", leftExpression, rhs)
    }
}
