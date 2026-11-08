grammar ADL;

architecture     : ARCHITECTURE ID LBRACE decl_list RBRACE EOF;

decl_list        : register_decl memory_decl format_list instruction_list ;

register_decl    : REGISTERS LBRACE reg_group+ RBRACE ;

reg_group        : NUM LBRACE ID+ RBRACE ;

memory_decl      : MEMORY NUM ;

format_list      : format_decl+ ;

format_decl      : FORMAT ID LBRACE field_decl+ RBRACE ;

field_decl       : field_type LBRACKET bit_range RBRACKET;

field_type       : OPCODE
                 | REG_DEST
                 | REG_SRC
                 | IMM_UNSIGNED
                 ;

bit_range        : NUM COLON NUM ;

instruction_list : instruction_decl+ ;

instruction_decl : INSTRUCTION ID LBRACE opcode_decl FORMAT ID RBRACE ;

opcode_decl      : OPCODE opcode_value ;

opcode_value     : NUM
                 | HEX
                 ;

ARCHITECTURE : 'architecture' ;
REGISTERS    : 'registers' ;
INSTRUCTION  : 'instruction' ;
OPCODE       : 'opcode' ;
FORMAT       : 'format' ;
MEMORY       : 'memory' ;
LBRACE       : '{' ;
RBRACE       : '}' ;
LBRACKET     : '[' ;
RBRACKET     : ']' ;
COLON        : ':' ;
REG_DEST     : 'reg_dest' ;
REG_SRC      : 'reg_src' ;
IMM_UNSIGNED : 'imm_unsigned' ;

ID           : [a-zA-Z_] [a-zA-Z_0-9]* ;
NUM          : [0-9]+ ;
HEX          : '0x' [0-9a-fA-F]+ ;

WS           : [ \t\r\n]+ -> skip ;