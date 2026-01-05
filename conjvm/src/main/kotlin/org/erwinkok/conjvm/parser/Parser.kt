package org.erwinkok.conjvm.parser

import org.antlr.v4.runtime.CharStreams
import org.antlr.v4.runtime.CommonTokenStream
import org.antlr.v4.runtime.misc.ParseCancellationException
import org.erwinkok.conjvm.CLexer
import org.erwinkok.conjvm.CParser
import org.erwinkok.conjvm.ast.AstBuilder
import org.erwinkok.conjvm.ast.statements.BlockStatement
import org.erwinkok.conjvm.ast.statements.CompilationUnitStatement
import org.erwinkok.conjvm.ast.types.SymbolTable

class Parser(
    private val errorReporter: ErrorReporter,
) {
    fun parseSource(source: SourceFile, symbolTable: SymbolTable): CompilationUnitStatement? {
        return try {
            val parser = createParser(source, symbolTable)
            AstBuilder(errorReporter, source).visit(parser.compilationUnit()).cast<CompilationUnitStatement>()
        } catch (_: ParseCancellationException) {
            null
        }
    }

    fun parseBlock(source: SourceFile, symbolTable: SymbolTable): BlockStatement? {
        return try {
            val parser = createParser(source, symbolTable)
            AstBuilder(errorReporter, source).visit(parser.statement()).cast<BlockStatement>()
        } catch (_: ParseCancellationException) {
            null
        }
    }

    private fun createParser(source: SourceFile, symbolTable: SymbolTable): CParser {
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
