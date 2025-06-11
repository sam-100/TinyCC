#ifndef SYMTAB_H
#define SYMTAB_H

#include "symbol.h"
#include "declarations.h"

#define MAX_SYMBOLS 100

typedef struct symtab {
    char *names[MAX_SYMBOLS];
    symbol *symbols[MAX_SYMBOLS];
    int size;
    func_decl *fd;
} symtab;


symtab *create_symtab();
void print_symtab(symtab *stab);

void add_symbol(char *name, symbol *sym, symtab *table);
symbol *lookup_symbol(char *name, symtab *table);
void remove_symbol(char *name, symtab *table);


#endif