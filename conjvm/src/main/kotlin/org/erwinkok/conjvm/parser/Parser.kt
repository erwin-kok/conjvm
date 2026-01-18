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
        return createParser(source) { parser, astBuilder ->
            val parseTree = parser.compilationUnit()
            astBuilder.visit(parseTree).cast<CompilationUnitStatement>()
        }
    }

    fun parseStatement(source: SourceFile): Statement? {
        return createParser(source) { parser, astBuilder ->
            val parseTree = parser.statement()
            astBuilder.visit(parseTree).cast<Statement>()
        }
    }

    fun parseExpression(source: SourceFile): Expression? {
        return createParser(source) { parser, astBuilder ->
            val parseTree = parser.expression()
            astBuilder.visit(parseTree).cast<Expression>()
        }
    }

    private fun <T> createParser(source: SourceFile, action: (CParser, AstBuilder) -> T): T? {
        return try {
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
            val astBuilder = AstBuilder(reporter, source, scopeManager)
            action(parser, astBuilder)
        } catch (e: ParseCancellationException) {
            val location = SourceLocation(source, 0, 0, 0)
            reporter.reportException(location, e)
            null
        }
    }
}
