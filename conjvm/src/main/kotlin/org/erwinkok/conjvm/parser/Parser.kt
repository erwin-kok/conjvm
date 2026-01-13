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
import org.erwinkok.conjvm.declarations.ScopeManager

class Parser(
    private val reporter: ErrorReporter,
) {
    private val scopeManager = ScopeManager()

    fun parseCompilationUnit(source: SourceFile): CompilationUnitStatement? {
        return try {
            val parser = createParser(source)
            val compilationUnitContext = parser.compilationUnit()
            AstBuilder(reporter, source).visit(compilationUnitContext).cast<CompilationUnitStatement>()
        } catch (e: ParseCancellationException) {
            val location = SourceLocation(source, 0, 0, 0)
            reporter.reportException(location, e)
            null
        }
    }

    fun parseStatement(source: SourceFile): Statement? {
        return try {
            val parser = createParser(source)
            val statementContext = parser.statement()
            AstBuilder(reporter, source).visit(statementContext).cast<Statement>()
        } catch (e: ParseCancellationException) {
            val location = SourceLocation(source, 0, 0, 0)
            reporter.reportException(location, e)
            null
        }
    }

    fun parseExpression(source: SourceFile): Expression? {
        return try {
            val parser = createParser(source)
            val statementContext = parser.expression()
            AstBuilder(reporter, source).visit(statementContext).cast<Expression>()
        } catch (e: ParseCancellationException) {
            val location = SourceLocation(source, 0, 0, 0)
            reporter.reportException(location, e)
            null
        }
    }

    private fun createParser(source: SourceFile): CParser {
        val input = CharStreams.fromString(source.text)
        val lexer = CLexer(input)
        lexer.removeErrorListeners()
        lexer.addErrorListener(LexerErrorListener(reporter, source))
        val tokens = CommonTokenStream(lexer)
        val declarationListener = DeclarationListener(reporter, source, scopeManager)
        val parser = CParser(tokens, declarationListener)
        parser.addParseListener(declarationListener)
        parser.removeErrorListeners()
        parser.addErrorListener(ParserErrorListener(reporter, source))
        parser.errorHandler = ParserErrorStrategy()
        return parser
    }
}
