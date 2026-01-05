package org.erwinkok.conjvm.ast.types

import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Assertions.assertFalse
import org.junit.jupiter.api.Assertions.assertTrue
import org.junit.jupiter.api.Test
import org.junit.jupiter.api.assertThrows

class QualTypeTest {
    @Test
    fun canonicalUnwrapsSimpleTypedef() {
        val intType = QualType(Type.Int(signed = true))
        val typedef = QualType(Type.Typedef("T", intType))
        val canonical = typedef.canonical
        assertEquals(intType.type, canonical.type)
        assertTrue(canonical.qualifiers.isEmpty())
    }

    @Test
    fun typedefEqualityUsesUnderlyingCanonicalType() {
        val intType = QualType(Type.Int(true))
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
        val base = QualType(Type.Int(true))
        val typedef = QualType(Type.Typedef("T", base))
            .with(TypeQualifier.CONST)

        val canonical = typedef.canonical

        assertEquals(Type.Int(true), canonical.type)
        assertTrue(TypeQualifier.CONST in canonical.qualifiers)
    }

    @Test
    fun typedefQualifierAppliesToPointerItself() {
        val intType = QualType(Type.Int(true))
        val ptr = QualType(Type.Pointer(intType))
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
        val intPtr = QualType(Type.Pointer(QualType(Type.Int(true))))
        val intPtr2 = QualType(Type.Pointer(QualType(Type.Int(true))))
        val charPtr = QualType(Type.Pointer(QualType(Type.Char(true))))

        assertTrue(intPtr.isCompatibleWith(intPtr2))
        assertFalse(intPtr.isCompatibleWith(charPtr))
    }

    @Test
    fun assignmentRespectsConstQualifier() {
        val lhs = QualType(Type.Int(true))
        val rhsConst = QualType(Type.Int(true)).with(TypeQualifier.CONST)

        assertFalse(lhs.isAssignableFrom(rhsConst))
        assertTrue(rhsConst.isAssignableFrom(lhs))
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
            tag = "S",
            fields = listOf(Field("x", QualType(Type.Int(true)))),
        )
        val s2 = Type.Struct(
            tag = "S",
            fields = listOf(Field("x", QualType(Type.Int(true)))),
        )

        assertEquals(s1, s2)
    }
}
