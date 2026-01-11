package org.erwinkok.conjvm.declarations

import org.erwinkok.conjvm.parser.ErrorReporter

class Scope(
    val reporter: ErrorReporter,
    val parent: Scope? = null,
)
