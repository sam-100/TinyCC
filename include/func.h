#ifndef FUNC_H
#define FUNC_H

#include "enums.h"
#include "exprn.h"
#include "stmt.h"
#include "symtab_stack.h"

typedef struct parameter {
    char *name;
    type_t type;
    symbol *sym;
    int line_no;
    struct parameter *next;
} parameter;

typedef struct argument {
    exprn *e;
    int line_no;
    symbol *sym;
    struct argument *next;
} argument;

// function call:- 
typedef struct func_call {
    char *name;
    argument *arg_list;
    int line_no;
    symbol *sym;
} func_call;

// function body:- 
typedef struct func_body {
    statement *stmt_list;
    symtab *symtab;
} func_body;


argument *create_arg(exprn *e);
argument *append_arg(argument *a, argument *na);
void print_arg(argument *arg, char *tabs);

parameter *create_param(char *name, type_t type);
parameter *append_param(parameter *p, parameter *np);
void print_param(parameter *p);

func_call *create_func_call(char *name, argument *arg_list);
func_body *create_func_body(statement *stmt_list);
void print_func_call(func_call *fc, char *tabs);
void print_func_body(func_body *fb);

void func_call_resolve(func_call *fc, symtab_stack *st);
void func_body_resolve(func_body *fb, symtab_stack *st);
void parameter_resolve(parameter *par, symtab_stack *st);
void arg_resolve(argument *arg, symtab_stack *st);

#endif