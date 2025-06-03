#include "symtab_stack.h"
#include <stdlib.h>


symtab_stack *create_symtab_stack() {
    symtab_stack *st = (symtab_stack*)malloc(sizeof(symtab_stack));
    st->top = -1;
    return st;
}

void scope_enter(symtab_stack *st) {
    st->arr[++(st->top)] = create_symtab();
}

void scope_exit(symtab_stack *st) {
    st->top--;
}

void scope_level(symtab_stack *st) {
    return st->top;
}

void scope_bind(char *name, symbol *sym, symtab_stack *st) {
    symtab *tab = st->arr[st->top];
    add_symbol(name, sym, tab);
}

symbol *scope_lookup(char *name, symtab_stack *st) {
    for(int i=st->top; i>=0; i--) {
        symbol *sym = lookup_symbol(name, st->arr[st->top]);
        if(sym)
            return sym;
    }
    return NULL;
}

symbol *scope_lookup_current(char *name, symtab_stack *st) {
    return lookup_symbol(name, st->arr[st->top]);
}
