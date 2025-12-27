package org.erwinkok.conjvm.parser

import org.antlr.v4.runtime.CharStreams
import org.erwinkok.conjvm.CParser
import org.erwinkok.conjvm.ast.AstBuilder
import org.erwinkok.conjvm.ast.statements.CompilationUnitStatement
import org.erwinkok.conjvm.ast.statements.Statement

object Parser {
    fun parseString(inputText: String): CompilationUnitStatement {
        val inputStream = CharStreams.fromString(inputText)
        val errorReporter = ErrorReporter()
        val lexer = ErrorHandlingLexer(errorReporter, inputStream)
        lexer.removeErrorListeners()
        val tokens = TriviaAwareTokenStream(lexer)
        val parser = CParser(tokens)
        parser.removeErrorListeners()
        parser.errorHandler = ParserErrorStrategy(errorReporter)
        //    parser.isTrace = true
        return AstBuilder(errorReporter).visit(parser.compilationUnit()).cast<CompilationUnitStatement>()
    }

    fun parseFile(inputFile: String): CompilationUnitStatement {
        val inputStream = CharStreams.fromFileName(inputFile)
        val errorReporter = ErrorReporter()
        val lexer = ErrorHandlingLexer(errorReporter, inputStream)
        lexer.removeErrorListeners()
        val tokens = TriviaAwareTokenStream(lexer)
        val parser = CParser(tokens)
        parser.removeErrorListeners()
        parser.errorHandler = ParserErrorStrategy(errorReporter)
        //    parser.isTrace = true
        return AstBuilder(errorReporter).visit(parser.compilationUnit()).cast<CompilationUnitStatement>()
    }

    inline fun <reified T : Statement> parseStatement(inputText: String): T {
        val inputStream = CharStreams.fromString(inputText)
        val errorReporter = ErrorReporter()
        val lexer = ErrorHandlingLexer(errorReporter, inputStream)
        lexer.removeErrorListeners()
        val tokens = TriviaAwareTokenStream(lexer)
        val parser = CParser(tokens)
        parser.removeErrorListeners()
        parser.errorHandler = ParserErrorStrategy(errorReporter)
        return AstBuilder(errorReporter).visit(parser.statement()).cast<T>()
    }
}
