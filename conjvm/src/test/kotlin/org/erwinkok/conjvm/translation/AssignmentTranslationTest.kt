package org.erwinkok.conjvm.translation

import org.junit.jupiter.api.DynamicTest
import org.junit.jupiter.api.TestFactory
import java.util.stream.Stream

class AssignmentTranslationTest {
    @TestFactory
    fun testAssignmentTranslation(): Stream<DynamicTest> {
        return listOf(
            Pair("{ int A = C = *B ^= 5; }", "{ *B = *B ^ 5; C = *B; int A = C; }"),
            Pair("{ int res = DY ^= OPER_I_32(); }", "{ DY = DY ^ OPER_I_32(); int res = DY; }"),
            Pair("{ int A = 5, B = 7; }", "{ int A = 5; int B = 7; }"),
        ).map { (input, expected) ->
            DynamicTest.dynamicTest("Test: $input --> $expected") {
                assertTranslatedAstEquals(input, expected, listOf(::AssignmentTranslation))
            }
        }.stream()
    }
}
