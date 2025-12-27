package org.erwinkok.conjvm.translation

import org.erwinkok.conjvm.ast.statements.BlockStatement
import org.erwinkok.conjvm.parser.Parser
import org.junit.jupiter.api.Assertions.assertEquals

fun assertTranslatedAstEquals(inputText: String, expectedText: String, translationVisitor: TranslationVisitor) {
    val statement = Parser.parseStatement<BlockStatement>(inputText)
    val translatedStatement = Translator.translateStatement<BlockStatement>(statement, translationVisitor)
    val expectedStatement = Parser.parseStatement<BlockStatement>(expectedText)
    assertEquals(expectedStatement, translatedStatement)
}
