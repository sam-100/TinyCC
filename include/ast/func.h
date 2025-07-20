#ifndef FUNC_H
#define FUNC_H

#include "ast/enums.h"
#include "ast/exprn.h"
#include "ast/stmt.h"
#include "symbol_table/symtab_stack.h"

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
    int local_len, temp_cnt;
} func_body;


argument *create_arg(exprn *e);
argument *append_arg(argument *a, argument *na);
void print_arg(argument *arg, char *tabs);
void resolve_arg(argument *arg, symtab_stack *st);

parameter *create_param(char *name, type_t type);
parameter *append_param(parameter *p, parameter *np);
void print_param(parameter *p);
symbol *construct_symtab_parameter(parameter *par, symtab_stack *st);

func_call *create_func_call(char *name, argument *arg_list);
void print_func_call(func_call *fc, char *tabs);
void resolve_func_call(func_call *fc, symtab_stack *st);
void typecheck_func_call(func_call *fc, symtab_stack *st);

func_body *create_func_body(statement *stmt_list);
void print_func_body(func_body *fb);
void construct_symtab_func_body(func_body *body, symtab_stack *st);
void resolve_func_body(func_body *fb, symtab_stack *st);
void typecheck_func_body(func_body *fb, symtab_stack *st);
void memory_layout_func_body(func_body *fb);

tac_operand *generate_tac_for_func_call(func_call *fc, symtab_stack *st, tac_stmt *code, int *temp_cnt);
void generate_tac_for_func_argument(argument *arg, symtab_stack *s, tac_stmt *code, int *temp_cnt);

#endif