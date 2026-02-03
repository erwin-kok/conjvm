package org.erwinkok.conjvm.linking

import org.erwinkok.conjvm.ast.AstResult
import org.erwinkok.conjvm.parser.ErrorReporter

class Linker(
    val reporter: ErrorReporter,
) {
    fun link(units: List<AstResult>): LinkedProgram {
        val globalSymbolTable = GlobalEntityTable()

        // Collect all external symbols
        units.forEach { unit ->
            unit.rootScope.getExternalVariables().forEach { entity ->
                globalSymbolTable.addVariable(entity)
            }
            unit.rootScope.getExternalFunctions().forEach { entity ->
                globalSymbolTable.addFunction(entity)
            }
        }
        globalSymbolTable.validate(reporter)
        return LinkedProgram(units, globalSymbolTable)
    }
}
