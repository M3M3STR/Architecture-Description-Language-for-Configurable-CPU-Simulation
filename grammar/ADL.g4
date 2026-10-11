grammar ADL;

program          : architecture EOF ;

architecture     : ARCHITECTURE ID LBRACE decl_list RBRACE ;

decl_list        : decl+ ;

decl             : register_decl
                 | instruction_decl
                 ;

register_decl    : REGISTERS NUM ;

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

LBRACE       : '{' ;
RBRACE       : '}' ;

ID           : [a-zA-Z_] [a-zA-Z_0-9]* ;
NUM          : [0-9]+ ;
HEX          : '0x' [0-9a-fA-F]+ ;

WS           : [ \t\r\n]+ -> skip ;