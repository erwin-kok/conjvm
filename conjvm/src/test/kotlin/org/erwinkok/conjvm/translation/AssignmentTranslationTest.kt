package org.erwinkok.conjvm.translation

import org.junit.jupiter.api.DynamicTest
import org.junit.jupiter.api.TestFactory
import java.util.stream.Stream

class AssignmentTranslationTest {
    @TestFactory
    fun testAssignmentTranslation(): Stream<DynamicTest> {
        return listOf(
            Pair("{ uint A = C = *B ^= 5; }", "{ *B = *B ^ 5; C = *B; uint A = C; }"),
            Pair("{ uint res = DY ^= OPER_I_32(); }", "{ DY = DY ^ OPER_I_32(); uint res = DY; }"),
            Pair("{ uint A = 5, B = 7; }", "{ uint A = 5; uint B = 7; }"),
        ).map { (input, expected) ->
            DynamicTest.dynamicTest("Test: $input --> $expected") {
                assertTranslatedAstEquals(input, expected, listOf(::AssignmentTranslation))
            }
        }.stream()
    }
}
