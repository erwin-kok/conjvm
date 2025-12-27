package org.erwinkok.conjvm.translation

import org.junit.jupiter.api.Test

class BlockMergingBaseTranslationTest {
    class NoOp : BaseTranslationVisitor()

    @Test
    fun testAssignment1() {
        assertTranslatedAstEquals("{ uint A = C = *B ^= 5; }", "{ uint A = C = *B ^= 5; }", NoOp())
    }

    @Test
    fun testAssignment2() {
        assertTranslatedAstEquals("{ uint res = DY ^= OPER_I_32(); }", "{ uint res = DY ^= OPER_I_32(); }", NoOp())
    }
}
