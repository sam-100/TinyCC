%{
    #include "parser.h"
    #include <stdio.h>
    #include <stdlib.h>

    extern void yyerror(const char *msg);

    int line_no = 1;
%}

digit   [0-9]
letter  [a-zA-Z]

%%
[ \t]                                       ;
\n                                          { line_no++; }


true                                        { printf("Token: BOOLEAN_LITERAL, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return BOOLEAN_LITERAL; }
false                                       { printf("Token: BOOLEAN_LITERAL, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return BOOLEAN_LITERAL; }
\'{letter}\'                                  { printf("Token: CHAR_LITERAL, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return CHAR_LITERAL; }
{digit}*                                    { printf("Token: INTEGER_LITERAL, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return INTEGER_LITERAL; }
print                                       { printf("Token: PRINT, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return PRINT; }
read                                       { printf("Token: READ, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return READ; }


integer                                     { printf("Token: INTEGER, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return INTEGER; }
void                                     { printf("Token: VOID, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return VOID; }
boolean                                     { printf("Token: BOOLEAN, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return BOOLEAN; }
char                                     { printf("Token: CHARACTER, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return CHARACTER; }


function                                    { printf("Token: FUNCTION, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return FUNCTION; }
return                                      { printf("Token: RETURN, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return RETURN; }


\+                                          { printf("Token: PLUS, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return PLUS; }
\-                                          { printf("Token: MINUS, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return MINUS; }
\*                                          { printf("Token: MULTIPLY, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return MULTIPLY; }
\/                                          { printf("Token: DIVIDE, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return DIVIDE; }
\<                                          { printf("Token: GREATER_THAN, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return GREATER_THAN; }
\>                                          { printf("Token: LESS_THAN, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return LESS_THAN; }
\=                                          { printf("Token: EQUALS, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return EQUALS; }


\(                                          { printf("Token: OPEN_BRACKET, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return OPEN_BRACKET; }
\)                                          { printf("Token: CLOSED_BRACKET, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return CLOSED_BRACKET; }
\[                                          { printf("Token: OPEN_SQUARE_BRACKET, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return OPEN_SQUARE_BRACKET; }
\]                                          { printf("Token: CLOSED_SQUARE_BRACKET, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return CLOSED_SQUARE_BRACKET; }
\{                                          { printf("Token: OPEN_CURLY_BRACKET, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return OPEN_CURLY_BRACKET; }
\}                                          { printf("Token: CLOSED_CURLY_BRACKET, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return CLOSED_CURLY_BRACKET; }

\:                                          { printf("Token: COLON, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return COLON; }
\;                                          { printf("Token: SEMICOLON, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return SEMICOLON; }

\.                                          { printf("Token: DOT, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return DOT; }
\,                                          { printf("Token: COMMA, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return COMMA; }

{letter}({letter}|{digit})*                 { printf("Token: IDENTIFIER, lexeme: \"%s\", line_no: %d\n", yytext, line_no); return IDENTIFIER; }

.                                           { yyerror("Invalid Token!"); exit(1);}


%%

