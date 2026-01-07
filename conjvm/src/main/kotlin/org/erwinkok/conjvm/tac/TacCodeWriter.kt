package org.erwinkok.conjvm.tac

import org.erwinkok.conjvm.tac.instructions.TacFunctionDefinition
import org.erwinkok.conjvm.tac.instructions.TacLabeledInstruction
import java.io.Writer

class TacCodeWriter(val writer: Writer) {
    fun printInstructions(functions: Map<String, TacFunctionDefinition>) {
        functions.forEach { (_, fd) ->
            writer.appendLine("void ${fd.name}(void)")
            writer.appendLine("{")
            fd.instructions.forEach {
                if (it !is TacLabeledInstruction) {
                    writer.append("    ")
                }
                writer.appendLine(it.toString())
            }
            writer.appendLine("}")
        }
    }
}
