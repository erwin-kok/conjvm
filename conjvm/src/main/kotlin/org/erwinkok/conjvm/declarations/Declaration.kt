package org.erwinkok.conjvm.declarations

import org.erwinkok.conjvm.ast.types.DeclarationSpecifier
import org.erwinkok.conjvm.ast.types.Declarator

class StructDeclaration(val declarationSpecifier: DeclarationSpecifier, val declarators: List<StructDeclarator>?)
class StructDeclarator(val declarator: Declarator?, val bitWidth: Long?)

class Enumerator(val name: String, val value: Long?)
