#include "symbol_table/symtab_stack.h"
#include <stdlib.h>
#include "symbol_table/print.h"


symtab_stack *create_symtab_stack() {
    symtab_stack *st = (symtab_stack*)malloc(sizeof(symtab_stack));
    st->top = -1;
    return st;
}

void destroy_symtab_stack(symtab_stack *st) {
    free(st);
}

void scope_enter(symtab_stack *st) {
    st->arr[++(st->top)] = create_symtab();
}

void scope_enter_func(func_decl *fd, symtab_stack *st) {
    scope_enter(st);
    scope_get_current(st)->fd = fd;
}
void scope_exit(symtab_stack *st) {
    st->top--;
}

int scope_level(symtab_stack *st) {
    return st->top+1;
}

scope_t scope_type(symtab_stack *st) {
    if(scope_level(st) == 1)
        return SCOPE_GLOBAL;
    return SCOPE_LOCAL;
}

void scope_bind(char *name, symbol *sym, symtab_stack *st) {
    symtab *tab = st->arr[st->top];
    add_symbol(name, sym, tab);
}

symbol *scope_lookup(const char *name, symtab_stack *st) {
    for(int i=st->top; i>=0; i--) {
        symbol *sym = lookup_symbol(name, st->arr[i]);
        if(sym)
            return sym;
    }

    fprintf(f_error, "symbol %s not found!\n", name);
    return NULL;
}

symbol *scope_lookup_current(const char *name, symtab_stack *st) {
    return lookup_symbol(name, st->arr[st->top]);
}

symtab *scope_get_current(symtab_stack *st) {
    if(st->top == -1)
        return NULL;
    return st->arr[st->top];
}

func_decl *scope_get_curr_func(symtab_stack *st) {
    for(int i=st->top; i >= 0; i--) {
        if(st->arr[i]->fd != NULL)
            return st->arr[i]->fd;
    }
    return NULL;
}

void scope_push(symtab *stab, symtab_stack *st) {
    st->arr[++st->top] = stab;
}

void scope_pop(symtab_stack *st) {
    st->top--;
}