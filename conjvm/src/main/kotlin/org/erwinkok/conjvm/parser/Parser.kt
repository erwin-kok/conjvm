package org.erwinkok.conjvm.parser

import org.antlr.v4.runtime.CharStreams
import org.antlr.v4.runtime.CommonTokenStream
import org.antlr.v4.runtime.misc.ParseCancellationException
import org.erwinkok.conjvm.CLexer
import org.erwinkok.conjvm.CParser
import org.erwinkok.conjvm.compiler.CompilerPhase
import org.erwinkok.conjvm.declarations.DeclarationListener
import org.erwinkok.conjvm.declarations.DeclarationResult
import org.erwinkok.conjvm.declarations.EntityTable
import org.erwinkok.conjvm.declarations.Scope
import org.erwinkok.conjvm.declarations.ScopeKind

class Parser(
    override val reporter: ErrorReporter,
    override val source: SourceFile,
) : CompilerPhase {
    private val entityTable = EntityTable()
    private val rootScope = Scope(ScopeKind.FILE, null)
    private val parser = createParser()

    fun parseCompilationUnit(): DeclarationResult? {
        return try {
            val parseTree = parser.compilationUnit()
            DeclarationResult(
                sourceFile = source,
                entityTable = entityTable,
                rootScope = rootScope,
                parseTree = parseTree,
            )
        } catch (e: ParseCancellationException) {
            val location = SourceLocation(source, 0, 0, 0)
            reporter.reportException(location, e)
            null
        }
    }

    fun parseStatement(): DeclarationResult? {
        return try {
            val parseTree = parser.statement()
            DeclarationResult(
                sourceFile = source,
                entityTable = entityTable,
                rootScope = rootScope,
                parseTree = parseTree,
            )
        } catch (e: ParseCancellationException) {
            val location = SourceLocation(source, 0, 0, 0)
            reporter.reportException(location, e)
            null
        }
    }

    fun parseExpression(): DeclarationResult? {
        return try {
            val parseTree = parser.expression()
            DeclarationResult(
                sourceFile = source,
                entityTable = entityTable,
                rootScope = rootScope,
                parseTree = parseTree,
            )
        } catch (e: ParseCancellationException) {
            val location = SourceLocation(source, 0, 0, 0)
            reporter.reportException(location, e)
            null
        }
    }

    private fun createParser(): CParser {
        val input = CharStreams.fromString(source.text)
        val lexer = CLexer(input)
        lexer.removeErrorListeners()
        lexer.addErrorListener(LexerErrorListener(reporter, source))
        val tokens = CommonTokenStream(lexer)
        val declarationListener = DeclarationListener(reporter, source, entityTable, rootScope)
        val parser = CParser(tokens, declarationListener)
        parser.addParseListener(declarationListener)
        parser.removeErrorListeners()
        parser.addErrorListener(ParserErrorListener(reporter, source))
        parser.errorHandler = ParserErrorStrategy()
        return parser
    }
}
