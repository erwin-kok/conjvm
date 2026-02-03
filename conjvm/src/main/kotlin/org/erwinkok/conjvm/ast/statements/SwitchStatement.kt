package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.expressions.ConstantExpression
import org.erwinkok.conjvm.ast.expressions.Expression
import org.erwinkok.conjvm.parser.SourceLocation

abstract class SwitchSection

data class SwitchCaseStatement(
    val location: SourceLocation,
    val condition: ConstantExpression,
    val block: BlockStatement,
) : SwitchSection() {
    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is SwitchCaseStatement) {
            return false
        }
        if (condition != other.condition) return false
        if (block != other.block) return false
        return true
    }

    override fun hashCode(): Int {
        var result = condition.hashCode()
        result = 31 * result + block.hashCode()
        return result
    }
}

data class SwitchDefaultStatement(val location: SourceLocation, val blockStatement: BlockStatement) : SwitchSection() {
    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is SwitchDefaultStatement) {
            return false
        }
        if (blockStatement != other.blockStatement) return false
        return true
    }

    override fun hashCode(): Int {
        return blockStatement.hashCode()
    }
}

class SwitchStatement(
    location: SourceLocation,
    val condition: Expression,
    val sections: List<SwitchCaseStatement>,
    val defaultSection: SwitchDefaultStatement?,
) : Statement(location) {
    override fun <R> accept(visitor: AstStatementVisitor<R>): R = visitor.visitSwitch(this)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is SwitchStatement) {
            return false
        }
        if (condition != other.condition) return false
        if (sections != other.sections) return false
        if (defaultSection != other.defaultSection) return false
        return true
    }

    override fun hashCode(): Int {
        var result = condition.hashCode()
        result = 31 * result + sections.hashCode()
        result = 31 * result + defaultSection.hashCode()
        return result
    }
}
