grammar ADL;

// ==========================================
// Parser Rules
// ==========================================

architecture
    : ARCHITECTURE ID LBRACE decl_list RBRACE EOF
    ;

decl_list
    : decl+
    ;

decl
    : register_decl
    | word_decl
    | mem_decl
    | inst_decl
    ;

register_decl
    : REGISTERS NUM
    ;

word_decl
    : WORD_SIZE NUM
    ;

mem_decl
    : MEMORY NUM
    ;

inst_decl
    : INSTRUCTION ID LBRACE
        opcode_decl
        format_decl
        behavior_decl
      RBRACE
    ;

opcode_decl
    : OPCODE opcode_val
    ;

opcode_val
    : NUM
    | HEX
    | BIN
    ;

format_decl
    : FORMAT ID
    ;

behavior_decl
    : BEHAVIOR LBRACE stmt_list RBRACE
    ;

stmt_list
    : stmt+
    ;

stmt
    : assign_stmt SEMI
    | if_stmt
    ;

assign_stmt
    : lhs ASSIGN expr
    ;

expr
    : primary op primary
    | primary
    ;

primary
    : NUM
    | HEX
    | BIN
    | ID
    | reg_ref
    | mem_ref
    ;

lhs
    : reg_ref
    | mem_ref
    | PC
    ;

reg_ref
    : R LBRACK ID RBRACK
    ;

mem_ref
    : MEM LBRACK expr RBRACK
    ;


// ===============================================================================
// TODO: not sure if this was part of the grammar or an idea but still included it
// ===============================================================================

if_stmt
    : IF LPAREN expr RPAREN LBRACE stmt_list RBRACE
    ;

op
    : PLUS
    | MINUS
    | MULT
    | DIV
    ;


// ==========================================
// Lexer Rules
// ==========================================

ARCHITECTURE : 'architecture';
REGISTERS    : 'registers';
WORD_SIZE    : 'word_size';
MEMORY       : 'memory';
INSTRUCTION  : 'instruction';
OPCODE       : 'opcode';
FORMAT       : 'format';
BEHAVIOR     : 'behavior';
IF           : 'if';

PC           : 'PC';
R            : 'R';
MEM          : 'Mem';

ASSIGN       : '=';
PLUS         : '+';
MINUS        : '-';
MULT         : '*';
DIV          : '/';

LBRACE       : '{';
RBRACE       : '}';
LBRACK       : '[';
RBRACK       : ']';
LPAREN       : '(';
RPAREN       : ')';
SEMI         : ';';

HEX
    : '0x' [0-9a-fA-F]+
    ;

BIN
    : '0b' [01]+
    ;

NUM
    : [0-9]+
    ;

ID
    : [a-zA-Z_] [a-zA-Z0-9_]*
    ;

WS
    : [ \t\r\n]+ -> skip
    ;