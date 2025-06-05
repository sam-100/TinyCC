#ifndef SYMBOL_H
#define SYMBOL_H

#include "enums.h"
#include "declarations.h"

typedef struct symbol {
    char *name;
    scope_t scope;
    type_t type;
    symbol_t sym_type;
    int which, offset;
    bool init;
} symbol;


symbol *create_symbol(char *name, symbol_t sym_type, scope_t scope, type_t type, int which, int offset, bool init);

void print_symbol(symbol *sym);

#endif