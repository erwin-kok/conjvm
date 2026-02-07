package org.erwinkok.conjvm.declarations

import org.erwinkok.conjvm.CBaseVisitor
import org.erwinkok.conjvm.CParser
import org.erwinkok.conjvm.CParser.DeclSpecFuncSpecContext
import org.erwinkok.conjvm.CParser.DeclSpecTypeQualContext
import org.erwinkok.conjvm.CParser.DeclSpecTypeSpecContext
import org.erwinkok.conjvm.CParser.StorageClassSpecContext
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.SourceFile
import org.erwinkok.conjvm.utils.ParserReporting
import org.erwinkok.conjvm.utils.Value

class DeclarationParser(
    override val reporter: ErrorReporter,
    override val source: SourceFile,
) : CBaseVisitor<Value>(),
    ParserReporting {
    override fun visitDeclaration_specifiers(ctx: CParser.Declaration_specifiersContext): Value {
        val storage = mutableSetOf<StorageClass>()
        val typeSpecs = mutableListOf<TypeSpec>()
        val qualifiers = mutableSetOf<TypeQualifier>()
        val functionSpecs = mutableSetOf<FunctionSpec>()
        ctx.declaration_specifier().forEach {
            when (it) {
                is StorageClassSpecContext -> storage += parseStorageClassSpec(it.storage_class_specifier())
                is DeclSpecTypeSpecContext -> typeSpecs += parseTypeSpec(it.type_specifier())
                is DeclSpecTypeQualContext -> qualifiers += parseTypeQualifier(it.type_qualifier())
                is DeclSpecFuncSpecContext -> functionSpecs += parseFunctionSpec(it.function_specifier())
            }
        }
        return Value.of(DeclarationSpecifier(storage, typeSpecs, qualifiers, functionSpecs))
    }

    override fun visitDeclaration_specifiers_2(ctx: CParser.Declaration_specifiers_2Context): Value {
        val storage = mutableSetOf<StorageClass>()
        val typeSpecs = mutableListOf<TypeSpec>()
        val qualifiers = mutableSetOf<TypeQualifier>()
        val functionSpecs = mutableSetOf<FunctionSpec>()
        ctx.declaration_specifier().forEach {
            when (it) {
                is StorageClassSpecContext -> storage += parseStorageClassSpec(it.storage_class_specifier())
                is DeclSpecTypeSpecContext -> typeSpecs += parseTypeSpec(it.type_specifier())
                is DeclSpecTypeQualContext -> qualifiers += parseTypeQualifier(it.type_qualifier())
                is DeclSpecFuncSpecContext -> functionSpecs += parseFunctionSpec(it.function_specifier())
            }
        }
        return Value.of(DeclarationSpecifier(storage, typeSpecs, qualifiers, functionSpecs))
    }

    override fun visitInit_declarator_list(ctx: CParser.Init_declarator_listContext): Value {
        return Value.of(ctx.init_declarator().map { visit(it).cast<InitDeclarator>() })
    }

    override fun visitInit_declarator(ctx: CParser.Init_declaratorContext): Value {
        val initializer = ctx.initializer()?.assignment_expression()
        return Value.of(InitDeclarator(visit(ctx.declarator()).cast<Declarator>(), initializer))
    }

    override fun visitSpecifier_qualifier_list(ctx: CParser.Specifier_qualifier_listContext): Value {
        val typeSpecs = mutableListOf<TypeSpec>()
        val qualifiers = mutableSetOf<TypeQualifier>()
        ctx.type_specifier().forEach { typeSpecs += parseTypeSpec(it) }
        ctx.type_qualifier().forEach { qualifiers += parseTypeQualifier(it) }
        return Value.of(DeclarationSpecifier(emptySet(), typeSpecs, qualifiers, emptySet()))
    }

    override fun visitStruct_declarator_list(ctx: CParser.Struct_declarator_listContext): Value {
        return Value.of(ctx.struct_declarator().map { visit(it).cast<StructDeclarator>() })
    }

    override fun visitStruct_declarator(ctx: CParser.Struct_declaratorContext): Value {
        val declarator = ctx.declarator()?.let { visit(it).cast<Declarator>() }
        return Value.of(StructDeclarator(declarator, ctx.constant_expression()))
    }

    override fun visitDeclarator(ctx: CParser.DeclaratorContext): Value {
        val base = visit(ctx.direct_declarator()).cast<Declarator>()
        val pointerQualifiers = ctx.pointer()?.let { visit(it).cast<List<List<TypeQualifier>>>() } ?: emptyList()
        val declarator = pointerQualifiers.foldRight(base) { qualifiers, inner ->
            Declarator.PointerDeclarator(ctx.location, qualifiers.toSet(), inner)
        }
        return Value.of(declarator)
    }

    override fun visitDirectDeclIdentifier(ctx: CParser.DirectDeclIdentifierContext): Value {
        return Value.of(Declarator.IdentifierDeclarator(ctx.location, ctx.Identifier().text))
    }

    override fun visitDirectDeclParenthesized(ctx: CParser.DirectDeclParenthesizedContext): Value {
        return visit(ctx.declarator())
    }

    override fun visitDirectDeclFunction(ctx: CParser.DirectDeclFunctionContext): Value {
        val inner = visit(ctx.direct_declarator()).cast<Declarator>()
        val params = ctx.parameter_type_list()?.let { visit(it).cast<List<Parameter>>() } ?: emptyList()
        return Value.of(Declarator.FunctionDeclarator(ctx.location, inner, params))
    }

    override fun visitDirectDeclArray(ctx: CParser.DirectDeclArrayContext): Value {
        val inner = visit(ctx.direct_declarator()).cast<Declarator>()
        return Value.of(Declarator.ArrayDeclarator(ctx.location, inner, ctx.assignment_expression()))
    }

    override fun visitDirectDeclBitField(ctx: CParser.DirectDeclBitFieldContext): Value {
        val name = ctx.Identifier().text
        val width = ctx.DigitSequence().text.toInt()
        return Value.of(Declarator.BitFieldDeclarator(ctx.location, name, width))
    }

    override fun visitPointer(ctx: CParser.PointerContext): Value {
        val pointer = ctx.pointer_part().map { visit(it).cast<List<TypeQualifier>>() }
        return Value.of(pointer)
    }

    override fun visitPointer_part(ctx: CParser.Pointer_partContext): Value {
        return Value.of(ctx.type_qualifier().map { parseTypeQualifier(it) })
    }

    override fun visitParamListNoParams(ctx: CParser.ParamListNoParamsContext): Value {
        return Value.of(emptyList<Parameter>())
    }

    override fun visitParamList(ctx: CParser.ParamListContext): Value {
        val params = ctx.parameter_list().parameter_declaration().map { visit(it).cast<Parameter>() }
        return Value.of(params)
    }

    override fun visitParamSpecDecl(ctx: CParser.ParamSpecDeclContext): Value {
        val declarationSpecifier = visit(ctx.declaration_specifiers()).cast<DeclarationSpecifier>()
        val declarator = visit(ctx.declarator()).cast<Declarator>()
        return Value.of(Parameter(ctx.location, declarationSpecifier, declarator))
    }

    override fun visitParamSpecAbstractDecl(ctx: CParser.ParamSpecAbstractDeclContext): Value {
        val declarationSpecifier = visit(ctx.declaration_specifiers_2()).cast<DeclarationSpecifier>()
        val declarator = ctx.abstract_declarator()?.let { visit(it).cast<Declarator>() } ?: Declarator.AnonymousDeclarator(ctx.location)
        return Value.of(Parameter(ctx.location, declarationSpecifier, declarator))
    }

    override fun visitAbsDeclPointer(ctx: CParser.AbsDeclPointerContext): Value {
        val base: Declarator = Declarator.AnonymousDeclarator(ctx.location)
        val pointerQualifiers = visit(ctx.pointer()).cast<List<List<TypeQualifier>>>()
        val declarator = pointerQualifiers.foldRight(base) { qualifiers, inner ->
            Declarator.PointerDeclarator(ctx.location, qualifiers.toSet(), inner)
        }
        return Value.of(declarator)
    }

    override fun visitAbsDeclCompound(ctx: CParser.AbsDeclCompoundContext): Value {
        val base = visit(ctx.direct_abstract_declarator()).cast<Declarator>()
        val pointerQualifiers = ctx.pointer()?.let { visit(it).cast<List<List<TypeQualifier>>>() } ?: emptyList()
        val declarator = pointerQualifiers.foldRight(base) { qualifiers, inner ->
            Declarator.PointerDeclarator(ctx.location, qualifiers.toSet(), inner)
        }
        return Value.of(declarator)
    }

    override fun visitDirectAbsDeclParenthesized(ctx: CParser.DirectAbsDeclParenthesizedContext): Value {
        return visit(ctx.abstract_declarator())
    }

    override fun visitDirectAbsDeclArray(ctx: CParser.DirectAbsDeclArrayContext): Value {
        val inner = Declarator.AnonymousDeclarator(ctx.location)
        return Value.of(Declarator.ArrayDeclarator(ctx.location, inner, ctx.assignment_expression()))
    }

    override fun visitDirectAbsDeclFunctionSimple(ctx: CParser.DirectAbsDeclFunctionSimpleContext): Value {
        val inner = Declarator.AnonymousDeclarator(ctx.location)
        val params = ctx.parameter_type_list()?.let { visit(it).cast<List<Parameter>>() } ?: emptyList()
        return Value.of(Declarator.FunctionDeclarator(ctx.location, inner, params))
    }

    override fun visitDirectAbsDeclArrayCompound(ctx: CParser.DirectAbsDeclArrayCompoundContext): Value {
        val inner = visit(ctx.direct_abstract_declarator()).cast<Declarator>()
        return Value.of(Declarator.ArrayDeclarator(ctx.location, inner, ctx.assignment_expression()))
    }

    override fun visitDirectAbsDeclFunctionCompound(ctx: CParser.DirectAbsDeclFunctionCompoundContext): Value {
        val inner = visit(ctx.direct_abstract_declarator()).cast<Declarator>()
        val params = ctx.parameter_type_list()?.let { visit(it).cast<List<Parameter>>() } ?: emptyList()
        return Value.of(Declarator.FunctionDeclarator(ctx.location, inner, params))
    }

    private fun parseStorageClassSpec(ctx: CParser.Storage_class_specifierContext): StorageClass {
        return when {
            ctx.Typedef() != null -> StorageClass.TYPEDEF
            ctx.Extern() != null -> StorageClass.EXTERN
            ctx.Static() != null -> StorageClass.STATIC
            ctx.ThreadLocal() != null -> StorageClass.THREAD_LOCAL
            ctx.Auto() != null -> StorageClass.AUTO
            ctx.Register() != null -> StorageClass.REGISTER
            else -> throw DeclarationException("Invalid storage class spec: ${ctx.text}")
        }
    }

    private fun parseTypeSpec(ctx: CParser.Type_specifierContext): TypeSpec {
        if (ctx.typedef_name() != null) {
            return TypeSpec.TypedefName(ctx.typedef_name().text)
        }
        ctx.struct_specifier()?.let {
            return TypeSpec.Struct(it.Identifier()?.text)
        }
        ctx.enum_specifier()?.let {
            return TypeSpec.Enum(it.Identifier()?.text)
        }
        return when {
            ctx.Void() != null -> TypeSpec.VOID
            ctx.Char() != null -> TypeSpec.CHAR
            ctx.Short() != null -> TypeSpec.SHORT
            ctx.Int() != null -> TypeSpec.INT
            ctx.Long() != null -> TypeSpec.LONG
            ctx.Float() != null -> TypeSpec.FLOAT
            ctx.Double() != null -> TypeSpec.DOUBLE
            ctx.Signed() != null -> TypeSpec.SIGNED
            ctx.Unsigned() != null -> TypeSpec.UNSIGNED
            ctx.Bool() != null -> TypeSpec.BOOL
            ctx.Complex() != null -> TypeSpec.COMPLEX
            else -> throw DeclarationException("Invalid type spec: ${ctx.text}")
        }
    }

    private fun parseTypeQualifier(ctx: CParser.Type_qualifierContext): TypeQualifier {
        return when {
            ctx.Const() != null -> TypeQualifier.CONST
            ctx.Restrict() != null -> TypeQualifier.RESTRICT
            ctx.Volatile() != null -> TypeQualifier.VOLATILE
            ctx.Atomic() != null -> TypeQualifier.ATOMIC
            else -> throw DeclarationException("Invalid type spec: ${ctx.text}")
        }
    }

    private fun parseFunctionSpec(ctx: CParser.Function_specifierContext): FunctionSpec {
        return when {
            ctx.Inline() != null -> FunctionSpec.INLINE
            else -> throw DeclarationException("Invalid function spec: ${ctx.text}")
        }
    }
}
