grammar Behavior;

behavior			: statement* ;

statement			: assignment
					;

assignment			: assignment_target ASSIGN expression SEMI ;

assignment_target	: ID ;

expression			: unary_expression (binary_operator unary_expression)* ;
			
unary_expression	: unary_operator* primary_expression ;
			
primary_expression	: ID
					| INT
					| LPAREN expression RPAREN
					;

binary_operator     : PLUS | MINUS
                    | MULT | DIV | MOD
                    | BIT_AND | BIT_OR | BIT_XOR
                    | SHIFT_LEFT | SHIFT_RIGHT
                    | EQ | NEQ
                    | LT | GT | LTE | GTE
                    | AND | OR
                    ;

unary_operator		: MINUS
					| NOT
					| BIT_NOT
					;

// Keywords and Operators

ASSIGN	: '=';
EQ		: '==';
NEQ		: '!=';
LT		: '<';
GT		: '>';
LTE		: '<=';
GTE		: '>=';

PLUS	: '+';
MINUS	: '-';
MULT	: '*';
DIV		: '/';
MOD		: '%';

AND		: '&&';
OR		: '||';
NOT		: '!';

BIT_NOT	: '~';
BIT_AND	: '&';
BIT_OR	: '|';
BIT_XOR	: '^';

SHIFT_LEFT	: '<<';
SHIFT_RIGHT	: '>>';

SEMI	: ';';
COMMA	: ',';

LPAREN	: '(';
RPAREN	: ')';
LBRACE	: '{';
RBRACE	: '}';
LBRACK	: '[';
RBRACK	: ']';

ID 			: [a-zA-Z_] [a-zA-Z_0-9]* ;

INT			: '0x' [0-9a-fA-F]+
			| '0b' [01]+
			| [0-9]+
			;

COMMENT		: '#' ~[\r\n]* -> skip;

WS          : [ \t\r\n]+ -> skip ;