#ifndef SYMBOL_H
#define SYMBOL_H

#include "enums.h"


typedef struct symbol {
    char *name;
    symbol_t kind;
    type_t type;
    int which;
} symbol;


symbol *create_symbol(char *name, symbol_t kind, type_t type, int which);



#endif