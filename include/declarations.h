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

/* symbol table constructs */
typedef struct symbol symbol;
typedef struct symtab symtab;
typedef struct symtab_stack symtab_stack;

/* three address code constructs */
typedef struct tac_stmt tac_stmt;
typedef struct tac_operand tac_operand;

/* Global variables */
extern FILE *f_input, *f_tokens, *f_ast, *f_nowhere, *f_error, *f_symtab, *f_tac;
extern program *root;

#endif