package org.erwinkok.conjvm.translation

import org.junit.jupiter.api.Test

class BlockMergingBaseTranslationTest {
    @Test
    fun testAssignment1() {
        assertTranslatedAstEquals("{ int A = C = *B ^= 5; }", "{ int A = C = *B ^= 5; }")
    }

    @Test
    fun testAssignment2() {
        assertTranslatedAstEquals("{ int res = DY ^= OPER_I_32(); }", "{ int res = DY ^= OPER_I_32(); }")
    }
}
