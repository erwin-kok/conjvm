package org.erwinkok.conjvm.parser

import org.antlr.v4.runtime.CharStreams
import org.antlr.v4.runtime.CommonTokenStream
import org.antlr.v4.runtime.misc.ParseCancellationException
import org.erwinkok.conjvm.CLexer
import org.erwinkok.conjvm.CParser
import org.erwinkok.conjvm.ast.AstBuilder
import org.erwinkok.conjvm.ast.statements.CompilationUnitStatement
import org.erwinkok.conjvm.ast.statements.Statement
import org.erwinkok.conjvm.ast.types.SymbolTable
import java.io.InputStream

object Parser {
    fun parseSource(source: SourceFile, symbolTable: SymbolTable): CompilationUnitStatement? {
        val diagnostics = mutableListOf<Diagnostic>()
        val input = CharStreams.fromString(source.text)
        val lexer = CLexer(input, symbolTable)
        lexer.removeErrorListeners()
        lexer.addErrorListener(LexerErrorListener(source, diagnostics))
        val tokens = CommonTokenStream(lexer)
        val parser = CParser(tokens)
        parser.removeErrorListeners()
        parser.addErrorListener(ParserErrorListener(source, diagnostics))
        parser.errorHandler = ParserErrorStrategy()
        return try {
            AstBuilder(ErrorReporter()).visit(parser.compilationUnit()).cast<CompilationUnitStatement>()
        } catch (_: ParseCancellationException) {
            val renderer = DiagnosticRenderer(source)
            diagnostics.forEach {
                println(renderer.render(it))
            }
            null
        }
    }

    fun parseString(inputText: String, symbolTable: SymbolTable): CompilationUnitStatement {
        val inputStream = CharStreams.fromString(inputText)
        val errorReporter = ErrorReporter()
        val lexer = ErrorHandlingLexer(errorReporter, inputStream, symbolTable)
        lexer.removeErrorListeners()
        val tokens = TriviaAwareTokenStream(lexer)
        val parser = CParser(tokens)
        parser.removeErrorListeners()
        parser.errorHandler = ParserErrorStrategy()
        //    parser.isTrace = true
        return AstBuilder(errorReporter).visit(parser.compilationUnit()).cast<CompilationUnitStatement>()
    }

    fun parseStream(inputStream: InputStream, symbolTable: SymbolTable): CompilationUnitStatement {
        val inputStream = CharStreams.fromStream(inputStream)
        val errorReporter = ErrorReporter()
        val lexer = ErrorHandlingLexer(errorReporter, inputStream, symbolTable)
        lexer.removeErrorListeners()
        val tokens = TriviaAwareTokenStream(lexer)
        val parser = CParser(tokens)
        parser.removeErrorListeners()
        parser.errorHandler = ParserErrorStrategy()
        //    parser.isTrace = true
        return AstBuilder(errorReporter).visit(parser.compilationUnit()).cast<CompilationUnitStatement>()
    }

    inline fun <reified T : Statement> parseStatement(inputText: String): T {
        val inputStream = CharStreams.fromString(inputText)
        val errorReporter = ErrorReporter()
        val lexer = ErrorHandlingLexer(errorReporter, inputStream, SymbolTable())
        lexer.removeErrorListeners()
        val tokens = TriviaAwareTokenStream(lexer)
        val parser = CParser(tokens)
        parser.removeErrorListeners()
        parser.errorHandler = ParserErrorStrategy()
        return AstBuilder(errorReporter).visit(parser.statement()).cast<T>()
    }
}
