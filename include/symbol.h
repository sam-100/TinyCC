#ifndef SYMBOL_H
#define SYMBOL_H

#include "enums.h"
#include "declarations.h"

typedef struct symbol {
    char *name;
    scope_t scope;
    type_t type;
    int which;
    bool init;
} symbol;


symbol *create_symbol(char *name, scope_t scope, type_t type, int which);

symbol *create_symbol_from_parameter(parameter *par, symtab_stack *st);
symbol *create_symbol_from_var_decl(var_decl *vd, symtab_stack *st);
symbol *create_symbol_from_func_decl(func_decl *fd, symtab_stack *st);
symbol *create_symbol_from_var_decl_stmt(var_decl_stmt *vd, symtab_stack *st);
symbol *create_symbol_from_assign_stmt(assign_stmt *as_stmt, symtab_stack *st);
symbol *create_symbol_from_print_stmt(print_stmt *p, symtab_stack *st);
symbol *create_symbol_from_read_stmt(read_stmt *r, symtab_stack *st);
symbol *create_symbol_from_return_stmt(return_stmt *ret_stmt, symtab_stack *st);

void print_symbol(symbol *sym);

#endif