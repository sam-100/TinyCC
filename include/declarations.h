#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <stdio.h>

typedef struct program program;

typedef struct decl decl;
typedef struct func_decl func_decl;
typedef struct var_decl var_decl;

typedef struct statement statement;
typedef struct print_stmt print_stmt;
typedef struct read_stmt read_stmt;
typedef struct var_decl_stmt var_decl_stmt;
typedef struct func_call_stmt func_call_stmt;
typedef struct assign_stmt assign_stmt;
typedef struct return_stmt return_stmt;

typedef struct exprn exprn;

typedef struct parameter parameter;
typedef struct argument argument;
typedef struct func_call func_call;
typedef struct func_body func_body;

extern FILE *f_ast;


#endif