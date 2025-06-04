#ifndef SYMTAB_STACK_H
#define SYMTAB_STACK_H

#include "symtab.h"

#define MAX_STACK_HEIGHT 10

typedef struct symtab_stack {
    symtab *arr[MAX_STACK_HEIGHT];
    int top;
} symtab_stack;


symtab_stack *create_symtab_stack();
void scope_enter(symtab_stack *st);
void scope_exit(symtab_stack *st);
int scope_level(symtab_stack *st);
scope_t scope_type(symtab_stack *st);
void scope_bind(char *name, symbol *sym, symtab_stack *st);
symbol *scope_lookup(char *name, symtab_stack *st);
symbol *scope_lookup_current(char *name, symtab_stack *st);
symtab *scope_get_current(symtab_stack *st);

#endif
