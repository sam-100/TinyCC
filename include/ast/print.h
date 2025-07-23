#ifndef PRINT_AST_H
#define PRINT_AST_H

#include "ast/program.h"
#include "ast/decl.h"
#include "ast/func.h"
#include "ast/stmt.h"
#include "ast/exprn.h"

/* print the program */
void print_program(const program *p);

/* Functions to print declaration */
void print_decl(const decl *d);
void print_var_decl(const var_decl *vd);
void print_func_decl(const func_decl *fd);

/* functions to print statements of various types*/
void print_statement(const statement *stmt, char *tabs);
void print_stmt_var_decl(const var_decl_stmt *vdstmt, char *tabs);
void print_stmt_assignment(const assign_stmt *asstmt, char *tabs);
void print_stmt_func_call(const func_call_stmt *fc_stmt, char *tab);
void print_stmt_print(const print_stmt *p, char *tab);
void print_stmt_read(const read_stmt *r_stmt, char *tabs);
void print_stmt_return(const return_stmt *ret_stmt, char *tabs);

/* Functions to print function body, function call, arguments, and parameters */
void print_arg(const argument *arg, char *tabs);
void print_param(const parameter *p);
void print_func_call(const func_call *fc, char *tabs);
void print_func_body(const func_body *fb);

/* Function to print the expression */
void print_exprn(const exprn *e, char *tabs);


#endif