package org.erwinkok.conjvm.translation

import org.erwinkok.conjvm.ast.expressions.AssignmentExpression
import org.erwinkok.conjvm.ast.expressions.AssignmentExpressionType
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
            te
        }
        return TranslationResult(
            allStatements,
            CallExpression(expression.location, expression.function, arguments),
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
        val (ts, te) = translate(e)
        requireNotNull(te)
        return TranslationResult(ts, te)
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
                allStatements.add(
                    VariableDeclarationStatement(
                        location = statement.location,
                        declarationSpecifier = statement.declarationSpecifier,
                        variableDeclarators = listOf(variableDeclarator),
                    ),
                )
            } else {
                val variableDeclarator = VariableDeclarator(
                    location = variableDeclarator.location,
                    declarator = variableDeclarator.declarator,
                    init = null,
                )
                allStatements.add(
                    VariableDeclarationStatement(
                        location = statement.location,
                        declarationSpecifier = statement.declarationSpecifier,
                        variableDeclarators = listOf(variableDeclarator),
                    ),
                )
            }
        }
        return TranslationResult(allStatements, null)
    }

    private fun translateCompoundAssignmentExpression(expression: AssignmentExpression, leftExpression: Expression, rightExpression: Expression): AssignmentExpression {
        if (expression.type == AssignmentExpressionType.Assign) {
            return AssignmentExpression(expression.location, expression.type, leftExpression, rightExpression)
        }
        val binOp = when (expression.type) {
            AssignmentExpressionType.PlusAssign -> BinaryExpressionType.Add
            AssignmentExpressionType.MinusAssign -> BinaryExpressionType.Subtract
            AssignmentExpressionType.AndAssign -> BinaryExpressionType.And
            AssignmentExpressionType.OrAssign -> BinaryExpressionType.InclusiveOr
            AssignmentExpressionType.XorAssign -> BinaryExpressionType.ExclusiveOr
            AssignmentExpressionType.MultiplyAssign -> BinaryExpressionType.Multiply
            AssignmentExpressionType.DivideAssign -> BinaryExpressionType.Divide
            AssignmentExpressionType.ModuloAssign -> BinaryExpressionType.Modulo
            AssignmentExpressionType.RightShiftAssign -> BinaryExpressionType.ShiftRight
            AssignmentExpressionType.LeftShiftAssign -> BinaryExpressionType.ShiftLeft
        }
        val rhs = BinaryExpression(expression.location, binOp, leftExpression, rightExpression)
        return AssignmentExpression(expression.location, AssignmentExpressionType.Assign, leftExpression, rhs)
    }
}
