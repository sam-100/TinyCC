#include "symbol.h"
#include <stdlib.h>

symbol *create_symbol(char *name, symbol_t kind, type_t type, int which) {
    symbol *sym = (symbol*)malloc(sizeof(symbol));
    sym->name = name;
    sym->kind=kind;
    sym->type=type;
    sym->which=which;
    return sym;
}



