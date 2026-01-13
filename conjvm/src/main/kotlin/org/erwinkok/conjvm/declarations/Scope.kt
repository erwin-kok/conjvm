package org.erwinkok.conjvm.declarations

import org.erwinkok.conjvm.ast.types.DeclarationSpecifier
import org.erwinkok.conjvm.ast.types.Declarator
import org.erwinkok.conjvm.ast.types.Parameter
import org.erwinkok.conjvm.parser.SourceLocation
import java.util.UUID

enum class ScopeKind {
    FILE,
    FUNCTION,
    BLOCK,
    STRUCT,
    FOR,
}

sealed class DeclStub(val location: SourceLocation, val scope: Scope, val name: String?) {
    class TypedefDecl(location: SourceLocation, scope: Scope, val declarationSpecifier: DeclarationSpecifier, val declarator: Declarator) : DeclStub(location, scope, declarator.name())
    class VariableDecl(location: SourceLocation, scope: Scope, val declarationSpecifier: DeclarationSpecifier, val declarator: Declarator) : DeclStub(location, scope, declarator.name())
    class FunctionDecl(location: SourceLocation, scope: Scope, val declarationSpecifier: DeclarationSpecifier, val declarator: Declarator, val parameters: List<Parameter>) : DeclStub(location, scope, declarator.name())
    class EnumeratorDecl(location: SourceLocation, scope: Scope, name: String) : DeclStub(location, scope, name)
}

sealed class DeclTagStub(val location: SourceLocation, val scope: Scope, val name: String?) {
    class StructDecl(location: SourceLocation, scope: Scope, name: String?, val memberScope: Scope) : DeclTagStub(location, scope, name) {
        val uuid = UUID.randomUUID()
        val declarations = mutableListOf<StructDeclaration>()

        fun addStructDeclaration(structDeclaration: StructDeclaration) {
            declarations.add(structDeclaration)
        }
    }

    class EnumDecl(location: SourceLocation, scope: Scope, name: String?) : DeclTagStub(location, scope, name) {
        val uuid = UUID.randomUUID()
        val enumerators = mutableListOf<DeclStub.EnumeratorDecl>()

        fun addEnumerator(enumerator: DeclStub.EnumeratorDecl) {
            enumerators.add(enumerator)
        }
    }
}

class Scope(
    val kind: ScopeKind,
    val parent: Scope? = null,
    val children: MutableList<Scope> = mutableListOf(),
) {
    override fun toString(): String {
        return "$kind"
    }
}
