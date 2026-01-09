/*
 BASED ON:

 https://github.com/antlr/grammars-v4/blob/master/c/C.g4

 [The "BSD licence"]
 Copyright (c) 2013 Sam Harwell
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:
 1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
 3. The name of the author may not be used to endorse or promote products
    derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

grammar C;

@lexer::header {
import org.erwinkok.conjvm.ast.types.SymbolTable;
}

@lexer::members {
    private SymbolTable symbolTable;

    public CLexer(CharStream input, SymbolTable symbolTable) {
	    this(input);
	    this.symbolTable = symbolTable;
	}

    private Boolean isTypedef(String s) {
        return symbolTable.isTypedef(s);
    }
}

// virtual token
tokens { TYPEDEF_NAME }

compilationUnit
    :   external_declaration* EOF
    ;

external_declaration
    :   function_definition                                                                         #declrFunctionDef
    |   variable_declaration                                                                        #declrVarDecl
    |   ';'                                                                                         #declrStray
    ;

function_definition
    :   declaration_specifiers declarator block_statement
    ;

//
// EXPRESSIONS
//
constant_expression
    :   conditional_expression
    ;

expression
    :   assignment_expression
    ;

assignment_expression
    :   conditional_expression                                                                      #simpleAssignExpr
    |   unary_expression assignment_operator assignment_expression                                  #compoundAssignExpr
    |   DigitSequence                                                                               #assignExprWithLiteral
    ;

assignment_operator
    :   '='
    |   '+='
    |   '-='
    |   '*='
    |   '/='
    |   '%='
    |   '&='
    |   '|='
    |   '^='
    |   '<<='
    |   '>>='
    ;

conditional_expression
	:	logical_or_expression                                                                       #simpleConditional
	|	test = logical_or_expression '?' thenExpr = expression ':' elseExpr = expression            #compoundConditional
	;

logical_or_expression
    :   left = logical_and_expression (op += '||' right += logical_and_expression)*
    ;

logical_and_expression
    :   left = inclusive_or_expression (op += '&&' right += inclusive_or_expression)*
    ;

inclusive_or_expression
    :   left = exclusive_or_expression (op += '|' right += exclusive_or_expression)*
	;

exclusive_or_expression
    :   left = and_expression (op += '^' right += and_expression)*
	;

and_expression
    :   left = equality_expression (op += '&' right += equality_expression)*
	;

equality_expression
    :   left = relational_expression (op += ('==' | '!=') right += relational_expression)*
	;

relational_expression
    :   left = shift_expression (op += ('<' | '>' | '<=' | '>=') right += shift_expression)*
	;

shift_expression
	:   left = additive_expression (op += ('<<' | '>>') right += additive_expression)*
	;

additive_expression
    :   left = multiplicative_expression (op += ('+' | '-') right += multiplicative_expression)*
	;

multiplicative_expression
	:   left = cast_expression (op += ('*' | '/' | '%') right += cast_expression)*
	;

cast_expression
    :   '(' type_name ')' cast_expression                                                           #castExpr
    |   unary_expression                                                                            #simpleCast
    |   DigitSequence                                                                               #castWithLiteral
    ;

unary_expression
    :   prefix_operator* unary_core
    ;

prefix_operator
    :   '++'
    |   '--'
    ;

unary_core
    :   postfix_expression                                                                          #simpleUnaryCore
    |   unary_operator cast_expression                                                              #compoundUnaryCore
    |   sizeof_type                                                                                 #sizeofUnaryCore
    ;

unary_operator
    :   '&'
    |   '*'
    |   '+'
    |   '-'
    |   '~'
    |   '!'
    ;

sizeof_type
    :   'sizeof' '(' type_name ')'
    ;

postfix_expression
    :   primary_expression postfix_suffix*
    ;

postfix_suffix
    :   '[' index = expression ']'                                                                  #postfixArrayAccess
    |   '(' args = argument_list? ')'                                                               #postfixFunctionCall
    |   '->' field = Identifier                                                                     #postfixPointerMemberAccess
    |   '.' field = Identifier                                                                      #postfixMemberAccess
    |   '++'                                                                                        #postfixIncrement
    |   '--'                                                                                        #postfixDecrement
    ;

primary_expression
    :   Identifier                                                                                  #primaryId
    |   Constant                                                                                    #primaryConstant
    |   StringLiteral+                                                                              #primaryStringLiteral
    |   '(' expression ')'                                                                          #primaryParenthesized
    ;

argument_list
    :   assignment_expression (',' assignment_expression)*
    ;

//
// STATEMENTS
//
statement
    :   labeled_statement                                                                           #statementLabel
    |   embedded_statement                                                                          #statementEmbedded
    ;

embedded_statement
    :   block_statement                                                                             #statementBlock
    |   expression_statement                                                                        #statementExpression
    |   if_then_statement                                                                           #statementIfThen
    |   if_then_else_statement                                                                      #statementIfThenElse
    |   while_statement                                                                             #statementWhile
    |   do_statement                                                                                #statementDo
    |   for_statement                                                                               #statementFor
    |   switch_statement                                                                            #statementSwitch
    |   break_statement                                                                             #statementBreak
    |   continue_statement                                                                          #statementContinue
    |   goto_statement                                                                              #statementGoto
    |   return_statement                                                                            #statementReturn
    ;

block_statement
    :   '{' block_item* '}'
    ;

block_item
    :   statement                                                                                   #blockItemStatement
    |   variable_declaration                                                                        #blockItemVarDecl
    ;

labeled_statement
    :   Identifier ':' statement
    ;

expression_statement
    :   expression? ';'                                                                              #exprStatAssign
    ;

if_then_statement
    :   If '(' test = expression ')' thenExpr = embedded_statement
    ;

if_then_else_statement
    :   If '(' test = expression ')' thenExpr = embedded_statement 'else' elseExpr = embedded_statement
    ;

switch_statement
    :   Switch '(' expression ')' '{' switch_section* '}'
    ;

switch_section
	:	'case' constant_expression ':' statement+                                                   #switchSectionCase
	|   'default' ':' statement+                                                                    #switchSectionDefault
	;

while_statement
    :   While '(' test = expression ')' statements = embedded_statement
    ;

do_statement
    :   Do statements = embedded_statement While '(' test = expression ')' ';'
    ;

for_statement
    :   For '(' init = for_initializer? ';' test = expression? ';' iterator = for_expression? ')' embedded_statement
    ;

for_initializer
    :   argument_list                                                                               #forInitAssignmentExpr
    |   declaration_specifiers init_declarator_list                                                 #forInitVarDecl
    ;

for_expression
 	:	assignment_expression (',' assignment_expression)*
 	;

break_statement
	:	'break' ';'
	;

continue_statement
	:	'continue' ';'
	;

goto_statement
	:	'goto' Identifier ';'
	;

return_statement
	:	'return' expression? ';'
	;

//
// VARIABLE DECLARATION
//
variable_declaration
    :   declaration_specifiers init_declarator_list? ';'
    ;

declaration_specifiers
    :   declaration_specifier+
    ;

declaration_specifier
    :   storage_class_specifier                                                                     #storageClassSpec
    |   type_specifier                                                                              #declSpecTypeSpec
    |   type_qualifier                                                                              #declSpecTypeQual
    |   function_specifier                                                                          #declSpecFuncSpec
    ;

init_declarator_list
    :   init_declarator (',' init_declarator)*
    ;

init_declarator
    :   declarator ('=' initializer)?
    ;

storage_class_specifier
    :   Typedef
    |   Extern
    |   Static
    |   Auto
    |   Register
    ;

// union is not supported
type_specifier
    :   Void
    |   Char
    |   Short
    |   Int
    |   Long
    |   Float
    |   Double
    |   Signed
    |   Unsigned
    |   struct_specifier
    |   enum_specifier
    |   typedef_name
    ;

struct_specifier
    :   'struct' Identifier? '{' struct_declaration_list '}'
    |   'struct' Identifier
    ;

struct_declaration_list
    :   struct_declaration+
    ;

struct_declaration // The first two rules have priority order and cannot be simplified to one expression.
    :   specifier_qualifier_list struct_declarator_list ';'
    |   specifier_qualifier_list ';'
    ;

specifier_qualifier_list
    :   (type_specifier | type_qualifier)+
    ;

struct_declarator_list
    :   struct_declarator (',' struct_declarator)*
    ;

struct_declarator
    :   declarator
    |   declarator? ':' constant_expression
    ;

enum_specifier
    :   'enum' Identifier? '{' enumerator_list ','? '}'
    |   'enum' Identifier
    ;

enumerator_list
    :   enumerator (',' enumerator)*
    ;

enumerator
    :   Identifier ('=' constant_expression)?
    ;

type_qualifier
    :   Const
    |   Restrict
    |   Volatile
    ;

function_specifier
    :   Inline
    ;

declarator
    :   pointer? direct_declarator
    ;

direct_declarator
    :   Identifier                                                                                  #directDeclIdentifier
    |   '(' declarator ')'                                                                          #directDeclParenthesized
    |   direct_declarator '(' parameter_type_list? ')'                                              #directDeclFunction
    |   direct_declarator '[' assignment_expression? ']'                                            #directDeclArray
    ;

pointer
    :   pointer_part+
    ;

pointer_part
    :   '*' type_qualifier*
    ;

parameter_type_list
    :   Void                                                                                        #paramListNoParams
    |   parameter_list                                                                              #paramList
    ;

parameter_list
    :   parameter_declaration (',' parameter_declaration)*
    ;

parameter_declaration
    :   declaration_specifiers declarator
    ;

type_name
    :   specifier_qualifier_list
    ;

typedef_name
    :   TYPEDEF_NAME
    ;

initializer
    :   assignment_expression
    ;


Break
    : 'break'
    ;

Case
    : 'case'
    ;

Char
    : 'char'
    ;

Const
    : 'const'
    ;

Restrict
    : 'restrict'
    ;

Continue
    : 'continue'
    ;

Default
    : 'default'
    ;

Do
    : 'do'
    ;

Double
    : 'double'
    ;

Else
    : 'else'
    ;

Enum
    : 'enum'
    ;

Float
    : 'float'
    ;

For
    : 'for'
    ;

Goto
    : 'goto'
    ;

If
    : 'if'
    ;

Int
    : 'int'
    ;

Long
    : 'long'
    ;

Return
    : 'return'
    ;

Short
    : 'short'
    ;

Signed
    : 'signed'
    ;

Sizeof
    : 'sizeof'
    ;

Static
    : 'static'
    ;

Auto
    : 'auto'
    ;

Register
    : 'register'
    ;

Struct
    : 'struct'
    ;

Switch
    : 'switch'
    ;

Typedef
    : 'typedef'
    ;

Extern
    : 'extern'
    ;

Union
    : 'union'
    ;

Unsigned
    : 'unsigned'
    ;

Void
    : 'void'
    ;

Volatile
    : 'volatile'
    ;

Inline
    : 'inline'
    ;

While
    : 'while'
    ;

LeftParen
    : '('
    ;

RightParen
    : ')'
    ;

LeftBracket
    : '['
    ;

RightBracket
    : ']'
    ;

LeftBrace
    : '{'
    ;

RightBrace
    : '}'
    ;

Less
    : '<'
    ;

LessEqual
    : '<='
    ;

Greater
    : '>'
    ;

GreaterEqual
    : '>='
    ;

LeftShift
    : '<<'
    ;

RightShift
    : '>>'
    ;

Plus
    : '+'
    ;

PlusPlus
    : '++'
    ;

Minus
    : '-'
    ;

MinusMinus
    : '--'
    ;

Star
    : '*'
    ;

Div
    : '/'
    ;

Mod
    : '%'
    ;

And
    : '&'
    ;

Or
    : '|'
    ;

AndAnd
    : '&&'
    ;

OrOr
    : '||'
    ;

Caret
    : '^'
    ;

Not
    : '!'
    ;

Tilde
    : '~'
    ;

Question
    : '?'
    ;

Colon
    : ':'
    ;

Semi
    : ';'
    ;

Comma
    : ','
    ;

Assign
    : '='
    ;

// '*=' | '/=' | '%=' | '+=' | '-=' | '<<=' | '>>=' | '&=' | '^=' | '|='
StarAssign
    : '*='
    ;

DivAssign
    : '/='
    ;

ModAssign
    : '%='
    ;

PlusAssign
    : '+='
    ;

MinusAssign
    : '-='
    ;

LeftShiftAssign
    : '<<='
    ;

RightShiftAssign
    : '>>='
    ;

AndAssign
    : '&='
    ;

XorAssign
    : '^='
    ;

OrAssign
    : '|='
    ;

Equal
    : '=='
    ;

NotEqual
    : '!='
    ;

Arrow
    : '->'
    ;

Dot
    : '.'
    ;

Ellipsis
    : '...'
    ;

Identifier
    : IdentifierNondigit (IdentifierNondigit | Digit)*
          {
              if (isTypedef(getText())) {
                  setType(CParser.TYPEDEF_NAME);
              }
          }
    ;

fragment IdentifierNondigit
    : Nondigit
    ;

fragment Nondigit
    : [a-zA-Z_]
    ;

fragment Digit
    : [0-9]
    ;

Constant
    : IntegerConstant
    | FloatingConstant
    | CharacterConstant
    ;

fragment IntegerConstant
    : DecimalConstant IntegerSuffix?
    | OctalConstant IntegerSuffix?
    | HexadecimalConstant IntegerSuffix?
    | BinaryConstant
    ;

fragment BinaryConstant
    : '0' [bB] [0-1]+
    ;

fragment DecimalConstant
    : NonzeroDigit Digit*
    ;

fragment OctalConstant
    : '0' OctalDigit*
    ;

fragment HexadecimalConstant
    : HexadecimalPrefix HexadecimalDigit+
    ;

fragment HexadecimalPrefix
    : '0' [xX]
    ;

fragment NonzeroDigit
    : [1-9]
    ;

fragment OctalDigit
    : [0-7]
    ;

fragment HexadecimalDigit
    : [0-9a-fA-F]
    ;

fragment IntegerSuffix
    : UnsignedSuffix LongSuffix?
    | UnsignedSuffix LongLongSuffix
    | LongSuffix UnsignedSuffix?
    | LongLongSuffix UnsignedSuffix?
    ;

fragment UnsignedSuffix
    : [uU]
    ;

fragment LongSuffix
    : [lL]
    ;

fragment LongLongSuffix
    : 'll'
    | 'LL'
    ;

fragment FloatingConstant
    : DecimalFloatingConstant
    | HexadecimalFloatingConstant
    ;

fragment DecimalFloatingConstant
    : FractionalConstant ExponentPart? FloatingSuffix?
    | DigitSequence ExponentPart FloatingSuffix?
    ;

fragment HexadecimalFloatingConstant
    : HexadecimalPrefix (HexadecimalFractionalConstant | HexadecimalDigitSequence) BinaryExponentPart FloatingSuffix?
    ;

fragment FractionalConstant
    : DigitSequence? '.' DigitSequence
    | DigitSequence '.'
    ;

fragment ExponentPart
    : [eE] Sign? DigitSequence
    ;

fragment Sign
    : [+-]
    ;

DigitSequence
    : Digit+
    ;

fragment HexadecimalFractionalConstant
    : HexadecimalDigitSequence? '.' HexadecimalDigitSequence
    | HexadecimalDigitSequence '.'
    ;

fragment BinaryExponentPart
    : [pP] Sign? DigitSequence
    ;

fragment HexadecimalDigitSequence
    : HexadecimalDigit+
    ;

fragment FloatingSuffix
    : [flFL]
    ;

fragment CharacterConstant
    : '\'' CCharSequence '\''
    ;

fragment CCharSequence
    : CChar+
    ;

fragment CChar
    : ~['\\\r\n]
    ;

fragment EscapeSequence
    : SimpleEscapeSequence
    ;

fragment SimpleEscapeSequence
    : '\\' ['"?abfnrtv\\]
    ;

fragment OctalEscapeSequence
    : '\\' OctalDigit OctalDigit? OctalDigit?
    ;

fragment HexadecimalEscapeSequence
    : '\\x' HexadecimalDigit+
    ;

StringLiteral
    : '"' SCharSequence? '"'
    ;

fragment SCharSequence
    : SChar+
    ;

fragment SChar
    : ~["\\\r\n]
    | EscapeSequence
    | '\\\n'   // Added line
    | '\\\r\n' // Added line
    ;

MultiLineMacro
    : '#' (~[\n]*? '\\' '\r'? '\n')+ ~ [\n]+ -> channel (HIDDEN)
    ;

Directive
    : '#' ~ [\n]* -> channel(HIDDEN)
    ;

Whitespace
    : [ \t]+ -> channel(HIDDEN)
    ;

Newline
    : ('\r' '\n'? | '\n') -> channel(HIDDEN)
    ;

BlockComment
    : '/*' .*? '*/' -> channel(HIDDEN)
    ;

LineComment
    : '//' ~[\r\n]* -> channel(HIDDEN)
    ;
