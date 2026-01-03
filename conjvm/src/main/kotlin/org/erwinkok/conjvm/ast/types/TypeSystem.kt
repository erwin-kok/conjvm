package org.erwinkok.conjvm.ast.types

object TypeSystem {
    /* ============================================================
     * Builtin canonical types
     * ============================================================ */

    val intType = QualType(Type.Int(signed = true))
    val longType = QualType(Type.Long(signed = true))
    val voidType = QualType(Type.Void)

    fun validateType(qt: QualType) {
        if (TypeQualifier.RESTRICT in qt.qualifiers && qt.type !is Type.Pointer) {
            throw TypeException("restrict qualifier requires pointer type")
        }
        if (qt.type is Type.Function && qt.qualifiers.isNotEmpty()) {
            throw TypeException("function type may not be qualified")
        }
        if (qt.type is Type.Void) {
            throw TypeException("object declared with type void")
        }
        validateRecursive(qt.type)
    }

    private fun validateRecursive(type: Type) {
        when (type) {
            is Type.Pointer -> {
                validateRecursive(type.pointee.type)
            }

            is Type.Array -> {
                if (type.elementType.type is Type.Function) {
                    throw TypeException("array of functions is illegal")
                }
                validateRecursive(type.elementType.type)
            }

            is Type.Function -> {
                if (type.returnType.type is Type.Array) {
                    throw TypeException("function returning array is illegal")
                }
                validateRecursive(type.returnType.type)
                type.parameters.forEach { validateRecursive(it.type) }
            }

            else -> {}
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
            t.canonical.type == Type.Double
    }

    fun isPointer(t: QualType): Boolean {
        return t.canonical.type is Type.Pointer
    }

    /* ============================================================
     * Lvalue-to-rvalue, array/function decay
     * C11 6.3.2.1
     * ============================================================ */

    fun decay(t: QualType): QualType {
        val ct = t.canonical
        return when (val ty = ct.type) {
            is Type.Array ->
                QualType(Type.Pointer(ty.elementType), emptySet())

            is Type.Function ->
                QualType(Type.Pointer(ct), emptySet())

            else ->
                ct.withoutQualifiers()
        }
    }

    /* ============================================================
     * Integer promotions
     * C11 6.3.1.1
     * ============================================================ */

    fun integerPromote(t: QualType): QualType {
        val ct = t.canonical
        return when (ct.type) {
            is Type.Char,
            is Type.Short,
            -> intType

            else -> ct
        }
    }

    /* ============================================================
     * Usual arithmetic conversions
     * C11 6.3.1.8
     * ============================================================ */

    fun usualArithmeticConversion(a: QualType, b: QualType): QualType {
        val ta = integerPromote(decay(a))
        val tb = integerPromote(decay(b))

        if (!isArithmetic(ta) || !isArithmetic(tb)) {
            return QualType.ErrorType
        }

        if (ta.type == tb.type) {
            return ta
        }

        // Floating dominates integer
        if (ta.type == Type.Double || tb.type == Type.Double) {
            return QualType(Type.Double)
        }

        if (ta.type == Type.Float || tb.type == Type.Float) {
            return QualType(Type.Float)
        }

        // Integer rank + signedness
        return maxIntegerRank(ta, tb)
    }

    private fun maxIntegerRank(a: QualType, b: QualType): QualType {
        val ra = integerRank(a.type)
        val rb = integerRank(b.type)
        return if (ra >= rb) a else b
    }

    private fun integerRank(t: Type): Int {
        return when (t) {
            is Type.Char -> 1
            is Type.Short -> 2
            is Type.Int -> 3
            is Type.Long -> 4
            is Type.LongLong -> 5
            else -> 0
        }
    }

    /* ============================================================
     * Pointer arithmetic
     * ============================================================ */

    fun pointerArithmetic(ptr: QualType, idx: QualType): QualType {
        val p = decay(ptr).canonical
        val i = decay(idx).canonical

        if (p.type is Type.Pointer && isInteger(i)) {
            return p
        }
        return QualType.ErrorType
    }

    fun pointerDifference(a: QualType, b: QualType): QualType {
        val pa = decay(a).canonical
        val pb = decay(b).canonical

        if (pa.type is Type.Pointer &&
            pb.type is Type.Pointer &&
            pa.type.pointee.isCompatibleWith(pb.type.pointee)
        ) {
            return longType // ptrdiff_t approximation
        }
        return QualType.ErrorType
    }

    /* ============================================================
     * Assignment
     * C11 6.5.16.1
     * ============================================================ */

    fun isAssignable(lhs: QualType, rhs: QualType): Boolean {
        val l = lhs.canonical
        val r = rhs.canonical

        if (l.type == Type.Error || r.type == Type.Error) {
            return true
        }

        // Cannot assign to const
        if (TypeQualifier.CONST in l.qualifiers) {
            return false
        }

        // Exact match
        if (l.type == r.type) {
            // cannot drop const on RHS
            if (TypeQualifier.CONST in r.qualifiers && TypeQualifier.CONST !in l.qualifiers) {
                return false
            }
            return true
        }

        // Arithmetic assignment
        if (isArithmetic(l) && isArithmetic(r)) {
            return true
        }

        if (l.type is Type.Pointer && r.type is Type.Pointer) {
            val lp = l.type.pointee.canonical
            val rp = r.type.pointee.canonical

            if (lp.type == Type.Void || rp.type == Type.Void) {
                return true
            }

            if (TypeQualifier.CONST in rp.qualifiers && TypeQualifier.CONST !in lp.qualifiers) {
                return false
            }

            return lp.isCompatibleWith(rp)
        }

        return false
    }

    /* ============================================================
     * Unary operators
     * ============================================================ */

    fun addressOf(t: QualType, isLValue: Boolean): QualType {
        if (!isLValue) return QualType.ErrorType
        return QualType(Type.Pointer(t))
    }

    fun dereference(t: QualType): QualType {
        val ct = decay(t).canonical
        val ptr = ct.type as? Type.Pointer ?: return QualType.ErrorType
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
}
