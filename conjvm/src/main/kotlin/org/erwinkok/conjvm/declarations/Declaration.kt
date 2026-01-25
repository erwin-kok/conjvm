package org.erwinkok.conjvm.declarations

import org.erwinkok.conjvm.parser.SourceLocation
import java.util.UUID

class StructDeclaration(val location: SourceLocation, val declarationSpecifier: DeclarationSpecifier, val declarators: List<StructDeclarator>?)
class StructDeclarator(val declarator: Declarator?, val bitWidth: Long?)

sealed class DeclStub(val location: SourceLocation, val scope: Scope, val name: String?) {
    class Typedef(location: SourceLocation, scope: Scope, val declarationSpecifier: DeclarationSpecifier, val declarator: Declarator) : DeclStub(location, scope, declarator.name())
    class Variable(location: SourceLocation, scope: Scope, val declarationSpecifier: DeclarationSpecifier, val declarator: Declarator) : DeclStub(location, scope, declarator.name())
    class Function(location: SourceLocation, scope: Scope, val declarationSpecifier: DeclarationSpecifier, val declarator: Declarator, val parameters: List<Parameter>) : DeclStub(location, scope, declarator.name())
    class Enumerator(location: SourceLocation, scope: Scope, name: String) : DeclStub(location, scope, name)
}

sealed class DeclTagStub(val location: SourceLocation, val scope: Scope, val name: String?) {
    class Struct(location: SourceLocation, scope: Scope, name: String?, val memberScope: Scope) : DeclTagStub(location, scope, name) {
        val uuid = UUID.randomUUID()
        val declarations = mutableListOf<StructDeclaration>()

        fun addStructDeclaration(structDeclaration: StructDeclaration) {
            declarations.add(structDeclaration)
        }
    }

    class Enum(location: SourceLocation, scope: Scope, name: String?) : DeclTagStub(location, scope, name) {
        val uuid = UUID.randomUUID()
        val enumerators = mutableListOf<DeclStub.Enumerator>()

        fun addEnumerator(enumerator: DeclStub.Enumerator) {
            enumerators.add(enumerator)
        }
    }
}
