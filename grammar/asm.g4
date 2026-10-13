grammar ASM;

program : line* EOF ;

line : instruction? comment? NEWLINE | NEWLINE;

instruction : ID operand_list? ;

operand_list : operand (COMMA operand)* ;

operand : REG | NUM ;

comment : HASH ;

REG      : 'r' [0-9]+ ;
NUM      : [0-9]+ ;
ID       : [a-zA-Z_] [a-zA-Z_0-9]* ;
COMMA    : ',' ;
HASH: '#' ~[\r\n]* ;

NEWLINE  : [\r\n]+ ;
WS       : [ \t]+ -> skip ;