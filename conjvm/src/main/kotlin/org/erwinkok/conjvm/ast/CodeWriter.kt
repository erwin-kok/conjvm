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
import org.erwinkok.conjvm.ast.statements.VariableDeclarator
import org.erwinkok.conjvm.ast.statements.WhileStatement
import java.io.Writer

data class DisplayContext(
    val indent: Int = 0,
) {
    fun increaseIndent() = copy(indent = indent + 1)
}

class CodeWriter(val writer: Writer) : AstVisitor<String, DisplayContext> {
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

    override fun visitArrayAccess(expression: ArrayAccessExpression, ctx: DisplayContext): String {
        val nodeResult = visit(expression.expression, ctx)
        return "${expression.base}[$nodeResult]"
    }

    override fun visitAssignment(expression: AssignmentExpression, ctx: DisplayContext): String {
        val leftResult = visit(expression.leftExpression, ctx)
        val rightResult = visit(expression.rightExpression, ctx)
        return "$leftResult ${expression.type} $rightResult"
    }

    override fun visitBinary(expression: BinaryExpression, ctx: DisplayContext): String {
        val leftResult = visit(expression.leftExpression, ctx)
        val rightResult = visit(expression.rightExpression, ctx)
        return "$leftResult ${expression.type} $rightResult"
    }

    override fun visitCall(expression: CallExpression, ctx: DisplayContext): String {
        val arguments = expression.arguments.joinToString(", ") { visit(it, ctx) }
        return "${expression.name}($arguments)"
    }

    override fun visitCast(expression: CastExpression, ctx: DisplayContext): String {
        val nodeResult = visit(expression.expression, ctx)
        return "(${expression.type})$nodeResult"
    }

    override fun visitConstantInt(expression: ConstantIntExpression, ctx: DisplayContext): String {
        return if (expression.value < 10) {
            expression.value.toString()
        } else {
            expression.value.toHexString(format)
        }
    }

    override fun visitConstantLong(expression: ConstantLongExpression, ctx: DisplayContext): String {
        return if (expression.value < 10) {
            expression.value.toString()
        } else {
            expression.value.toHexString(format)
        }
    }

    override fun visitConstantString(expression: ConstantStringExpression, ctx: DisplayContext): String {
        return expression.value
    }

    override fun visitFieldAccess(expression: FieldAccessExpression, ctx: DisplayContext): String {
        return "${expression.base}.${expression.field}"
    }

    override fun visitIdentifier(identifier: Identifier, ctx: DisplayContext): String {
        return identifier.id
    }

    override fun visitParenthesized(expression: ParenthesizedExpression, ctx: DisplayContext): String {
        val nodeResult = visit(expression.expression, ctx)
        return "($nodeResult)"
    }

    override fun visitPostfixDecrement(expression: PostfixDecrementExpression, ctx: DisplayContext): String {
        val nodeResult = visit(expression.expression, ctx)
        return "$nodeResult--"
    }

    override fun visitPostfixIncrement(expression: PostfixIncrementExpression, ctx: DisplayContext): String {
        val nodeResult = visit(expression.expression, ctx)
        return "$nodeResult++"
    }

    override fun visitTernary(expression: TernaryExpression, ctx: DisplayContext): String {
        val testResult = visit(expression.testExpression, ctx)
        val thenResult = visit(expression.thenExpression, ctx)
        val elseResult = visit(expression.elseExpression, ctx)
        return "$testResult ? $thenResult : $elseResult"
    }

    override fun visitUnary(expression: UnaryExpression, ctx: DisplayContext): String {
        val nodeResult = visit(expression.expression, ctx)
        return "${expression.type}$nodeResult"
    }

    override fun visitBlock(statement: BlockStatement, ctx: DisplayContext): String {
        appendIndent(ctx)
        writer.appendLine("{")
        statement.statements.forEach { visit(it, ctx.increaseIndent()) }
        appendIndent(ctx)
        writer.appendLine("}")
        return ""
    }

    override fun visitBreak(statement: BreakStatement, ctx: DisplayContext): String {
        appendIndent(ctx)
        writer.appendLine("break;")
        return ""
    }

    override fun visitCompilationUnit(statement: CompilationUnitStatement, ctx: DisplayContext): String {
        require(ctx.indent == 0)
        statement.functionDefinitions.forEach { visit(it, ctx) }
        return ""
    }

    override fun visitContinue(statement: ContinueStatement, ctx: DisplayContext): String {
        appendIndent(ctx)
        writer.appendLine("continue;")
        return ""
    }

    override fun visitExpression(statement: ExpressionStatement, ctx: DisplayContext): String {
        appendIndent(ctx)
        val nodeResult = visit(statement.expression, ctx)
        writer.appendLine("$nodeResult;")
        return ""
    }

    override fun visitFor(statement: ForStatement, ctx: DisplayContext): String {
        val initResult = statement.init?.let { visitForInit(it, ctx) } ?: ""
        val testResult = statement.test?.let { visit(it, ctx) } ?: ""
        val iteratorResult = statement.iterators?.joinToString(";") { visit(it, ctx) } ?: ""
        appendIndent(ctx)
        writer.appendLine("for ($initResult; $testResult; $iteratorResult)")
        writer.appendLine(visit(statement.statements, ctx))
        return ""
    }

    override fun visitFunctionDefinition(definition: FunctionDefinitionStatement, ctx: DisplayContext): String {
        writer.appendLine("void ${definition.name}(void)")
        visit(definition.statements, ctx)
        writer.appendLine()
        writer.appendLine()
        return ""
    }

    override fun visitGoto(statement: GotoStatement, ctx: DisplayContext): String {
        appendIndent(ctx)
        writer.appendLine("goto ${statement.label};")
        return ""
    }

    override fun visitIfThenElse(statement: IfThenElseStatement, ctx: DisplayContext): String {
        appendIndent(ctx)
        val testResult = visit(statement.test, ctx)
        writer.appendLine("if ($testResult)")
        writer.appendLine(visit(statement.thenBlock, ctx))
        appendIndent(ctx)
        writer.appendLine("else")
        writer.appendLine(visit(statement.elseBlock, ctx))
        return ""
    }

    override fun visitIfThen(statement: IfThenStatement, ctx: DisplayContext): String {
        appendIndent(ctx)
        val testResult = visit(statement.test, ctx)
        writer.appendLine("if ($testResult)")
        writer.appendLine(visit(statement.thenBlock, ctx))
        return ""
    }

    override fun visitLabeled(statement: LabeledStatement, ctx: DisplayContext): String {
        appendIndent(ctx)
        writer.appendLine("${statement.id}:")
        visit(statement.statement, ctx)
        return ""
    }

    override fun visitReturn(statement: ReturnStatement, ctx: DisplayContext): String {
        appendIndent(ctx)
        if (statement.value != null) {
            val nodeResult = visit(statement.value, ctx)
            writer.appendLine("return $nodeResult;")
        } else {
            writer.appendLine("return;")
        }
        return ""
    }

    override fun visitSwitch(statement: SwitchStatement, ctx: DisplayContext): String {
        appendIndent(ctx)
        val testResult = visit(statement.test, ctx)
        writer.appendLine("switch ($testResult) {")
        val newIdent = ctx.increaseIndent()
        statement.sections.forEach { visitSwitchCase(it, newIdent) }
        statement.defaultSection?.let { visitSwitchDefault(it, newIdent) }
        appendIndent(ctx)
        writer.appendLine("}")
        return ""
    }

    override fun visitVariableDeclaration(statement: VariableDeclarationStatement, ctx: DisplayContext): String {
        appendIndent(ctx)
        val nodeResult = statement.variableDeclarators.joinToString {
            writeVariableDeclarator(it, ctx)
        }
        writer.appendLine("${statement.type} $nodeResult;")
        return ""
    }

    override fun visitWhile(statement: WhileStatement, ctx: DisplayContext): String {
        val testResult = statement.test?.let { visit(it, ctx) } ?: ""
        appendIndent(ctx)
        writer.appendLine("while ($testResult)")
        writer.appendLine(visit(statement.statements, ctx))
        return ""
    }

    private fun writeVariableDeclarator(declarator: VariableDeclarator, ctx: DisplayContext): String {
        val pointer = if (declarator.declarator.pointer) "*" else ""
        val init = declarator.init?.let { visit(it, ctx) }
        return if (init != null) {
            "$pointer${declarator.declarator.name} = $init"
        } else {
            "$pointer${declarator.declarator.name}"
        }
    }

    private fun visitSwitchCase(statement: SwitchCaseStatement, ctx: DisplayContext): String {
        appendIndent(ctx)
        val labelResult = visit(statement.test, ctx)
        writer.appendLine("case $labelResult:")
        val newIdent = ctx.increaseIndent()
        statement.blockStatement.statements.forEach {
            writer.appendLine(visit(it, newIdent))
        }
        return ""
    }

    private fun visitSwitchDefault(statement: SwitchDefaultStatement, ctx: DisplayContext): String {
        appendIndent(ctx)
        writer.appendLine("default:")
        val newIdent = ctx.increaseIndent()
        statement.blockStatement.statements.forEach {
            writer.appendLine(visit(it, newIdent))
        }
        return ""
    }

    private fun visitForInit(statement: ForInit, ctx: DisplayContext): String {
        if (statement is ForInitVariableDeclaration) {
            val nodeResult = statement.variableDeclaration.variableDeclarators.joinToString { writeVariableDeclarator(it, ctx) }
            return if (statement.variableDeclaration.type != null) {
                "${statement.variableDeclaration.type} $nodeResult"
            } else {
                nodeResult
            }
        } else {
            require(statement is ForInitAssignmentExpression)
            return statement.assignments.joinToString(", ") { visit(it, ctx) }
        }
    }

    private fun appendIndent(ctx: DisplayContext) {
        repeat(ctx.indent) {
            writer.append("\t")
        }
    }
}
