package org.erwinkok.conjvm.ast.expressions

import org.erwinkok.conjvm.parser.SourceLocation
import org.erwinkok.conjvm.types.QualType

abstract class ConstantExpression(location: SourceLocation, type: QualType) : Expression(location, type)
