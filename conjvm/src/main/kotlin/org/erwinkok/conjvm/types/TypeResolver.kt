package org.erwinkok.conjvm.types

import org.erwinkok.conjvm.declarations.Entity
import org.erwinkok.conjvm.declarations.EntityTable
import org.erwinkok.conjvm.parser.ErrorReporter
import org.erwinkok.conjvm.parser.SourceFile
import org.erwinkok.conjvm.utils.ParserReporting

class TypeResolver(
    override val reporter: ErrorReporter,
    override val source: SourceFile,
    private val entityTable: EntityTable,
    private val symbolTable: SymbolTable,
) : ParserReporting {
    // Cache for recursive struct types
    private val structCache = mutableMapOf<Entity.Struct, StructSymbol>()
    private val constantEvaluator = ConstantExpressionEvaluator(
        reporter = reporter,
        source = source,
        symbolTable = symbolTable,
    )

    fun resolveTypedef(typedef: Entity.Typedef): TypedefSymbol {
        return TypedefSymbol(
            name = typedef.name,
            type = QualType.ErrorType,
            scope = typedef.scope,
            entity = typedef,
        )
    }

    fun resolveVariable(variable: Entity.Variable): VariableSymbol {
        return VariableSymbol(
            name = variable.name,
            type = QualType.ErrorType,
            storage = emptySet(),
            linkage = variable.linkage,
            scope = variable.scope,
            entity = variable,
        )
    }

    fun resolveFunction(function: Entity.Function): FunctionSymbol {
        return FunctionSymbol(
            name = function.name,
            returnType = QualType.ErrorType,
            parameterTypes = emptyList(),
            storage = emptySet(),
            linkage = function.linkage,
            scope = function.scope,
            entity = function,
        )
    }

    fun resolveStruct(struct: Entity.Struct): StructSymbol {
        return StructSymbol(
            name = struct.name,
            members = emptyList(),
            isComplete = false,
            scope = struct.scope,
            entity = struct,
            size = null,
            alignment = null,
        )
    }

    fun resolveEnum(enum: Entity.Enum): EnumSymbol {
        return EnumSymbol(
            name = enum.name,
            constants = emptyMap(),
            underlyingType = QualType.ErrorType,
            scope = enum.scope,
            entity = enum,
        )
    }
}
