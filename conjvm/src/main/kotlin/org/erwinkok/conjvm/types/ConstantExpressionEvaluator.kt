package org.erwinkok.conjvm.types

import org.antlr.v4.runtime.ParserRuleContext
import org.erwinkok.conjvm.CBaseVisitor
import org.erwinkok.conjvm.CParser
import org.erwinkok.conjvm.declarations.Scope
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.SourceFile
import org.erwinkok.conjvm.utils.ParserReporting

class ConstantExpressionEvaluator(
    override val reporter: ErrorReporter,
    override val source: SourceFile,
    private val scope: Scope,
) : CBaseVisitor<Long?>(),
    ParserReporting {
    override fun visitConstant_expression(ctx: CParser.Constant_expressionContext): Long? {
        return visit(ctx.conditional_expression())
    }

    override fun visitExpression(ctx: CParser.ExpressionContext): Long? {
        return visit(ctx.assignment_expression())
    }

    override fun visitSimpleAssignExpr(ctx: CParser.SimpleAssignExprContext): Long? {
        return visit(ctx.conditional_expression())
    }

    override fun visitCompoundAssignExpr(ctx: CParser.CompoundAssignExprContext): Long? {
        reporter.reportError(ctx.location, "invalid constant expression: ${ctx.text}")
        return null
    }

    override fun visitSimpleConditional(ctx: CParser.SimpleConditionalContext): Long? {
        return visit(ctx.logical_or_expression())
    }

    override fun visitCompoundConditional(ctx: CParser.CompoundConditionalContext): Long? {
        val cond = visit(ctx.test) ?: return null
        return if (cond != 0L) {
            visit(ctx.thenExpr)
        } else {
            visit(ctx.elseExpr)
        }
    }

    override fun visitLogical_or_expression(ctx: CParser.Logical_or_expressionContext): Long? {
        return ctx.op.zip(ctx.right)
            .fold(visit(ctx.left)) { acc, (_, right) ->
                val leftVal = acc ?: return null
                val rightVal = visit(right) ?: return null
                if (leftVal != 0L || rightVal != 0L) {
                    1L
                } else {
                    0L
                }
            }
    }

    override fun visitLogical_and_expression(ctx: CParser.Logical_and_expressionContext): Long? {
        return ctx.op.zip(ctx.right)
            .fold(visit(ctx.left)) { acc, (_, right) ->
                val leftVal = acc ?: return null
                val rightVal = visit(right) ?: return null
                if (leftVal != 0L && rightVal != 0L) {
                    1L
                } else {
                    0L
                }
            }
    }

    override fun visitInclusive_or_expression(ctx: CParser.Inclusive_or_expressionContext): Long? {
        return ctx.op.zip(ctx.right)
            .fold(visit(ctx.left)) { acc, (_, right) ->
                val leftVal = acc ?: return null
                val rightVal = visit(right) ?: return null
                leftVal or rightVal
            }
    }

    override fun visitExclusive_or_expression(ctx: CParser.Exclusive_or_expressionContext): Long? {
        return ctx.op.zip(ctx.right)
            .fold(visit(ctx.left)) { acc, (_, right) ->
                val leftVal = acc ?: return null
                val rightVal = visit(right) ?: return null
                leftVal xor rightVal
            }
    }

    override fun visitAnd_expression(ctx: CParser.And_expressionContext): Long? {
        return ctx.op.zip(ctx.right)
            .fold(visit(ctx.left)) { acc, (_, right) ->
                val leftVal = acc ?: return null
                val rightVal = visit(right) ?: return null
                leftVal and rightVal
            }
    }

    override fun visitEquality_expression(ctx: CParser.Equality_expressionContext): Long? {
        return ctx.op.zip(ctx.right)
            .fold(visit(ctx.left)) { acc, (op, right) ->
                val leftVal = acc ?: return null
                val rightVal = visit(right) ?: return null
                when (op.text) {
                    "==" -> if (leftVal == rightVal) 1L else 0L
                    "!=" -> if (leftVal != rightVal) 1L else 0L
                    else -> return null
                }
            }
    }

    override fun visitRelational_expression(ctx: CParser.Relational_expressionContext): Long? {
        return ctx.op.zip(ctx.right)
            .fold(visit(ctx.left)) { acc, (op, right) ->
                val leftVal = acc ?: return null
                val rightVal = visit(right) ?: return null
                when (op.text) {
                    "<" -> if (leftVal < rightVal) 1L else 0L
                    ">" -> if (leftVal > rightVal) 1L else 0L
                    "<=" -> if (leftVal <= rightVal) 1L else 0L
                    ">=" -> if (leftVal >= rightVal) 1L else 0L
                    else -> return null
                }
            }
    }

    override fun visitShift_expression(ctx: CParser.Shift_expressionContext): Long? {
        return ctx.op.zip(ctx.right)
            .fold(visit(ctx.left)) { acc, (op, right) ->
                val leftVal = acc ?: return null
                val rightVal = visit(right) ?: return null
                when (op.text) {
                    "<<" -> leftVal shl rightVal.toInt()
                    ">>" -> leftVal shr rightVal.toInt()
                    else -> return null
                }
            }
    }

    override fun visitAdditive_expression(ctx: CParser.Additive_expressionContext): Long? {
        return ctx.op.zip(ctx.right)
            .fold(visit(ctx.left)) { acc, (op, right) ->
                val leftVal = acc ?: return null
                val rightVal = visit(right) ?: return null
                when (op.text) {
                    "+" -> leftVal + rightVal
                    "-" -> leftVal - rightVal
                    else -> return null
                }
            }
    }

    override fun visitMultiplicative_expression(ctx: CParser.Multiplicative_expressionContext): Long? {
        return ctx.op.zip(ctx.right)
            .fold(visit(ctx.left)) { acc, (op, right) ->
                val leftVal = acc ?: return null
                val rightVal = visit(right) ?: return null
                when (op.text) {
                    "*" -> leftVal * rightVal
                    "/" -> {
                        if (rightVal == 0L) {
                            reporter.reportError(ctx.location, "division by zero")
                            return null
                        }
                        leftVal / rightVal
                    }

                    "%" -> {
                        if (rightVal == 0L) {
                            reporter.reportError(ctx.location, "modulo by zero")
                            return null
                        }
                        leftVal % rightVal
                    }

                    else -> return null
                }
            }
    }

    override fun visitCastExpr(ctx: CParser.CastExprContext): Long? {
        // Note: In constant expressions, casts do not change the value
        return visit(ctx.cast_expression())
    }

    override fun visitSimpleCast(ctx: CParser.SimpleCastContext): Long? {
        return visit(ctx.unary_expression())
    }

    override fun visitUnary_expression(ctx: CParser.Unary_expressionContext): Long? {
        val coreExpr = visit(ctx.unary_core()) ?: return null
        return ctx.prefix_operator()
            .asReversed()
            .fold(coreExpr) { _, op ->
                when (op) {
                    is CParser.PrefixSizeofContext -> error("sizeof operator is currently not supported")
                    else -> {
                        reporter.reportError(ctx.location, "invalid constant expression: ${ctx.text}")
                        return null
                    }
                }
            }
    }

    override fun visitCompoundUnaryCore(ctx: CParser.CompoundUnaryCoreContext): Long? {
        val value = visit(ctx.cast_expression()) ?: return null
        return when (ctx.unary_operator().text) {
            "+" -> value
            "-" -> -value
            "~" -> value.inv()
            "!" -> if (value == 0L) 1L else 0L
            else -> {
                reporter.reportError(
                    ctx.location,
                    "operator '${ctx.unary_operator().text}' not allowed in constant expression",
                )
                null
            }
        }
    }

    override fun visitSimpleUnaryCore(ctx: CParser.SimpleUnaryCoreContext): Long? {
        return visit(ctx.postfix_expression())
    }

    override fun visitSizeofUnaryCore(ctx: CParser.SizeofUnaryCoreContext): Long? {
        error("sizeof operator is currently not supported")
    }

    override fun visitPostfix_expression(ctx: CParser.Postfix_expressionContext): Long? {
        return if (!ctx.postfix_suffix().isNullOrEmpty()) {
            reporter.reportError(ctx.location, "invalid constant expression: ${ctx.text}")
            null
        } else {
            visit(ctx.primary_expression())
        }
    }

    override fun visitPrimaryId(ctx: CParser.PrimaryIdContext): Long? {
        val name = ctx.Identifier().text
        val enumValue = scope.lookupEnumConstant(name)
        return if (enumValue != null) {
            enumValue
        } else {
            reporter.reportError(ctx.location, "'$name' is not a constant expression")
            null
        }
    }

    override fun visitPrimaryConstant(ctx: CParser.PrimaryConstantContext): Long? {
        return parseConstant(ctx, ctx.Constant().text)
    }

    override fun visitPrimaryStringLiteral(ctx: CParser.PrimaryStringLiteralContext): Long? {
        reporter.reportError(ctx.location, "invalid constant expression: ${ctx.text}")
        return null
    }

    override fun visitPrimaryParenthesized(ctx: CParser.PrimaryParenthesizedContext): Long? {
        return visit(ctx.expression())
    }

    private fun parseConstant(ctx: ParserRuleContext, text: String): Long? {
        return try {
            when {
                text.startsWith("0x") || text.startsWith("0X") -> {
                    text.substring(2).filter { it.isLetterOrDigit() }.toLong(16)
                }

                text.startsWith("0") && text.length > 1 && text[1].isDigit() -> {
                    text.filter { it.isDigit() }.toLong(8)
                }

                text.startsWith("'") -> {
                    // Character constant
                    parseCharacterConstant(text)
                }

                else -> {
                    text.filter { it.isDigit() }.toLong(10)
                }
            }
        } catch (_: NumberFormatException) {
            reporter.reportError(ctx.location, "invalid integer constant: $text")
            null
        }
    }

    private fun parseCharacterConstant(text: String): Long {
        val content = text.substring(1, text.length - 1)
        return when {
            content.startsWith("\\") -> {
                when (content[1]) {
                    'n' -> '\n'.code.toLong()
                    't' -> '\t'.code.toLong()
                    'r' -> '\r'.code.toLong()
                    '0' -> 0L
                    '\\' -> '\\'.code.toLong()
                    '\'' -> '\''.code.toLong()
                    else -> content[1].code.toLong()
                }
            }

            else -> content[0].code.toLong()
        }
    }
}
