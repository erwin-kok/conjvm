package org.erwinkok.conjvm.types

import org.erwinkok.conjvm.declarations.TypeQualifier

object TypeSystem {
    /* ============================================================
     * Builtin canonical types
     * ============================================================ */

    val intType = QualType(Type.Int(signed = true))
    val longType = QualType(Type.Long(signed = true))
    val voidType = QualType(Type.Void)

    fun validateWellFormed(qt: QualType) {
        if (TypeQualifier.RESTRICT in qt.qualifiers && qt.type !is Type.Pointer) {
            throw TypeException("restrict qualifier requires pointer type")
        }
        if (qt.type is Type.Function && qt.qualifiers.isNotEmpty()) {
            throw TypeException("function type may not be qualified")
        }
        validateRecursive(qt.type)
    }

    fun validateObjectType(qt: QualType) {
        validateWellFormed(qt)
        if (qt.type == Type.Void) {
            throw TypeException("object declared with type void")
        }
    }

    /* ============================================================
     * Classification helpers
     * ============================================================ */

    fun isInteger(t: QualType): Boolean {
        return when (t.canonical.type) {
            is Type.Char,
            is Type.Short,
            is Type.Int,
            is Type.Long,
            is Type.LongLong,
            -> true

            else -> false
        }
    }

    fun isArithmetic(t: QualType): Boolean {
        return isInteger(t) ||
            t.canonical.type == Type.Float ||
            t.canonical.type == Type.Double ||
            t.canonical.type == Type.LongDouble
    }

    fun isPointer(t: QualType): Boolean {
        return t.canonical.type is Type.Pointer
    }

    /* ============================================================
     * Lvalue-to-rvalue, array/function decay
     * ============================================================ */

    fun decay(t: QualType): QualType {
        val ct = t.canonical
        return when (val ty = ct.type) {
            is Type.Array -> QualType(Type.Pointer(ty.elementType), emptySet())
            is Type.Function -> QualType(Type.Pointer(QualType(ty, emptySet())), emptySet())
            else -> ct.withoutQualifiers()
        }
    }

    /* ============================================================
     * Integer promotions
     * ============================================================ */

    fun integerPromote(t: QualType): QualType {
        val ct = t.canonical
        return when (ct.type) {
            is Type.Char,
            is Type.Short,
            is Type.Bool,
            -> intType

            else -> ct
        }
    }

    /* ============================================================
     * Usual arithmetic conversions
     * ============================================================ */

    fun usualArithmeticConversion(a: QualType, b: QualType): QualType {
        val ta = integerPromote(decay(a))
        val tb = integerPromote(decay(b))

        if (!isArithmetic(ta) || !isArithmetic(tb)) {
            return QualType.ErrorType
        }

        // Floating
        if (ta.type == Type.LongDouble || tb.type == Type.LongDouble) {
            return QualType(Type.LongDouble)
        }

        if (ta.type == Type.Double || tb.type == Type.Double) {
            return QualType(Type.Double)
        }

        if (ta.type == Type.Float || tb.type == Type.Float) {
            return QualType(Type.Float)
        }

        // Integers
        if (ta.type == tb.type) {
            return ta
        }

        val sa = isSigned(ta.type)
        val sb = isSigned(tb.type)
        val ra = integerRank(ta.type)
        val rb = integerRank(tb.type)

        // Same signedness
        if (sa == sb) {
            return if (ra >= rb) ta else tb
        }

        val signed = if (sa) ta else tb
        val unsigned = if (sa) tb else ta

        return when {
            integerRank(unsigned.type) >= integerRank(signed.type) -> unsigned
            canRepresentAllValues(signed.type, unsigned.type) -> signed
            else -> makeUnsignedVersion(signed)
        }
    }

    /* ============================================================
     * Pointer arithmetic
     * ============================================================ */

    fun pointerArithmetic(ptr: QualType, idx: QualType): QualType {
        val p = ptr.canonical
        val i = idx.canonical
        if (p.type is Type.Pointer && isInteger(i) && p.type.pointee.type != Type.Void) {
            return p
        }
        return QualType.ErrorType
    }

    fun pointerDifference(a: QualType, b: QualType): QualType {
        val pa = a.canonical
        val pb = b.canonical

        if (pa.type is Type.Pointer && pb.type is Type.Pointer && pa.type.pointee.isCompatibleWith(pb.type.pointee)) {
            return longType // ptrdiff_t approximation
        }
        return QualType.ErrorType
    }

    /* ============================================================
     * Assignment
     * ============================================================ */

    fun isAssignable(lhs: QualType, rhs: QualType): Boolean {
        val l = lhs.canonical
        val r = rhs.canonical

        // If either type is error, allow to prevent cascading
        if (l.type == Type.Error || r.type == Type.Error) {
            return true
        }

        // LHS must be modifiable
        if (TypeQualifier.CONST in l.qualifiers) {
            return false
        }

        // Arithmetic types
        if (isArithmetic(l) && isArithmetic(r)) {
            // Allowed as long as LHS is not const
            return true
        }

        // Pointer assignment
        if (l.type is Type.Pointer && r.type is Type.Pointer) {
            val lp = l.type.pointee.canonical
            val rp = r.type.pointee.canonical

            // void* is compatible
            if (lp.type == Type.Void || rp.type == Type.Void) {
                return lp.qualifiers.containsAll(rp.qualifiers)
            }

            // Pointee types must be compatible
            if (!lp.isCompatibleWith(rp)) {
                return false
            }

            // Cannot drop qualifiers
            if (!lp.qualifiers.containsAll(rp.qualifiers)) {
                return false
            }
            return true
        }
        return false
    }

    /* ============================================================
     * Unary operators
     * ============================================================ */

    fun addressOf(t: QualType, isLValue: Boolean): QualType {
        if (!isLValue) {
            return QualType.ErrorType
        }
        return QualType(Type.Pointer(t))
    }

    fun dereference(t: QualType): QualType {
        val ct = decay(t).canonical
        val ptr = ct.type as? Type.Pointer ?: return QualType.ErrorType
        if (ptr.pointee.type == Type.Void) {
            return QualType.ErrorType
        }
        return ptr.pointee
    }

    /* ============================================================
     * Function calls
     * ============================================================ */

    fun asFunctionType(t: QualType): Type.Function? {
        val ct = decay(t).canonical
        return when (val ty = ct.type) {
            is Type.Function -> ty
            is Type.Pointer -> ty.pointee.type as? Type.Function
            else -> null
        }
    }

    private fun isSigned(t: Type): Boolean = when (t) {
        is Type.Char -> t.signed
        is Type.Short -> t.signed
        is Type.Int -> t.signed
        is Type.Long -> t.signed
        is Type.LongLong -> t.signed
        else -> false
    }

    private fun validateRecursive(type: Type) {
        when (type) {
            is Type.Pointer -> validateWellFormed(type.pointee)

            is Type.Array -> {
                if (type.elementType.type is Type.Function) {
                    throw TypeException("array of functions is illegal")
                }
                if (type.elementType.type is Type.Void) {
                    throw TypeException("array of void is illegal")
                }
                validateWellFormed(type.elementType)
            }

            is Type.Function -> {
                if (type.returnType.type is Type.Function) {
                    throw TypeException("function returning function is illegal")
                }
                if (type.returnType.type is Type.Array) {
                    throw TypeException("function returning array is illegal")
                }

                validateWellFormed(type.returnType)
                type.parameters.forEach { validateWellFormed(it) }

                validateFunctionParameters(type.parameters)
            }

            else -> {}
        }
    }

    private fun validateFunctionParameters(params: List<QualType>) {
        if (params.isEmpty()) {
            return
        }
        if (params.size == 1 && params[0].type == Type.Void) {
            return
        }
        if (params.any { it.type == Type.Void }) {
            throw TypeException("void must be the only parameter")
        }
    }

    private fun canRepresentAllValues(signed: Type, unsigned: Type): Boolean {
        val rs = integerRank(signed)
        val ru = integerRank(unsigned)
        // If signed has strictly greater rank, it must be wider
        return rs > ru
    }

    private fun makeUnsignedVersion(t: QualType): QualType = when (t.type) {
        is Type.Int -> QualType(Type.Int(false))
        is Type.Long -> QualType(Type.Long(false))
        is Type.LongLong -> QualType(Type.LongLong(false))
        else -> t
    }

    private fun integerRank(t: Type): Int {
        return when (t) {
            is Type.Bool -> 0
            is Type.Char -> 1
            is Type.Short -> 2
            is Type.Int -> 3
            is Type.Long -> 4
            is Type.LongLong -> 5
            else -> -1
        }
    }
}
