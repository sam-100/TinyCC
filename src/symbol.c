#include "symbol.h"
#include <stdlib.h>
#include "decl.h"
#include "string.h"
#include "utils.h"


symbol *create_symbol(char *name, symbol_t sym_type, scope_t scope, type_t type, int which, int offset, bool init) {
    symbol *sym = (symbol*)malloc(sizeof(symbol));
    sym->name = name;
    sym->scope=scope;
    sym->type=type;
    sym->which=which;
    sym->init = init;
    sym->sym_type = sym_type;
    sym->offset = offset;
    return sym;
}


void print_symbol(symbol *sym) {
    fprintf(f_symtab, "{\n");
    fprintf(f_symtab, "\tname: %s;\n", sym->name);
    fprintf(f_symtab, "\ttype: %s;\n", get_type_name(sym->type));
    fprintf(f_symtab, "\tscope: %s;\n", get_scope_name(sym->scope));
    fprintf(f_symtab, "\tinit: %s;\n", btoa(sym->init));
    fprintf(f_symtab, "\twhich: %d;\n", sym->which);
    fprintf(f_symtab, "\toffset: %d;\n", sym->offset);
    fprintf(f_symtab, "}\n");
}