#include "symbol_table/symbol.h"
#include <stdlib.h>
#include "ast/decl.h"
#include "string.h"
#include "utils.h"


symbol *create_symbol(char *name, type_t type, scope_t scope, symbol_t kind, int which, int offset, symbol *param_list) {
    symbol *sym = (symbol*)malloc(sizeof(symbol));
    sym->name = name;
    sym->type = type;
    sym->scope = scope;
    sym->kind = kind;
    sym->which = which;
    sym->offset = offset;
    sym->next_param = param_list;
    return sym;
}

symbol *create_symbol_var_local(char *name, type_t type, int which, int offset) {
    symbol *sym = (symbol*)malloc(sizeof(symbol));
    sym->name=name;
    sym->type=type;
    sym->scope=SCOPE_LOCAL;
    sym->kind=SYM_VAR;
    sym->which=which;
    sym->offset=offset;
    sym->next_param=NULL;
    return sym;
}

symbol *create_symbol_var_global(char *name, type_t type, int which, int offset) {
    symbol *sym = (symbol*)malloc(sizeof(symbol));
    sym->name=name;
    sym->type=type;
    sym->scope=SCOPE_GLOBAL;
    sym->kind=SYM_VAR;
    sym->which=which;
    sym->offset=offset;
    sym->next_param=NULL;
    return sym;
}

symbol *create_symbol_param(parameter *param) {
    if(param == NULL)
        return NULL;
    
    symbol *sym = (symbol*)malloc(sizeof(symbol));
    sym->name=param->name;
    sym->type=param->type;
    sym->scope=SCOPE_PARAMETER;
    sym->kind=SYM_PARAM;
    sym->next_param = create_symbol_param(param->next);
    param->sym=sym;
    return sym;
}

symbol *create_symbol_func(char *name, type_t type, symbol *param_list) {
    symbol *sym = (symbol*)malloc(sizeof(symbol));
    sym->name=name;
    sym->type=type;
    sym->scope=SCOPE_GLOBAL;
    sym->kind=SYM_FUNC;
    sym->next_param=param_list;
    return sym;
}


void print_symbol(symbol *sym) {
    fprintf(f_symtab, "{\n");
    fprintf(f_symtab, "\tname: %s;\n", sym->name);
    fprintf(f_symtab, "\ttype: %s;\n", get_type_name(sym->type));
    fprintf(f_symtab, "\tkind: %s;\n", get_symbol_kind_name(sym->kind));
    fprintf(f_symtab, "\tscope: %s;\n", get_scope_name(sym->scope));
    // fprintf(f_symtab, "\taddress: %p;\n", sym);

    switch(sym->kind)
    {
        case SYM_VAR:
            fprintf(f_symtab, "\twhich: %d;\n", sym->which);
            fprintf(f_symtab, "\toffset: %d;\n", sym->offset);
        
        case SYM_FUNC:
            fprintf(f_symtab, "\tparameters: \n");
            for(symbol *ptr=sym->next_param; ptr != NULL; ptr=ptr->next_param) {
                fprintf(f_symtab, "\t\tparameter %d [%d]: %s: %s\n", ptr->which, ptr->offset, ptr->name, get_type_name(ptr->type));
            }
            break;
        case SYM_PARAM:
            fprintf(f_symtab, "\twhich: %d;\n", sym->which);
            fprintf(f_symtab, "\toffset: %d;\n", sym->offset);
            break;            
        default:
            fprintf(f_symtab, "Unknown kind of symbol\n");
            break;
    }
    fprintf(f_symtab, "}\n");
}

const char *codegen_symbol(symbol *sym) {
    // TODO: 
}