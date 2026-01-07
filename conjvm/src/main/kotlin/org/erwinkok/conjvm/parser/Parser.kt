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
import org.erwinkok.conjvm.ast.types.SymbolTable

class Parser(
    private val errorReporter: ErrorReporter,
    private val symbolTable: SymbolTable,
) {
    fun parseCompilationUnit(source: SourceFile): CompilationUnitStatement? {
        return try {
            val parser = createParser(source)
            val compilationUnitContext = parser.compilationUnit()
            AstBuilder(errorReporter, source, symbolTable).visit(compilationUnitContext).cast<CompilationUnitStatement>()
        } catch (_: ParseCancellationException) {
            null
        }
    }

    fun parseStatement(source: SourceFile): Statement? {
        return try {
            val parser = createParser(source)
            val statementContext = parser.statement()
            AstBuilder(errorReporter, source, symbolTable).visit(statementContext).cast<Statement>()
        } catch (_: ParseCancellationException) {
            null
        }
    }

    fun parseExpression(source: SourceFile): Expression? {
        return try {
            val parser = createParser(source)
            val statementContext = parser.expression()
            AstBuilder(errorReporter, source, symbolTable).visit(statementContext).cast<Expression>()
        } catch (_: ParseCancellationException) {
            null
        }
    }

    private fun createParser(source: SourceFile): CParser {
        val input = CharStreams.fromString(source.text)
        val lexer = CLexer(input, symbolTable)
        lexer.removeErrorListeners()
        lexer.addErrorListener(LexerErrorListener(errorReporter, source))
        val tokens = CommonTokenStream(lexer)
        val parser = CParser(tokens)
        parser.removeErrorListeners()
        parser.addErrorListener(ParserErrorListener(errorReporter, source))
        parser.errorHandler = ParserErrorStrategy()
        return parser
    }
}
