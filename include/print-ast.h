#ifndef PRINT_AST_H
#define PRINT_AST_H

#include "program.h"
#include "func.h"

/* Now here functions to print the abstract syntax tree */
void print_program(program *p);
void print_decl(decl *d);
void print_var_decl(var_decl *vd);
void print_func_decl(func_decl *fd);
void print_exprn(exprn *e);
void print_param(parameter *p);
void print_body(func_body *fb);

/* Other utility functions */
char *get_type_name(type_t type);
char get_op_name(operator_t op);
char *btoa(bool val);

#endif