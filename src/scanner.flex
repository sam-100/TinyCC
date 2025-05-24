%{
    #include "parser.h"
    #include <stdio.h>
    #include <stdlib.h>

    int line_no = 1;
%}

digit   [0-9]
letter  [a-zA-Z]

%%
[ \t]                                       ;
\n                                          { line_no++; }

integer                                     { printf("Token: INTEGER, lexeme: %s, line_no: %d\n", yytext, line_no); return INTEGER; }
function                                    { printf("Token: FUNCTION, lexeme: %s, line_no: %d\n", yytext, line_no); return FUNCTION; }
return                                      { printf("Token: RETURN, lexeme: %s, line_no: %d\n", yytext, line_no); return RETURN; }

\+                                          { printf("Token: PLUS, lexeme: %s, line_no: %d\n", yytext, line_no); return PLUS; }
\-                                          { printf("Token: MINUS, lexeme: %s, line_no: %d\n", yytext, line_no); return MINUS; }
\*                                          { printf("Token: MULTIPLY, lexeme: %s, line_no: %d\n", yytext, line_no); return MULTIPLY; }
\/                                          { printf("Token: DIVIDE, lexeme: %s, line_no: %d\n", yytext, line_no); return DIVIDE; }
\<                                          { printf("Token: GREATER_THAN, lexeme: %s, line_no: %d\n", yytext, line_no); return GREATER_THAN; }
\>                                          { printf("Token: LESS_THAN, lexeme: %s, line_no: %d\n", yytext, line_no); return LESS_THAN; }
\=                                          { printf("Token: EQUALS, lexeme: %s, line_no: %d\n", yytext, line_no); return EQUALS; }

\(                                          { printf("Token: OPEN_BRACKET, lexeme: %s, line_no: %d\n", yytext, line_no); return OPEN_BRACKET; }
\)                                          { printf("Token: CLOSED_BRACKET, lexeme: %s, line_no: %d\n", yytext, line_no); return CLOSED_BRACKET; }
\[                                          { printf("Token: OPEN_SQUARE_BRACKET, lexeme: %s, line_no: %d\n", yytext, line_no); return OPEN_SQUARE_BRACKET; }
\]                                          { printf("Token: CLOSED_SQUARE_BRACKET, lexeme: %s, line_no: %d\n", yytext, line_no); return CLOSED_SQUARE_BRACKET; }
\{                                          { printf("Token: OPEN_CURLY_BRACKET, lexeme: %s, line_no: %d\n", yytext, line_no); return OPEN_CURLY_BRACKET; }
\}                                          { printf("Token: CLOSED_CURLY_BRACKET, lexeme: %s, line_no: %d\n", yytext, line_no); return CLOSED_CURLY_BRACKET; }

\:                                          { printf("Token: COLON, lexeme: %s, line_no: %d\n", yytext, line_no); return COLON; }
\;                                          { printf("Token: SEMICOLON, lexeme: %s, line_no: %d\n", yytext, line_no); return SEMICOLON; }

\.                                          { printf("Token: DOT, lexeme: %s, line_no: %d\n", yytext, line_no); return DOT; }
\,                                          { printf("Token: COMMA, lexeme: %s, line_no: %d\n", yytext, line_no); return COMMA; }

{digit}*                                    { printf("Token: INTEGER_LITERAL, lexeme: %s, line_no: %d\n", yytext, line_no); return INTEGER_LITERAL; }
{letter}({letter}|{digit})*                 { printf("Token: IDENTIFIER, lexeme: %s, line_no: %d\n", yytext, line_no); return IDENTIFIER; }

.                                           { printf("Invalid Token: %s\t at line_no: %d", yytext, line_no); exit(-1); }


%%

