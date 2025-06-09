#ifndef SYMBOL_H
#define SYMBOL_H

#include "enums.h"
#include "declarations.h"

typedef struct symbol {
    char *name;
    type_t type;
    scope_t scope;
    symbol_t kind;
    int which, offset;
    struct symbol *next_param;
} symbol;


symbol *create_symbol(char *name, type_t type, scope_t scope, symbol_t kind, int which, int offset, symbol *param_list);

symbol *create_symbol_var_local(char *name, type_t type, int which, int offset);
symbol *create_symbol_var_global(char *name, type_t type, int which, int offset);
symbol *create_symbol_param(char *name, type_t type, symbol *next_param);
symbol *create_symbol_func(char *name, type_t type, symbol *param_list);

void print_symbol(symbol *sym);

#endif