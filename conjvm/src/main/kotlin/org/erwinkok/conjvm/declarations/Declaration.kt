package org.erwinkok.conjvm.declarations

import org.erwinkok.conjvm.ast.types.DeclarationSpecifier
import org.erwinkok.conjvm.ast.types.Declarator
import org.erwinkok.conjvm.parser.SourceLocation

class StructDeclaration(val location: SourceLocation, val declarationSpecifier: DeclarationSpecifier, val declarators: List<StructDeclarator>?)
class StructDeclarator(val declarator: Declarator?, val bitWidth: Long?)
