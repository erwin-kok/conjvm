package org.erwinkok.conjvm.tac

import org.erwinkok.conjvm.tac.instructions.TacFunctionDefinition
import org.erwinkok.conjvm.tac.instructions.TacInstruction
import org.erwinkok.conjvm.tac.instructions.TacLabeledInstruction
import java.io.Writer

class TacCodeWriter(val writer: Writer) {
    fun printInstructions(functions: Map<String, TacFunctionDefinition>) {
        functions.forEach { (_, fd) ->
            writer.appendLine("void ${fd.name}(void)")
            writer.appendLine("{")
            printInstructions(fd.instructions)
            writer.appendLine()
            writer.appendLine("}")
        }
    }

    fun printInstructions(instructions: List<TacInstruction>) {
        instructions.forEachIndexed { index, instruction ->
            if (index != 0) {
                writer.appendLine()
            }
            if (instruction !is TacLabeledInstruction) {
                writer.append("    ")
            }
            writer.append(instruction.toString())
        }
    }
}
