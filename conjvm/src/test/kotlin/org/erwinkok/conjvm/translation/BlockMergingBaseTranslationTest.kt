package org.erwinkok.conjvm.translation

import org.junit.jupiter.api.Disabled
import org.junit.jupiter.api.Test

class BlockMergingBaseTranslationTest {
    @Test
    @Disabled
    fun testAssignment1() {
        assertTranslatedAstEquals("{ int A = C = *B ^= 5; }", "{ int A = C = *B ^= 5; }")
    }

    @Test
    @Disabled
    fun testAssignment2() {
        assertTranslatedAstEquals("{ int res = DY ^= OPER_I_32(); }", "{ int res = DY ^= OPER_I_32(); }")
    }
}
