%{
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "parser.h"

extern void yyerror(const char *msg);
extern FILE *f_tokens;
extern YYLTYPE yylloc;

int line_no = 1;

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = line_no;
%}

%option yylineno


digit   [0-9]
letter  [a-zA-Z]

%%


[ \t]                                       ;
\n                                          { line_no++; }


true                                        { 
                                                yylval.b_val = true;
                                                fprintf(f_tokens, "Token: BOOLEAN_LITERAL, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return BOOLEAN_LITERAL; 
                                            }
false                                       { 
                                                yylval.b_val = false;
                                                fprintf(f_tokens, "Token: BOOLEAN_LITERAL, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return BOOLEAN_LITERAL; 
                                            }
\'({letter}|{digit})\'                      { 
                                                yylval.c_val = yytext[1];
                                                fprintf(f_tokens, "Token: CHAR_LITERAL, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return CHAR_LITERAL; 
                                            }
{digit}+                                    { 
                                                yylval.i_val = atoi(yytext);
                                                fprintf(f_tokens, "Token: INTEGER_LITERAL, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return INTEGER_LITERAL;
                                            }

print                                       { 
                                                fprintf(f_tokens, "Token: PRINT, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return PRINT; 
                                            }
read                                        { 
                                                fprintf(f_tokens, "Token: READ, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return READ; 
                                            }


integer                                     { 
                                                yylval.i_val = INTEGER;
                                                fprintf(f_tokens, "Token: INTEGER, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return INTEGER; 
                                            }
void                                        { 
                                                yylval.i_val = VOID;
                                                fprintf(f_tokens, "Token: VOID, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return VOID; 
                                            }
bool                                        { 
                                                yylval.i_val = BOOLEAN;
                                                fprintf(f_tokens, "Token: BOOLEAN, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return BOOLEAN; 
                                            }
char                                        { 
                                                yylval.i_val = CHARACTER;
                                                fprintf(f_tokens, "Token: CHARACTER, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return CHARACTER; 
                                            }


function                                    { 
                                                fprintf(f_tokens, "Token: FUNCTION, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return FUNCTION; 
                                            }
return                                      { 
                                                fprintf(f_tokens, "Token: RETURN, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return RETURN; 
                                            }


\+                                          { 
                                                fprintf(f_tokens, "Token: PLUS, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return PLUS; 
                                            }
\-                                          { 
                                                fprintf(f_tokens, "Token: MINUS, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return MINUS; 
                                            }
\*                                          { 
                                                fprintf(f_tokens, "Token: MULTIPLY, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return MULTIPLY; 
                                            }
\/                                          { 
                                                fprintf(f_tokens, "Token: DIVIDE, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return DIVIDE; 
                                            }
\=                                          { 
                                                fprintf(f_tokens, "Token: ASSIGN, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return ASSIGN; 
                                            }
\<                                          { 
                                                fprintf(  f_tokens, "Token: GT, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return GT;
                                            }
\<\=                                        { 
                                                fprintf(f_tokens, "Token: LE, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return LE; 
                                            }
\>                                          { 
                                                fprintf(f_tokens, "Token: LT, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return LT; 
                                            }
\>\=                                        { 
                                                fprintf(f_tokens, "Token: GE, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return GE; 
                                            }
\=\=                                        { 
                                                fprintf(f_tokens, "Token: EQ, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return EQ; 
                                            }



\(                                          { 
                                                fprintf(f_tokens, "Token: OPEN_BRACKET, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return OPEN_BRACKET; 
                                            }
\)                                          { 
                                                fprintf(f_tokens, "Token: CLOSED_BRACKET, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return CLOSED_BRACKET; 
                                            }
\[                                          { 
                                                fprintf(f_tokens, "Token: OPEN_SQUARE_BRACKET, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return OPEN_SQUARE_BRACKET; 
                                            }
\]                                          { 
                                                fprintf(f_tokens, "Token: CLOSED_SQUARE_BRACKET, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return CLOSED_SQUARE_BRACKET; 
                                            }
\{                                          { 
                                                fprintf(f_tokens, "Token: OPEN_CURLY_BRACKET, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return OPEN_CURLY_BRACKET; 
                                            }
\}                                          { 
                                                fprintf(f_tokens, "Token: CLOSED_CURLY_BRACKET, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return CLOSED_CURLY_BRACKET; 
                                            }

\:                                          { 
                                                fprintf(f_tokens, "Token: COLON, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return COLON; 
                                            }
\;                                          { 
                                                fprintf(f_tokens, "Token: SEMICOLON, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return SEMICOLON; 
                                            }

\.                                          { 
                                                fprintf(f_tokens, "Token: DOT, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return DOT; 
                                            }
\,                                          { 
                                                fprintf(f_tokens, "Token: COMMA, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return COMMA; 
                                            }

{letter}({letter}|{digit})*                 { 
                                                yylval.s_val = strdup(yytext);
                                                fprintf(f_tokens, "Token: IDENTIFIER, lexeme: \"%s\", line_no: %d\n", yytext, line_no); 
                                                return IDENTIFIER; 
                                            }

.                                           { 
                                                yyerror("Invalid Token!"); 
                                                exit(1);
                                            }


%%

