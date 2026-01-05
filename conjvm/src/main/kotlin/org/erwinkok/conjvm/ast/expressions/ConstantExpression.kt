package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.parser.SourceLocation

abstract class ConstantExpression(location: SourceLocation) : Expression(location)
