%{
extern int yylex(void);
extern int yyerror(const char *msg);

#include <stdio.h>
%}


%token INTEGER VOID FUNCTION RETURN                                 // keyword
%token IDENTIFIER INTEGER_LITERAL                                   
%token COLON SEMICOLON SINGLE_QUOTE DOUBLE_QUOTE COMMA DOT          // symbols
%token OPEN_BRACKET CLOSED_BRACKET OPEN_SQUARE_BRACKET CLOSED_SQUARE_BRACKET OPEN_CURLY_BRACKET CLOSED_CURLY_BRACKET    // brackets
%token PLUS MINUS MULTIPLY DIVIDE EQUALS GREATER_THAN LESS_THAN     // arithmetic operator

%%

start:  decl_list               { printf("Program parsed successfully!"); }
    ;

decl_list:  decl_list declaration
        |   declaration
        |   
        ;

declaration: 
        var_declaration
        | func_declaration
        ;

var_declaration:
        IDENTIFIER COLON INTEGER SEMICOLON
        ;
func_declaration:
        IDENTIFIER COLON FUNCTION INTEGER OPEN_BRACKET param_list CLOSED_BRACKET func_body
        ;

param_list:     
        param_list COMMA param_declaration
        | param_declaration
        | 
        ;

param_declaration:
        IDENTIFIER COLON INTEGER
        ;
    
func_body: 
        OPEN_CURLY_BRACKET stmt_list CLOSED_CURLY_BRACKET
        ;

stmt_list:
        stmt_list stmt_declaration
        | stmt_declaration
        |
        ;
stmt_declaration:
        var_declaration
        | assign_stmt
        | return_stmt
        ;

assign_stmt:
        IDENTIFIER EQUALS exprn SEMICOLON
        ;

return_stmt:
        RETURN exprn SEMICOLON
        ;

exprn:  
        OPEN_BRACKET exprn CLOSED_BRACKET
        | exprn PLUS exprn
        | exprn MINUS exprn
        | exprn MULTIPLY exprn
        | exprn DIVIDE exprn
        | IDENTIFIER
        | INTEGER_LITERAL
        ;


%%

