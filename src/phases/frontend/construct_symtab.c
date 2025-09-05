#include "phases/frontend/construct_symtab.h"

void construct_symtab_program(program *p) {
    symtab_stack *st = create_symtab_stack();
    scope_enter(st);
    construct_symtab_decl(p->decl_list, st);
    p->sym_tab = scope_get_current(st);
    scope_exit(st);
    destroy_symtab_stack(st);
}

void construct_symtab_decl(decl *d, symtab_stack *st) {
    if(d == NULL)
        return;
    
    switch(d->kind)
    {
        case DECL_VAR:
            construct_symtab_var_decl(d->vd, st);
            break;
        case DECL_FUNC:
            construct_symtab_func_decl(d->fd, st);
            break;
    }
    construct_symtab_decl(d->next, st);
}

void construct_symtab_var_decl(var_decl *vd, symtab_stack *st) {
    if(scope_lookup_current(vd->name, st)) {
        fprintf(stderr, "Error: redeclaration of symbol %s at line %d\n", vd->name, vd->line_no);
        return;
    }
    vd->sym = create_symbol_var_global(vd->name, vd->type, -1, -1);
    scope_bind(vd->name, vd->sym, st);
}

void construct_symtab_func_decl(func_decl *fd, symtab_stack *st) {
    // Create a symbol for function name
    if(scope_lookup_current(fd->name, st)) {
        fprintf(stderr, "Error: redeclaration of symbol %s at line %d\n", fd->name, fd->line_no);
        return;
    }
    fd->sym = create_symbol_func(fd->name, fd->type, NULL);
    scope_bind(fd->name, fd->sym, st);

    // scope_enter(st);                        // enter function scope
    scope_enter_func(fd, st);
    construct_symtab_parameter(fd->param_list, st);
    construct_symtab_block_stmt(fd->body, st);
    fd->symtab = scope_get_current(st);       // save function scope
    scope_exit(st);
}

void construct_symtab_func_body(func_body *body, symtab_stack *st) {
    construct_symtab_stmt(body->stmt_list, st);
}

symbol *construct_symtab_parameter(parameter *par, symtab_stack *st) {
    if(par == NULL)
        return NULL;

    if(scope_lookup_current(par->name, st)) {
        fprintf(f_error, "Parameter %s declared again at line no. %d\n", par->name, par->line_no);
        return NULL;
    }

    symbol *sym = create_symbol(par->name, par->type, SCOPE_PARAMETER, SYM_PARAM, -1, -1, NULL);
    scope_bind(par->name, sym, st);
    sym->next_param = construct_symtab_parameter(par->next, st);
    
    par->sym = sym; 
    return sym;
}

void construct_symtab_stmt(statement *stmt, symtab_stack *st) {
    if(stmt == NULL)
        return;
    
    switch(stmt->kind)
    {
        case STMT_VAR_DECL:
            construct_symtab_var_decl_stmt(stmt->vd_stmt, st);
            break;
        case STMT_BLOCK:
            construct_symtab_block_stmt(stmt->blk_stmt, st);
            break;
    }

    construct_symtab_stmt(stmt->next, st);
}

void construct_symtab_block_stmt(block_stmt *stmt, symtab_stack *st) {
    scope_enter(st);
    construct_symtab_stmt(stmt->stmt_list, st);
    stmt->symbol_table = scope_get_current(st);
    scope_pop(st);
}