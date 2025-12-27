package org.erwinkok.conjvm

import org.erwinkok.conjvm.parser.Parser
import org.erwinkok.conjvm.tac.TacCodeWriter
import org.erwinkok.conjvm.tac.TacTranslation
import org.erwinkok.conjvm.translation.AssignmentTranslation
import org.erwinkok.conjvm.translation.ConvertForToWhileTranslation
import org.erwinkok.conjvm.translation.Translator
import java.io.FileWriter

fun main() {
    val compilationUnit = Parser.parseFile("./input.c")

    var translatedCompilationUnit = Translator.translateStatement(compilationUnit, ConvertForToWhileTranslation())
    translatedCompilationUnit = Translator.translateStatement(translatedCompilationUnit, AssignmentTranslation())

    val translationVisitor = TacTranslation()
    translationVisitor.translateStatement(translatedCompilationUnit)

    FileWriter("./output.c").use {
        val tacCodeWriter = TacCodeWriter(it)
        tacCodeWriter.printFunctions(translationVisitor.functions)
    }
}
