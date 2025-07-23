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


const char *codegen_symbol(symbol *sym) {
    // TODO: 
}