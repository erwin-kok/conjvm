package org.erwinkok.conjvm.ast.statements

import org.erwinkok.conjvm.ast.AstStatementVisitor
import org.erwinkok.conjvm.ast.SourceLocation
import org.erwinkok.conjvm.ast.expressions.ConstantExpression
import org.erwinkok.conjvm.ast.expressions.Expression

abstract class SwitchSection

data class SwitchCaseStatement(val location: SourceLocation, val test: ConstantExpression, val blockStatement: BlockStatement) : SwitchSection() {
    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is SwitchCaseStatement) {
            return false
        }

        if (test != other.test) return false
        if (blockStatement != other.blockStatement) return false

        return true
    }

    override fun hashCode(): Int {
        var result = test.hashCode()
        result = 31 * result + blockStatement.hashCode()
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

class SwitchStatement(location: SourceLocation, val test: Expression, val sections: List<SwitchCaseStatement>, val defaultSection: SwitchDefaultStatement?) : Statement(location) {
    override fun <R> accept(visitor: AstStatementVisitor<R>): R = visitor.visitSwitch(this)

    override fun equals(other: Any?): Boolean {
        if (other === this) {
            return true
        }
        if (other !is SwitchStatement) {
            return false
        }

        if (test != other.test) return false
        if (sections != other.sections) return false
        if (defaultSection != other.defaultSection) return false

        return true
    }

    override fun hashCode(): Int {
        var result = test.hashCode()
        result = 31 * result + sections.hashCode()
        result = 31 * result + defaultSection.hashCode()
        return result
    }
}
