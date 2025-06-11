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
    int which;
    int offset;
    struct parameter *next;
} parameter;

typedef struct argument {
    exprn *e;
    int line_no;
    symbol *sym;
    int which;
    struct argument *next;
} argument;


typedef struct func_call {
    char *name;
    argument *arg_list;
    int line_no;
    symbol *sym;
    type_t type;
} func_call;


typedef struct func_body {
    statement *stmt_list;
    symtab *symtab;
} func_body;


argument *create_arg(exprn *e);
argument *append_arg(argument *a, argument *na);
void print_arg(argument *arg, char *tabs);
void arg_resolve(argument *arg, symtab_stack *st);

parameter *create_param(char *name, type_t type);
parameter *append_param(parameter *p, parameter *np);
void print_param(parameter *p);
symbol *parameter_construct_symtab(parameter *par, symtab_stack *st);

func_call *create_func_call(char *name, argument *arg_list);
void print_func_call(func_call *fc, char *tabs);
void func_call_resolve(func_call *fc, symtab_stack *st);
void func_call_typecheck(func_call *fc, symtab_stack *st);

func_body *create_func_body(statement *stmt_list);
void print_func_body(func_body *fb);
void func_body_construct_symtab(func_body *body, symtab_stack *st);
void func_body_resolve(func_body *fb, symtab_stack *st);
void func_body_typecheck(func_body *fb, symtab_stack *st);




#endif