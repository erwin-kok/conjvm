package org.erwinkok.conjvm.types

import org.erwinkok.conjvm.declarations.TypeQualifier
import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Assertions.assertFalse
import org.junit.jupiter.api.Assertions.assertNotEquals
import org.junit.jupiter.api.Assertions.assertTrue
import org.junit.jupiter.api.Test
import org.junit.jupiter.api.assertThrows
import java.util.UUID

class QualTypeTest {
    @Test
    fun canonicalUnwrapsSimpleTypedef() {
        val intType = intType()
        val typedef = QualType(Type.Typedef("T", intType))
        val canonical = typedef.canonical
        assertEquals(intType.type, canonical.type)
        assertTrue(canonical.qualifiers.isEmpty())
    }

    @Test
    fun typedefEqualityUsesUnderlyingCanonicalType() {
        val intType = intType()
        val t1 = Type.Typedef("A", intType)
        val t2 = Type.Typedef("B", intType)
        assertEquals(t1, t2)
        assertEquals(t1.hashCode(), t2.hashCode())
    }

    @Test
    fun circularTypedefThrows() {
        val placeholder = QualType(Type.Error)

        val typedefA = Type.Typedef("A", placeholder)
        val typedefB = Type.Typedef("B", QualType(typedefA))

        // patch A to point to B
        val circularA = QualType(Type.Typedef("A", QualType(typedefB)))

        assertThrows<TypeException> { circularA.canonical }
    }

    @Test
    fun typedefQualifierMergesForNonPointer() {
        val base = intType()
        val typedef = QualType(Type.Typedef("T", base))
            .with(TypeQualifier.CONST)

        val canonical = typedef.canonical

        assertEquals(Type.Int(true), canonical.type)
        assertTrue(TypeQualifier.CONST in canonical.qualifiers)
    }

    @Test
    fun typedefQualifierAppliesToPointerItself() {
        val intType = intType()
        val ptr = ptr(intType)
        val typedef = QualType(Type.Typedef("P", ptr))
            .with(TypeQualifier.CONST)

        val canonical = typedef.canonical

        // const applies to pointer, not pointee
        assertTrue(TypeQualifier.CONST in canonical.qualifiers)
        assertTrue(canonical.type is Type.Pointer)
        assertTrue((canonical.type as Type.Pointer).pointee.qualifiers.isEmpty())
    }

    @Test
    fun pointerCompatibilityChecksPointee() {
        val intPtr = ptr(QualType(Type.Int(true)))
        val intPtr2 = ptr(QualType(Type.Int(true)))
        val charPtr = ptr(QualType(Type.Char(true)))

        assertTrue(intPtr.isCompatibleWith(intPtr2))
        assertFalse(intPtr.isCompatibleWith(charPtr))
    }

    @Test
    fun assignmentRespectsConstQualifier() {
        val lhs = intType() // non-const
        val rhsConst = intType().with(TypeQualifier.CONST)
        assertTrue(TypeSystem.isAssignable(lhs, rhsConst)) // legal in C
        assertFalse(TypeSystem.isAssignable(rhsConst, lhs)) // cannot assign to const
    }

    @Test
    fun functionCanonicalizesReturnAndParameters() {
        val typedefInt = QualType(Type.Typedef("T", QualType(Type.Int(true))))
        val fn = QualType(
            Type.Function(
                returnType = typedefInt,
                parameters = listOf(typedefInt),
            ),
        )

        val canonical = fn.canonical
        val fnType = canonical.type as Type.Function

        assertEquals(Type.Int(true), fnType.returnType.type)
        assertEquals(Type.Int(true), fnType.parameters.first().type)
    }

    @Test
    fun structEqualityIsStructural() {
        val s1 = Type.Struct(
            UUID.randomUUID(),
            tag = "S",
            fields = listOf(Field("x", QualType(Type.Int(true)))),
        )
        val s2 = Type.Struct(
            UUID.randomUUID(),
            tag = "S",
            fields = listOf(Field("x", QualType(Type.Int(true)))),
        )
        assertNotEquals(s1, s2)
    }

    @Test
    fun arrayDecayProducesPointer() {
        val intArray = QualType(Type.Array(intType(), 10))
        val decayed = TypeSystem.decay(intArray)
        assertTrue(decayed.type is Type.Pointer)
        val ptr = decayed.type as Type.Pointer
        assertEquals(Type.Int(true), ptr.pointee.type)
    }

    @Test
    fun pointerArithmeticOnlyWithInteger() {
        val ptr = ptr(QualType(Type.Int(true)))
        val idx = intType()
        val res = TypeSystem.pointerArithmetic(ptr, idx)
        assertEquals(ptr.canonical, res)

        val invalidIdx = ptr(QualType(Type.Int(true)))
        val err = TypeSystem.pointerArithmetic(ptr, invalidIdx)
        assertEquals(Type.Error, err.type)
    }

    @Test
    fun pointerDifferenceType() {
        val a = ptr(QualType(Type.Int(true)))
        val b = ptr(QualType(Type.Int(true)))
        val diff = TypeSystem.pointerDifference(a, b)
        assertEquals(TypeSystem.longType.type, diff.type)

        val c = ptr(QualType(Type.Char(true)))
        val err = TypeSystem.pointerDifference(a, c)
        assertEquals(Type.Error, err.type)
    }

    @Test
    fun integerPromotionWorks() {
        val c = QualType(Type.Char(true))
        val s = QualType(Type.Short(true))
        val promotedC = TypeSystem.integerPromote(c)
        val promotedS = TypeSystem.integerPromote(s)
        assertEquals(TypeSystem.intType, promotedC)
        assertEquals(TypeSystem.intType, promotedS)

        val i = intType()
        assertEquals(i, TypeSystem.integerPromote(i))
    }

    @Test
    fun usualArithmeticConversionTest() {
        val i = intType()
        val u = uintType()
        val f = QualType(Type.Float)
        val d = QualType(Type.Double)

        // int + unsigned int → unsigned
        assertEquals(u, TypeSystem.usualArithmeticConversion(i, u))

        // float + int → float
        assertEquals(f.type, TypeSystem.usualArithmeticConversion(f, i).type)

        // double + float → double
        assertEquals(d.type, TypeSystem.usualArithmeticConversion(d, f).type)

        // pointer + int → error
        val ptr = ptr(i)
        assertEquals(Type.Error, TypeSystem.usualArithmeticConversion(ptr, i).type)
    }

    @Test
    fun illegalArrayOfVoidThrows() {
        val arr = QualType(Type.Array(QualType(Type.Void), 10))
        assertThrows<TypeException> { TypeSystem.validateObjectType(arr) }
    }

    @Test
    fun illegalFunctionReturningArrayThrows() {
        val fn = QualType(Type.Function(QualType(Type.Array(intType(), 5)), listOf()))
        assertThrows<TypeException> { TypeSystem.validateWellFormed(fn) }
    }

    @Test
    fun functionDecayToPointer() {
        val fn = QualType(Type.Function(intType(), listOf()))
        val decayed = TypeSystem.decay(fn)
        assertTrue(decayed.type is Type.Pointer)
        val ptr = decayed.type as Type.Pointer
        assertTrue(ptr.pointee.type is Type.Function)
    }

    @Test
    fun nestedTypedefCanonicalization() {
        val base = intType()
        val td1 = QualType(Type.Typedef("A", base))
        val td2 = QualType(Type.Typedef("B", td1))
        val td3 = QualType(Type.Typedef("C", td2))

        assertEquals(base.type, td3.canonical.type)
    }

    private fun intType() = QualType(Type.Int(true))
    private fun uintType() = QualType(Type.Int(false))
    private fun ptr(to: QualType) = QualType(Type.Pointer(to))
}
