package org.erwinkok.conjvm.error

class Value private constructor(val value: Any) {
    inline fun <reified T> cast(): T {
        return value as T
    }

    inline fun <reified T> tryCast(): T? {
        return value as? T
    }

    companion object {
        fun of(value: Any): Value {
            return Value(value)
        }
    }
}
