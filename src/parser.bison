%{
#include <stdio.h>
#include <stdbool.h>
#include "ast/decl.h"
#include "ast/stmt.h"
#include "ast/exprn.h"
#include "ast/func.h"
#include "ast/program.h"
#include "utils.h"

extern int yylex(void);
extern int yyerror(const char *msg);
extern program *root;
%}

// Here tokens -->
%token INTEGER CHARACTER BOOLEAN VOID FUNCTION RETURN       
%token PRINT READ                          
%token IF ELSE
%token IDENTIFIER INTEGER_LITERAL BOOLEAN_LITERAL CHAR_LITERAL
%token COLON SEMICOLON SINGLE_QUOTE DOUBLE_QUOTE COMMA DOT          
%token AND OR NOT                                               // boolean operators
%token PLUS MINUS MULTIPLY DIVIDE                               // arithmetic operators
%token LT GT EQ LE GE                                           // comparison operators
%token ASSIGN                                                   // '=' assignment operator
%token OPEN_BRACKET CLOSED_BRACKET 
%token OPEN_SQUARE_BRACKET CLOSED_SQUARE_BRACKET
%token OPEN_CURLY_BRACKET CLOSED_CURLY_BRACKET 

%left AND OR NOT
%left LT LE EQ GT GE
%left PLUS MINUS
%left MULTIPLY DIVIDE
%right UMINUS

%type <p> program
%type <d> global_decl_list
%type <vd> var_decl
%type <fd> func_decl
%type <fc> func_call
%type <i_val> type
%type <stmt> stmt_list statement
%type <e> exprn literal
%type <param> param_list param_declaration
%type <arg> arg_list argument
%type <as_stmt> assign_stmt
%type <vd_stmt> var_decl_stmt
%type <fc_stmt> func_call_stmt
%type <ret_stmt> return_stmt
%type <if_stmt> if_stmt;
%type <p_stmt> print_stmt
%type <r_stmt> read_stmt
%type <b_stmt> block_stmt

%type <s_val> IDENTIFIER
%type <i_val> INTEGER VOID BOOLEAN CHARACTER
%type <i_val> INTEGER_LITERAL
%type <b_val> BOOLEAN_LITERAL
%type <c_val> CHAR_LITERAL


%locations

%union {
        struct program *p;
        struct decl *d;
        struct func_decl *fd;
        struct var_decl *vd;
        struct statement *stmt;
        struct print_stmt *p_stmt;
        struct read_stmt *r_stmt;
        struct if_stmt *if_stmt;
        struct var_decl_stmt *vd_stmt;
        struct func_call_stmt *fc_stmt;
        struct return_stmt *ret_stmt;
        struct assign_stmt *as_stmt;
        struct block_stmt *b_stmt;
        struct exprn *e;
        struct func_call *fc;
        struct parameter *param;
        struct argument *arg;
        int i_val;
        bool b_val;
        char c_val;
        char *s_val;
};

%start program

%%

program:  
        global_decl_list                                { root = create_program($1); }
        ;

global_decl_list: 
                global_decl_list func_decl              { $$ = append_decl($1, create_decl_from_func($2)); }
                | global_decl_list var_decl             { $$ = append_decl($1, create_decl_from_var($2)); }
                | func_decl                             { $$ = create_decl_from_func($1); }
                | var_decl                              { $$ = create_decl_from_var($1); }
                ;


var_decl:
        IDENTIFIER COLON type SEMICOLON                 { 
                                                                $$ = create_var_decl($1, $3, NULL); 
                                                                $$->line_no = @1.first_line;
                                                        }
        | IDENTIFIER COLON type ASSIGN literal SEMICOLON  { 
                                                                $$ = create_var_decl($1, $3, $5); 
                                                                $$->line_no = @1.first_line;
                                                        }
        ;

func_decl:
        IDENTIFIER COLON FUNCTION type OPEN_BRACKET param_list CLOSED_BRACKET SEMICOLON         { 
                                                                                                        $$ = create_func_decl($1, $4, $6, NULL); 
                                                                                                        $$->line_no = @1.first_line;
                                                                                                }
        | IDENTIFIER COLON FUNCTION type OPEN_BRACKET param_list CLOSED_BRACKET block_stmt      {
                                                                                                        $$ = create_func_decl($1, $4, $6, $8); 
                                                                                                        $$->line_no = @1.first_line;
                                                                                                }
        ;

type:   INTEGER                                 { $$ = get_type($1); }
        | VOID                                  { $$ = get_type($1); }
        | BOOLEAN                               { $$ = get_type($1); }
        | CHARACTER                             { $$ = get_type($1); }
        ;

exprn:  
        OPEN_BRACKET exprn CLOSED_BRACKET       { 
                                                        $$ = $2; 
                                                }
        | exprn PLUS exprn                      { 
                                                        $$ = create_exprn($1, OP_PLUS, $3); 
                                                        $$->line_no = @2.first_line;
                                                }
        | exprn MINUS exprn                     { 
                                                        $$ = create_exprn($1, OP_MINUS, $3); 
                                                        $$->line_no = @2.first_line;
                                                }
        | exprn MULTIPLY exprn                  { 
                                                        $$ = create_exprn($1, OP_MUL, $3); 
                                                        $$->line_no = @2.first_line;
                                                }
        | exprn DIVIDE exprn                    { 
                                                        $$ = create_exprn($1, OP_DIV, $3); 
                                                        $$->line_no = @2.first_line;
                                                }
        | MINUS exprn %prec UMINUS              { 
                                                        $$ = negate_exprn($2); 
                                                        $$->line_no = @1.first_line;
                                                }
        | exprn AND exprn                       {
                                                        $$ = create_exprn($1, OP_AND, $3);
                                                        $$->line_no = @2.first_line;
                                                }
        | exprn OR exprn                        {
                                                        $$ = create_exprn($1, OP_OR, $3);
                                                        $$->line_no = @2.first_line;
                                                }
        | NOT exprn                             {
                                                        $$ = create_not_exprn($2);
                                                        $$->line_no = @2.first_line;
                                                }
        | exprn GT exprn                        {
                                                        $$ = create_exprn($1, OP_GT, $3);
                                                        $$->line_no = @2.first_line;
                                                }
        | exprn GE exprn                        {
                                                        $$ = create_exprn($1, OP_GE, $3);
                                                        $$->line_no = @2.first_line;
                                                }
        | exprn EQ exprn                        {
                                                        $$ = create_exprn($1, OP_EQ, $3);
                                                        $$->line_no = @2.first_line;
                                                }
        | exprn LE exprn                        {
                                                        $$ = create_exprn($1, OP_LE, $3);
                                                        $$->line_no = @2.first_line;
                                                }
        | exprn LT exprn                        {
                                                        $$ = create_exprn($1, OP_LT, $3);
                                                        $$->line_no = @2.first_line;
                                                }
        | IDENTIFIER                            { 
                                                        $$ = create_exprn_id($1); 
                                                        $$->line_no = @1.first_line;
                                                }
        | literal                               { 
                                                        $$ = $1; 
                                                }
        ;

param_list:     
        param_list COMMA param_declaration              { $$ = append_param($1, $3); }
        | param_declaration                             { $$ = $1; }
        |                                               { $$ = NULL; }
        ;


param_declaration:
        IDENTIFIER COLON type                           { 
                                                                $$ = create_param($1, $3); 
                                                                $$->line_no = @1.first_line; 
                                                        }
        ;

stmt_list:
        stmt_list statement                             { $$ = append_stmt($1, $2); }
        | statement                                     { $$ = $1; }
        ;


statement:
        var_decl_stmt                           { $$ = create_stmt_from_var_decl($1); }
        | assign_stmt                           { $$ = create_stmt_from_assign($1); }
        | return_stmt                           { $$ = create_stmt_from_return($1); }
        | print_stmt                            { $$ = create_stmt_from_print($1); }
        | read_stmt                             { $$ = create_stmt_from_read($1); }
        | func_call_stmt                        { $$ = create_stmt_from_func_call($1); }
        | block_stmt                            { $$ = create_stmt_from_block($1); }
        | if_stmt                               { $$ = create_stmt_from_if($1); }
        ;

if_stmt:
        IF OPEN_BRACKET exprn CLOSED_BRACKET block_stmt         { 
                                                                        $$ = create_if_stmt($3, $5); 
                                                                        $$->line_no = @1.first_line;
                                                                }


var_decl_stmt:
        IDENTIFIER COLON type SEMICOLON                         { 
                                                                        $$ = create_var_decl_stmt($1, $3, NULL); 
                                                                        $$->line_no = @1.first_line;
                                                                }
        | IDENTIFIER COLON type ASSIGN exprn SEMICOLON          { 
                                                                        $$ = create_var_decl_stmt($1, $3, $5); 
                                                                        $$->line_no = @1.first_line;
                                                                }
        ;


print_stmt:
        PRINT exprn SEMICOLON                   { 
                                                        $$ = create_print_stmt($2); 
                                                        $$->line_no = @1.first_line;
                                                }
        ;

read_stmt:
        READ IDENTIFIER SEMICOLON               { 
                                                        $$ = create_read_stmt($2); 
                                                        $$->line_no = @1.first_line;
                                                }
        ;

func_call_stmt: 
        IDENTIFIER OPEN_BRACKET arg_list CLOSED_BRACKET SEMICOLON               { 
                                                                                        $$ = create_func_call_stmt($1, $3); 
                                                                                        $$->line_no = @1.first_line;
                                                                                }
        ;

literal: INTEGER_LITERAL                        { 
                                                        $$ = create_exprn_int($1); 
                                                        $$->line_no = @1.first_line;
                                                }
        | BOOLEAN_LITERAL                       { 
                                                        $$ = create_exprn_bool($1); 
                                                        $$->line_no = @1.first_line;
                                                }
        | CHAR_LITERAL                          { 
                                                        $$ = create_exprn_char($1); 
                                                        $$->line_no = @1.first_line;
                                                }
        ;

assign_stmt:
        IDENTIFIER ASSIGN exprn SEMICOLON       { 
                                                        $$ = create_assign_stmt_from_exprn($1, $3); 
                                                        $$->line_no=@1.first_line;
                                                }
        | IDENTIFIER ASSIGN func_call SEMICOLON { 
                                                        $$ = create_assign_stmt_from_func_call($1, $3); 
                                                        $$->line_no=@1.first_line;
                                                }
        ;

return_stmt:
        RETURN exprn SEMICOLON                  { 
                                                        $$ = create_ret_stmt($2); 
                                                        $$->line_no = @1.first_line; 
                                                }
        | RETURN SEMICOLON                      {
                                                        $$ = create_ret_stmt(NULL);
                                                        $$->line_no = @1.first_line;
                                                }
        ;

block_stmt:
        OPEN_CURLY_BRACKET stmt_list CLOSED_CURLY_BRACKET       {
                                                                        $$ = create_block_stmt($2);
                                                                        $$->line_no = @1.first_line;
                                                                }

func_call: 
        IDENTIFIER OPEN_BRACKET arg_list CLOSED_BRACKET         { 
                                                                        $$ = create_func_call($1, $3); 
                                                                        $$->line_no = @1.first_line;
                                                                }
        ;

arg_list:
        arg_list COMMA argument                 { $$ = append_arg($1, $3); }
        | argument                              { $$ = $1; }
        |                                       { $$ = NULL; }
        ;

argument:
        exprn                                   { 
                                                        $$ = create_arg($1); 
                                                        $$->line_no = $1->line_no; 
                                                }
        ;

%%

