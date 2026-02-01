package org.erwinkok.conjvm.linking

import org.erwinkok.conjvm.ast.AstResult
import org.erwinkok.conjvm.parser.ErrorReporter

class Linker(
    val reporter: ErrorReporter,
) {
    fun link(units: List<AstResult>): LinkedProgram {
        val globalSymbolTable = GlobalSymbolTable()

        // Collect all external symbols
        units.forEach { unit ->
            unit.symbolTable.externalVariables.forEach { symbol ->
                globalSymbolTable.addVariable(symbol)
            }
            unit.symbolTable.externalFunctions.forEach { symbol ->
                globalSymbolTable.addFunction(symbol)
            }
        }
        globalSymbolTable.validate(reporter)
        return LinkedProgram(units, globalSymbolTable)
    }
}
