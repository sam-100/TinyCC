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


symbol *create_symbol(char *name, scope_t scope, type_t type, int which, bool init);

void print_symbol(symbol *sym);

#endif