#ifndef PRINT_AST_H
#define PRINT_AST_H

#include "ast/program.h"
#include "ast/decl.h"
#include "ast/func.h"
#include "ast/stmt.h"
#include "ast/exprn.h"

/* print the program */
void print_program(program *p);

/* Functions to print declaration */
void print_decl(decl *d);
void print_var_decl(var_decl *vd);
void print_func_decl(func_decl *fd);

/* functions to print statements of various types*/
void print_statement(statement *stmt, char *tabs);
void print_stmt_var_decl(var_decl_stmt *vdstmt, char *tabs);
void print_stmt_assignment(assign_stmt *asstmt, char *tabs);
void print_stmt_func_call(func_call_stmt *fc_stmt, char *tab);
void print_stmt_print(print_stmt *p, char *tab);
void print_stmt_read(read_stmt *r_stmt, char *tabs);
void print_stmt_return(return_stmt *ret_stmt, char *tabs);

/* Functions to print function body, function call, arguments, and parameters */
void print_arg(argument *arg, char *tabs);
void print_param(parameter *p);
void print_func_call(func_call *fc, char *tabs);
void print_func_body(func_body *fb);

/* Function to print the expression */
void print_exprn(exprn *e, char *tabs);


#endif