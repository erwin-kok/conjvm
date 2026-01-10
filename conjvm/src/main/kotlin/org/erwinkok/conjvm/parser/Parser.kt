package org.erwinkok.conjvm.parser

import org.antlr.v4.runtime.CharStreams
import org.antlr.v4.runtime.CommonTokenStream
import org.antlr.v4.runtime.misc.ParseCancellationException
import org.erwinkok.conjvm.CLexer
import org.erwinkok.conjvm.CParser
import org.erwinkok.conjvm.ast.AstBuilder
import org.erwinkok.conjvm.ast.expressions.Expression
import org.erwinkok.conjvm.ast.statements.CompilationUnitStatement
import org.erwinkok.conjvm.ast.statements.Statement
import org.erwinkok.conjvm.declarations.DeclarationListener

class Parser(
    private val errorReporter: ErrorReporter,
) {
    fun parseCompilationUnit(source: SourceFile): CompilationUnitStatement? {
        return try {
            val parser = createParser(source)
            val compilationUnitContext = parser.compilationUnit()
            AstBuilder(errorReporter, source).visit(compilationUnitContext).cast<CompilationUnitStatement>()
        } catch (e: Exception) {
            null
        }
    }

    fun parseStatement(source: SourceFile): Statement? {
        return try {
            val parser = createParser(source)
            val statementContext = parser.statement()
            AstBuilder(errorReporter, source).visit(statementContext).cast<Statement>()
        } catch (e: ParseCancellationException) {
            null
        }
    }

    fun parseExpression(source: SourceFile): Expression? {
        return try {
            val parser = createParser(source)
            val statementContext = parser.expression()
            AstBuilder(errorReporter, source).visit(statementContext).cast<Expression>()
        } catch (e: ParseCancellationException) {
            null
        }
    }

    private fun createParser(source: SourceFile): CParser {
        val input = CharStreams.fromString(source.text)
        val lexer = CLexer(input)
        lexer.removeErrorListeners()
        lexer.addErrorListener(LexerErrorListener(errorReporter, source))
        val tokens = CommonTokenStream(lexer)
        val declarationListener = DeclarationListener(errorReporter, source)
        val parser = CParser(tokens, declarationListener)
        parser.addParseListener(declarationListener)
        parser.removeErrorListeners()
        parser.addErrorListener(ParserErrorListener(errorReporter, source))
        parser.errorHandler = ParserErrorStrategy()
        return parser
    }
}
