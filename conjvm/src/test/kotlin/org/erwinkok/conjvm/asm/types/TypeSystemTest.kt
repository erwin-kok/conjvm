package org.erwinkok.conjvm.asm.types

import org.erwinkok.conjvm.ast.types.QualType
import org.erwinkok.conjvm.ast.types.Type
import org.erwinkok.conjvm.ast.types.TypeException
import org.erwinkok.conjvm.ast.types.TypeQualifier
import org.erwinkok.conjvm.ast.types.TypeSystem
import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Assertions.assertFalse
import org.junit.jupiter.api.Assertions.assertNotNull
import org.junit.jupiter.api.Assertions.assertTrue
import org.junit.jupiter.api.Test
import org.junit.jupiter.api.assertThrows

class TypeSystemTest {
    @Test
    fun voidObjectIsRejected() {
        assertThrows<TypeException> {
            TypeSystem.validateType(QualType(Type.Void))
        }
    }

    @Test
    fun restrictRequiresPointer() {
        val t = QualType(Type.Int(true)).with(TypeQualifier.RESTRICT)
        assertThrows<TypeException> {
            TypeSystem.validateType(t)
        }
    }

    @Test
    fun arrayOfFunctionsIsIllegal() {
        val fn = QualType(Type.Function(TypeSystem.intType, emptyList()))
        val arr = QualType(Type.Array(fn, 10))
        assertThrows<TypeException> {
            TypeSystem.validateType(arr)
        }
    }

    @Test
    fun arrayDecaysToPointer() {
        val arr = QualType(Type.Array(TypeSystem.intType, 10))
        val decayed = TypeSystem.decay(arr)
        assertTrue(decayed.type is Type.Pointer)
    }

    @Test
    fun functionDecaysToFunctionPointer() {
        val fn = QualType(Type.Function(TypeSystem.intType, emptyList()))
        val decayed = TypeSystem.decay(fn)
        assertTrue(decayed.type is Type.Pointer)
    }

    @Test
    fun charPromotesToInt() {
        val c = QualType(Type.Char(true))
        assertEquals(TypeSystem.intType, TypeSystem.integerPromote(c))
    }

    @Test
    fun doubleDominatesInt() {
        val r = TypeSystem.usualArithmeticConversion(
            TypeSystem.intType,
            QualType(Type.Double),
        )
        assertEquals(Type.Double, r.type)
    }

    @Test
    fun arithmeticRejectsNonArithmetic() {
        val p = QualType(Type.Pointer(TypeSystem.intType))
        val r = TypeSystem.usualArithmeticConversion(p, TypeSystem.intType)
        assertEquals(Type.Error, r.type)
    }

    @Test
    fun pointerPlusIntegerIsPointer() {
        val p = QualType(Type.Pointer(TypeSystem.intType))
        val r = TypeSystem.pointerArithmetic(p, TypeSystem.intType)
        assertEquals(p.canonical.type, r.type)
    }

    @Test
    fun pointerPlusPointerIsIllegal() {
        val p = QualType(Type.Pointer(TypeSystem.intType))
        val r = TypeSystem.pointerArithmetic(p, p)
        assertEquals(Type.Error, r.type)
    }

    @Test
    fun pointerDifferenceYieldsLong() {
        val p = QualType(Type.Pointer(TypeSystem.intType))
        val r = TypeSystem.pointerDifference(p, p)
        assertEquals(Type.Long(true), r.type)
    }

    @Test
    fun cannotAssignToConst() {
        val lhs = TypeSystem.intType.with(TypeQualifier.CONST)
        val rhs = TypeSystem.intType
        assertFalse(TypeSystem.isAssignable(lhs, rhs))
    }

    @Test
    fun arithmeticAssignmentAllowed() {
        val lhs = TypeSystem.intType
        val rhs = QualType(Type.Double)
        assertTrue(TypeSystem.isAssignable(lhs, rhs))
    }

    @Test
    fun cannotDropConstOnPointee() {
        val lhs = QualType(Type.Pointer(TypeSystem.intType))
        val rhs = QualType(
            Type.Pointer(TypeSystem.intType.with(TypeQualifier.CONST)),
        )
        assertFalse(TypeSystem.isAssignable(lhs, rhs))
    }

    @Test
    fun voidPointerAssignmentAllowed() {
        val vp = QualType(Type.Pointer(TypeSystem.voidType))
        val ip = QualType(Type.Pointer(TypeSystem.intType))
        assertTrue(TypeSystem.isAssignable(vp, ip))
        assertTrue(TypeSystem.isAssignable(ip, vp))
    }

    @Test
    fun addressOfRequiresLValue() {
        val t = TypeSystem.intType
        assertEquals(Type.Error, TypeSystem.addressOf(t, isLValue = false).type)
    }

    @Test
    fun dereferencePointerYieldsPointee() {
        val p = QualType(Type.Pointer(TypeSystem.intType))
        val d = TypeSystem.dereference(p)
        assertEquals(TypeSystem.intType.type, d.type)
    }

    @Test
    fun functionPointerCallable() {
        val fn = QualType(Type.Function(TypeSystem.intType, emptyList()))
        val ptr = QualType(Type.Pointer(fn))
        val f = TypeSystem.asFunctionType(ptr)
        assertNotNull(f)
    }
}
