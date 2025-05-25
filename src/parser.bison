%{
extern int yylex(void);
extern int yyerror(const char *msg);

#include <stdio.h>
%}


%token INTEGER CHARACTER BOOLEAN VOID FUNCTION RETURN       
%token PRINT READ                          
%token IDENTIFIER INTEGER_LITERAL BOOLEAN_LITERAL CHAR_LITERAL
%token COLON SEMICOLON SINGLE_QUOTE DOUBLE_QUOTE COMMA DOT          
%token PLUS MINUS MULTIPLY DIVIDE EQUALS GREATER_THAN LESS_THAN     // arithmetic operator
%token OPEN_BRACKET CLOSED_BRACKET 
%token OPEN_SQUARE_BRACKET CLOSED_SQUARE_BRACKET
%token OPEN_CURLY_BRACKET CLOSED_CURLY_BRACKET 

%left PLUS MINUS
%left MULTIPLY DIVIDE

%%

start:  decl_list               { printf("Program parsed successfully!\n"); }
    ;

decl_list:  decl_list declaration
        |   declaration
        ;

declaration: 
        var_declaration
        | func_declaration
        ;

var_declaration:
        IDENTIFIER COLON type SEMICOLON
        | IDENTIFIER COLON type EQUALS exprn SEMICOLON
        ;
func_declaration:
        IDENTIFIER COLON FUNCTION type OPEN_BRACKET param_list CLOSED_BRACKET func_body
        | IDENTIFIER COLON FUNCTION type OPEN_BRACKET CLOSED_BRACKET func_body
        ;

param_list:     
        param_list COMMA param_declaration
        | param_declaration
        ;

param_declaration:
        IDENTIFIER COLON type
        ;
    
func_body: 
        OPEN_CURLY_BRACKET stmt_list CLOSED_CURLY_BRACKET
        ;

stmt_list:
        stmt_list stmt_declaration
        | stmt_declaration
        ;
stmt_declaration:
        var_declaration
        | assign_stmt
        | return_stmt
        | print_stmt
        | read_stmt
        ;

print_stmt:
        PRINT IDENTIFIER SEMICOLON
        | PRINT literal SEMICOLON
        ;

read_stmt:
        READ IDENTIFIER SEMICOLON
        ;

type:   INTEGER
        | VOID
        | BOOLEAN
        | CHARACTER
        ;

literal: INTEGER_LITERAL
        | BOOLEAN_LITERAL
        | CHAR_LITERAL
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
        | literal
        | func_call
        ;

func_call: 
        IDENTIFIER OPEN_BRACKET arg_list CLOSED_BRACKET
        | IDENTIFIER OPEN_BRACKET CLOSED_BRACKET
        ;

arg_list:
        arg_list COMMA exprn
        | exprn
        ;

%%

