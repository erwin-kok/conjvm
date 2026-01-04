package org.erwinkok.conjvm.ast

import org.erwinkok.conjvm.ast.expressions.ArrayAccessExpression
import org.erwinkok.conjvm.ast.expressions.AssignmentExpression
import org.erwinkok.conjvm.ast.expressions.BinaryExpression
import org.erwinkok.conjvm.ast.expressions.CallExpression
import org.erwinkok.conjvm.ast.expressions.CastExpression
import org.erwinkok.conjvm.ast.expressions.ConstantIntExpression
import org.erwinkok.conjvm.ast.expressions.ConstantLongExpression
import org.erwinkok.conjvm.ast.expressions.ConstantStringExpression
import org.erwinkok.conjvm.ast.expressions.FieldAccessExpression
import org.erwinkok.conjvm.ast.expressions.Identifier
import org.erwinkok.conjvm.ast.expressions.ParenthesizedExpression
import org.erwinkok.conjvm.ast.expressions.PostfixDecrementExpression
import org.erwinkok.conjvm.ast.expressions.PostfixIncrementExpression
import org.erwinkok.conjvm.ast.expressions.TernaryExpression
import org.erwinkok.conjvm.ast.expressions.UnaryExpression
import org.erwinkok.conjvm.ast.statements.BlockStatement
import org.erwinkok.conjvm.ast.statements.BreakStatement
import org.erwinkok.conjvm.ast.statements.CompilationUnitStatement
import org.erwinkok.conjvm.ast.statements.ContinueStatement
import org.erwinkok.conjvm.ast.statements.ExpressionStatement
import org.erwinkok.conjvm.ast.statements.ForInit
import org.erwinkok.conjvm.ast.statements.ForInitAssignmentExpression
import org.erwinkok.conjvm.ast.statements.ForInitVariableDeclaration
import org.erwinkok.conjvm.ast.statements.ForStatement
import org.erwinkok.conjvm.ast.statements.FunctionDefinitionStatement
import org.erwinkok.conjvm.ast.statements.GotoStatement
import org.erwinkok.conjvm.ast.statements.IfThenElseStatement
import org.erwinkok.conjvm.ast.statements.IfThenStatement
import org.erwinkok.conjvm.ast.statements.LabeledStatement
import org.erwinkok.conjvm.ast.statements.ReturnStatement
import org.erwinkok.conjvm.ast.statements.SwitchCaseStatement
import org.erwinkok.conjvm.ast.statements.SwitchDefaultStatement
import org.erwinkok.conjvm.ast.statements.SwitchStatement
import org.erwinkok.conjvm.ast.statements.VariableDeclarationStatement
import org.erwinkok.conjvm.ast.statements.WhileStatement
import java.io.Writer

class CodeWriter(val writer: Writer) : AstVisitor<String> {
    private var indent: Int = 0

    private val format = HexFormat {
        upperCase = false
        bytes {
            bytesPerLine = 2
            byteSeparator = " "
            bytePrefix = "0x"
            number.removeLeadingZeros = true
            number.prefix = "0x"
        }
    }

    override fun visitArrayAccess(expression: ArrayAccessExpression): String {
        val nodeResult = visit(expression.index)
        return "${expression.base}[$nodeResult]"
    }

    override fun visitAssignment(expression: AssignmentExpression): String {
        val leftResult = visit(expression.leftExpression)
        val rightResult = visit(expression.rightExpression)
        return "$leftResult ${expression.type} $rightResult"
    }

    override fun visitBinary(expression: BinaryExpression): String {
        val leftResult = visit(expression.leftExpression)
        val rightResult = visit(expression.rightExpression)
        return "$leftResult ${expression.type} $rightResult"
    }

    override fun visitCall(expression: CallExpression): String {
        val arguments = expression.arguments.joinToString(", ") { visit(it) }
        return "${expression.function}($arguments)"
    }

    override fun visitCast(expression: CastExpression): String {
        val nodeResult = visit(expression.expression)
        return "(${expression.targetType})$nodeResult"
    }

    override fun visitConstantInt(expression: ConstantIntExpression): String {
        return if (expression.value < 10) {
            expression.value.toString()
        } else {
            expression.value.toHexString(format)
        }
    }

    override fun visitConstantLong(expression: ConstantLongExpression): String {
        return if (expression.value < 10) {
            expression.value.toString()
        } else {
            expression.value.toHexString(format)
        }
    }

    override fun visitConstantString(expression: ConstantStringExpression): String {
        return expression.value
    }

    override fun visitFieldAccess(expression: FieldAccessExpression): String {
        return "${expression.base}.${expression.field}"
    }

    override fun visitIdentifier(identifier: Identifier): String {
        return identifier.name
    }

    override fun visitParenthesized(expression: ParenthesizedExpression): String {
        val nodeResult = visit(expression.expression)
        return "($nodeResult)"
    }

    override fun visitPostfixDecrement(expression: PostfixDecrementExpression): String {
        val nodeResult = visit(expression.expression)
        return "$nodeResult--"
    }

    override fun visitPostfixIncrement(expression: PostfixIncrementExpression): String {
        val nodeResult = visit(expression.expression)
        return "$nodeResult++"
    }

    override fun visitTernary(expression: TernaryExpression): String {
        val testResult = visit(expression.condition)
        val thenResult = visit(expression.thenExpression)
        val elseResult = visit(expression.elseExpression)
        return "$testResult ? $thenResult : $elseResult"
    }

    override fun visitUnary(expression: UnaryExpression): String {
        val nodeResult = visit(expression.operand)
        return "${expression.type}$nodeResult"
    }

    override fun visitBlock(statement: BlockStatement): String {
        appendIndent()
        writer.appendLine("{")
        withIncreasedIdent {
            statement.statements.forEach { visit(it) }
        }
        appendIndent()
        writer.appendLine("}")
        return ""
    }

    override fun visitBreak(statement: BreakStatement): String {
        appendIndent()
        writer.appendLine("break;")
        return ""
    }

    override fun visitCompilationUnit(statement: CompilationUnitStatement): String {
        require(indent == 0)
        statement.functionDefinitions.forEach { visit(it) }
        return ""
    }

    override fun visitContinue(statement: ContinueStatement): String {
        appendIndent()
        writer.appendLine("continue;")
        return ""
    }

    override fun visitExpression(statement: ExpressionStatement): String {
        appendIndent()
        val nodeResult = visit(statement.expression)
        writer.appendLine("$nodeResult;")
        return ""
    }

    override fun visitFor(statement: ForStatement): String {
        val initResult = statement.init?.let { visitForInit(it) } ?: ""
        val testResult = statement.condition?.let { visit(it) } ?: ""
        val iteratorResult = statement.iterators?.joinToString(";") { visit(it) } ?: ""
        appendIndent()
        writer.appendLine("for ($initResult; $testResult; $iteratorResult)")
        writer.appendLine(visit(statement.statements))
        return ""
    }

    override fun visitFunctionDefinition(definition: FunctionDefinitionStatement): String {
        writer.appendLine(definition.toString())
        visit(definition.statements)
        writer.appendLine()
        writer.appendLine()
        return ""
    }

    override fun visitGoto(statement: GotoStatement): String {
        appendIndent()
        writer.appendLine("goto ${statement.label};")
        return ""
    }

    override fun visitIfThenElse(statement: IfThenElseStatement): String {
        appendIndent()
        val testResult = visit(statement.test)
        writer.appendLine("if ($testResult)")
        writer.appendLine(visit(statement.thenBlock))
        appendIndent()
        writer.appendLine("else")
        writer.appendLine(visit(statement.elseBlock))
        return ""
    }

    override fun visitIfThen(statement: IfThenStatement): String {
        appendIndent()
        val testResult = visit(statement.test)
        writer.appendLine("if ($testResult)")
        writer.appendLine(visit(statement.thenBlock))
        return ""
    }

    override fun visitLabeled(statement: LabeledStatement): String {
        appendIndent()
        writer.appendLine("${statement.id}:")
        visit(statement.statement)
        return ""
    }

    override fun visitReturn(statement: ReturnStatement): String {
        appendIndent()
        if (statement.value != null) {
            val nodeResult = visit(statement.value)
            writer.appendLine("return $nodeResult;")
        } else {
            writer.appendLine("return;")
        }
        return ""
    }

    override fun visitSwitch(statement: SwitchStatement): String {
        appendIndent()
        val testResult = visit(statement.test)
        writer.appendLine("switch ($testResult) {")
        withIncreasedIdent {
            statement.sections.forEach { visitSwitchCase(it) }
            statement.defaultSection?.let { visitSwitchDefault(it) }
        }
        appendIndent()
        writer.appendLine("}")
        return ""
    }

    override fun visitVariableDeclaration(statement: VariableDeclarationStatement): String {
        appendIndent()
        val nodeResult = statement.variableDeclarators.joinToString {
            it.toString()
        }
        writer.appendLine("${statement.declarationSpecifier} $nodeResult;")
        return ""
    }

    override fun visitWhile(statement: WhileStatement): String {
        val testResult = visit(statement.condition)
        appendIndent()
        writer.appendLine("while ($testResult)")
        writer.appendLine(visit(statement.statements))
        return ""
    }

    private fun visitSwitchCase(statement: SwitchCaseStatement): String {
        appendIndent()
        val labelResult = visit(statement.test)
        writer.appendLine("case $labelResult:")
        withIncreasedIdent {
            statement.blockStatement.statements.forEach {
                writer.appendLine(visit(it))
            }
        }
        return ""
    }

    private fun visitSwitchDefault(statement: SwitchDefaultStatement): String {
        appendIndent()
        writer.appendLine("default:")
        withIncreasedIdent {
            statement.blockStatement.statements.forEach {
                writer.appendLine(visit(it))
            }
        }
        return ""
    }

    private fun visitForInit(statement: ForInit): String {
        if (statement is ForInitVariableDeclaration) {
            val nodeResult = statement.variableDeclaration.variableDeclarators.joinToString { it.toString() }
            return "${statement.variableDeclaration.declarationSpecifier} $nodeResult"
        } else {
            require(statement is ForInitAssignmentExpression)
            return statement.assignments.joinToString(", ") { visit(it) }
        }
    }

    private inline fun withIncreasedIdent(action: () -> Unit) {
        indent++
        action()
        indent--
    }

    private fun appendIndent() {
        repeat(indent) {
            writer.append("\t")
        }
    }
}
