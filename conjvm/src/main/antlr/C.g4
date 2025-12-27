grammar C;

compilationUnit
    :   functionDefinition* EOF
    ;

functionDefinition
    :  Static? Void id = Identifier '(' Void ')' block_statement
    ;

//
// EXPRESSIONS
//
expression
    :   assignment_expression
    ;

assignment_expression
    :   conditional_expression                                                                      #simpleAssignExpr
    |   unary_expression assignment_operator assignment_expression                                  #compoundAssignExpr
    ;

assignment_operator
    : '='
    | '+='
    | '-='
    | '*='
    | '/='
    | '%='
    | '&='
    | '|='
    | '^='
    | '<<='
    | '>>='
    ;

conditional_expression
	:	logical_or_expression                                                                       #simpleConditional
	|	test = logical_or_expression '?' thenExpr = expression ':' elseExpr = expression            #compoundConditional
	;

logical_or_expression
	:	logical_and_expression                                                                      #simpleLogicalOr
	|	left = logical_or_expression '||' right = logical_and_expression                            #compoundLogicalOr
	;

logical_and_expression
	:	inclusive_or_expression                                                                     #simpleLogicalAnd
	|	left = logical_and_expression '&&' right = inclusive_or_expression                          #compoundLogicalAnd
	;

inclusive_or_expression
	:	exclusive_or_expression                                                                     #simpleInclusiveOr
	|	left = inclusive_or_expression '|' right = exclusive_or_expression                          #compoundInclusiveOr
	;

exclusive_or_expression
	:	and_expression                                                                              #simpleExclusiveOr
	|	left = exclusive_or_expression '^' right = and_expression                                   #compoundExclusiveOr
	;

and_expression
	:	equality_expression                                                                         #simpleAnd
	|	left = and_expression '&' right = equality_expression                                       #compoundAnd
	;

equality_expression
	:	relational_expression                                                                       #simpleEquality
	|	left = equality_expression '==' right = relational_expression                               #equalityEquals
	|	left = equality_expression '!=' right = relational_expression                               #equalityNotEquals
	;

relational_expression
	:	shift_expression                                                                            #simpleRelational
	|	left = relational_expression '<' right = shift_expression                                   #relationalLess
	|	left = relational_expression '>' right = shift_expression                                   #relationalGreater
	|	left = relational_expression '<=' right = shift_expression                                  #relationalLessOrEqual
	|	left = relational_expression '>=' right = shift_expression                                  #relationalGreaterOrEqual
	;

shift_expression
	:	additive_expression                                                                         #simpleShift
	|	left = shift_expression '<<' right = additive_expression                                    #shiftLeft
	|	left = shift_expression '>>' right = additive_expression                                    #shiftRight
	;

additive_expression
	:	multiplicative_expression                                                                   #simpleAdditive
	|	left = additive_expression '+' right = multiplicative_expression                            #additiveAdd
	|	left = additive_expression '-' right = multiplicative_expression                            #additiveSubtract
	;

multiplicative_expression
	:	cast_expression                                                                             #simpleMultiplicative
	|	left = multiplicative_expression '*' right = cast_expression                                #multiplicativeMultiply
	|	left = multiplicative_expression '/' right = cast_expression                                #multiplicativeDivide
	|	left = multiplicative_expression '%' right = cast_expression                                #multiplicativeModulo
	;

cast_expression
    :   unary_expression                                                                            #simpleCast
    |   '(' type_name ')' cast_expression                                                           #castExpr
    ;

unary_expression
    :   postfix_expression                                                                          #simpleUnary
    |   '&' cast_expression                                                                         #unaryAddress
    |   '*' cast_expression                                                                         #unaryIndirection
    |   '+' cast_expression                                                                         #unaryPlus
	|   '-' cast_expression                                                                         #unaryMinus
	|   '~' cast_expression                                                                         #unaryBitwiseNot
	|   '!' cast_expression                                                                         #unaryLogicalNot
    |   '++' cast_expression                                                                        #unaryPlusPlus
    |   '--' cast_expression                                                                        #unaryMinusMinus
    ;

postfix_expression
    :   primary_expression                                                                          #postfixPrimary
    |   postfix_expression '[' expression ']'                                                       #postfixArrayAccess
    |   id = Identifier '(' argument_list? ')'                                                      #postfixCall
//    |   postfix_expression '(' argument_list? ')'                                                   #postfixCall
    |   postfix_expression '.' Identifier                                                           #postfixFieldAccess
    |   postfix_expression '->' Identifier                                                          #postfixPtrFieldAccess
    |   postfix_expression '++'                                                                     #postfixPlusPlus
    |   postfix_expression '--'                                                                     #postfixMinusMinus
    ;

primary_expression
    :   Identifier                                                                                  #primaryId
    |   Constant                                                                                    #primaryConstant
    |   StringLiteral                                                                               #primaryStringLiteral
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
    |   variable_declaration                                                                        #statementVarDecl
    |   embedded_statement                                                                          #statementEmbedded
    ;

embedded_statement
    :   block_statement                                                                             #statementBlock
    |   expression_statement                                                                        #statementExpression
    |   if_then_statement                                                                           #statementIfThen
    |   if_then_else_statement                                                                      #statementIfThenElse
    |   while_statement                                                                             #statementWhile
    |   for_statement                                                                               #statementFor
    |   switch_statement                                                                            #statementSwitch
    |   break_statement                                                                             #statementBreak
    |   continue_statement                                                                          #statementContinue
    |   goto_statement                                                                              #statementGoto
    |   return_statement                                                                            #statementReturn
    ;

block_statement
    : '{' statement* '}'
    ;

labeled_statement
    :   Identifier ':' statement
    ;

expression_statement
    :   expression ';'                                                                              #exprStatAssign
    ;

if_then_statement
    : If '(' test = expression ')' thenExpr = embedded_statement
    ;

if_then_else_statement
    : If '(' test = expression ')' thenExpr = statement 'else' elseExpr = embedded_statement
    ;

switch_statement
    : Switch '(' expression ')' '{' switch_section* '}'
    ;

switch_section
	:	'case' expression ':' statement+                                                            #switchSectionCase
	|   'default' ':' statement+                                                                    #switchSectionDefault
	;

while_statement
    :   While '(' test = expression ')' statements = embedded_statement
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
    :   declaration_specifiers init_declarator_list ';'
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
    :   'typedef'
    |   'extern'
    |   'static'
    |   'auto'
    |   'register'
    ;

// struct, union and enum are not supported
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
    |   typedef_name
    ;

typedef_name
    :   Identifier
    ;

specifier_qualifier_list
    : (type_specifier | type_qualifier) specifier_qualifier_list?
    ;

type_qualifier
    :   'const'
    |   'restrict'
    |   'volatile'
    ;

function_specifier
    :   'inline'
    ;

// Not all direct declarator types are supported, only Identifier
declarator
    :   pointer? Identifier
    ;

pointer
    :   '*'
    ;

type_name
    :   specifier_qualifier_list
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

Struct
    : 'struct'
    ;

Switch
    : 'switch'
    ;

Typedef
    : 'typedef'
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
