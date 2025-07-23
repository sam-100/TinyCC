#include "symbol_table/symtab.h"
#include <stdlib.h>
#include <string.h>

symtab *create_symtab() {
    symtab *s = (symtab*)malloc(sizeof(symtab));
    s->size = 0;
    s->fd = NULL;
    return s;
}

void add_symbol(char *name, symbol *sym, symtab *table) {
    table->names[table->size] = strdup(name);
    table->symbols[table->size] = sym;
    table->size++;    
}

symbol *lookup_symbol(const char *name, symtab *table) {
    for(int i=0; i<table->size; i++) {
        if(strcmp(table->names[i], name) == 0)
            return table->symbols[i];
    }
    return NULL;
}

void remove_symbol(char *name, symtab *table) {
    int index = -1;
    for(int i=0; i<table->size; i++) {
        if(strcmp(table->names[i], name) == 0) {
            index = i;
            break;
        }
    }

    if(index == -1) {
        printf("Symbol %s to be removed not found!\n", name);
        return;
    }

    for(int i=index; i<table->size-1; i++) {
        table->names[i] = table->names[i+1];
        table->symbols[i] = table->symbols[i+1];
    }

    table->size--;
}

