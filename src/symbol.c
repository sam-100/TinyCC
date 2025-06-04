#include "symbol.h"
#include <stdlib.h>
#include "decl.h"
#include "string.h"

symbol *create_symbol(char *name, scope_t scope, type_t type, int which) {
    symbol *sym = (symbol*)malloc(sizeof(symbol));
    sym->name = name;
    sym->scope=scope;
    sym->type=type;
    sym->which=which;
    return sym;
}

symbol *create_symbol_from_var_decl(var_decl *vd, symtab_stack *st) {
    symbol *sym = (symbol*)malloc(sizeof(symbol));
    sym->name = strdup(vd->name);
    sym->scope = scope_type(st);
    sym->type = vd->type;
    sym->init = vd->initialized;
    return sym;
}

symbol *create_symbol_from_func_decl(func_decl *fd, symtab_stack *st) {
    symbol *sym = (symbol*)malloc(sizeof(symbol));
    sym->name = strdup(fd->name);
    sym->scope = scope_type(st);
    sym->type = fd->type;
    sym->init = (fd->body != NULL);
    return sym;
}

symbol *create_symbol_from_parameter(parameter *par, symtab_stack *st) {
    symbol *sym = create_symbol(par->name, scope_type(st), par->type, -1);
    return sym;
}

symbol *create_symbol_from_var_decl_stmt(var_decl_stmt *vd, symtab_stack *st) {
    return create_symbol_from_var_decl(vd->vd, st);
}

symbol *create_symbol_from_assign_stmt(assign_stmt *as_stmt, symtab_stack *st) {
    symbol *sym = create_symbol(as_stmt->name, scope_type(st), as_stmt->type, -1);
    return sym;
}

symbol *create_symbol_from_print_stmt(print_stmt *p, symtab_stack *st) {
    return NULL;
}

symbol *create_symbol_from_read_stmt(read_stmt *r, symtab_stack *st) {
    return NULL;
}

symbol *create_symbol_from_return_stmt(return_stmt *ret_stmt, symtab_stack *st) {
    return NULL;
}

