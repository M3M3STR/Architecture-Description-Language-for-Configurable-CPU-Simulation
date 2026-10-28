grammar ADL;

architecture     : ARCHITECTURE ID LBRACE decl_list RBRACE EOF;

decl_list        : register_decl memory_decl instruction_list ;

register_decl    : REGISTERS NUM ;

memory_decl      : MEMORY NUM ;

instruction_list : instruction_decl+ ;

instruction_decl : INSTRUCTION ID LBRACE opcode_decl format_decl RBRACE ;

opcode_decl      : OPCODE opcode_value ;

opcode_value     : NUM
                 | HEX
                 ;

format_decl      : FORMAT ID ;

ARCHITECTURE : 'architecture' ;
REGISTERS    : 'registers' ;
INSTRUCTION  : 'instruction' ;
OPCODE       : 'opcode' ;
FORMAT       : 'format' ;
MEMORY       : 'memory' ;
LBRACE       : '{' ;
RBRACE       : '}' ;

ID           : [a-zA-Z_] [a-zA-Z_0-9]* ;
NUM          : [0-9]+ ;
HEX          : '0x' [0-9a-fA-F]+ ;

WS           : [ \t\r\n]+ -> skip ;