grammar ADL;

import Behavior;

architecture     : ARCHITECTURE ID LBRACE decl_list RBRACE EOF;

decl_list        : register_decl memory_decl format_list instruction_list ;

register_decl    : REGISTERS LBRACE reg_group+ RBRACE ;

reg_group        : NUM LBRACE ID+ RBRACE ;

memory_decl      : MEMORY NUM ;

format_list      : format_decl+ ;

format_decl      : FORMAT ID LBRACE field_decl+ RBRACE ;

field_decl       : ID field_type LBRACK bit_range RBRACK;

field_type       : OPCODE
                 | REG_DEST
                 | REG_SRC
                 | IMM_UNSIGNED
                 ;

bit_range        : NUM COLON NUM ;

instruction_list : instruction_decl+ ;

instruction_decl : INSTRUCTION ID LBRACE OPCODE NUM FORMAT ID operand_list behavior_decl RBRACE ;

operand_list     : OPERANDS LBRACE operand_decl* RBRACE ;

operand_decl     : ID operand_type access_type IMPLICIT? ;

operand_type     : REGISTER
                 | IMMEDIATE
                 | MEMORY
                 ;

access_type      : INPUT
                 | OUTPUT
                 | INPUT_OUTPUT
                 ;

behavior_decl    : BEHAVIOR LBRACE behavior RBRACE ;

ARCHITECTURE : 'architecture' ;
REGISTERS    : 'registers' ;
INSTRUCTION  : 'instruction' ;
OPCODE       : 'opcode' ;
FORMAT       : 'format' ;
MEMORY       : 'memory' ;
LBRACE       : '{' ;
RBRACE       : '}' ;
LBRACK       : '[' ;
RBRACK       : ']' ;
COLON        : ':' ;
REG_DEST     : 'reg_dest' ;
REG_SRC      : 'reg_src' ;
IMM_UNSIGNED : 'imm_unsigned' ;
INPUT	     : 'input' ;
OUTPUT	     : 'output' ;
INPUT_OUTPUT : 'input_output' ;
REGISTER     : 'register' ;
IMMEDIATE    : 'immediate' ;
BEHAVIOR     : 'behavior' ;
IMPLICIT     : 'implicit' ;
OPERANDS	 : 'operands' ;

ID           : [a-zA-Z_] [a-zA-Z_0-9]* ;
NUM          : [0-9]+ ;
HEX          : '0x' [0-9a-fA-F]+ ;

WS           : [ \t\r\n]+ -> skip ;