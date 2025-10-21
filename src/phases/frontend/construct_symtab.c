#include "phases/frontend/construct_symtab.h"
#include "stdlib.h"

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
    fd->symtab = fd->body->symbol_table;       // save function scope
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
        case STMT_IF:
            construct_symtab_if_stmt(stmt->if_stmt, st);
            break;
        case STMT_FOR:
            construct_symtab_for_stmt(stmt->for_stmt, st);
            break;
        case STMT_WHILE:
            construct_symtab_while_stmt(stmt->while_stmt, st);
            break;
        default:
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

void construct_symtab_if_stmt(if_stmt *stmt, symtab_stack *st) {
    construct_symtab_exprn(stmt->condition, st);
    construct_symtab_block_stmt(stmt->block, st);
}

void construct_symtab_for_stmt(for_stmt *stmt, symtab_stack *st) {
    construct_symtab_exprn(stmt->init, st);
    construct_symtab_exprn(stmt->cond, st);
    construct_symtab_exprn(stmt->update, st);
    construct_symtab_block_stmt(stmt->block, st);
}

void construct_symtab_while_stmt(while_stmt *stmt, symtab_stack *st) {
    construct_symtab_exprn(stmt->condition, st);
    construct_symtab_block_stmt(stmt->block, st);
}

void construct_symtab_exprn(exprn *e, symtab_stack *st) {
    if(e == NULL)
        return;
    
    switch(e->kind)
    {
        case ARITHMETIC_EXPRN:
        case COMPARISON_EXPRN:
        case BOOLEAN_EXPRN:
            construct_symtab_exprn(e->left, st);
            construct_symtab_exprn(e->right, st);
            break;
        case ASSIGNMENT_EXPRN:
            {
                symbol *sym = scope_lookup_current(e->name, st);
                if(sym == NULL) {
                    fprintf(f_error, "Error: variable %s used before declaration at line no. %d\n", e->name, e->line_no);
                    exit(1);
                }
                e->sym = sym;
                construct_symtab_exprn(e->right, st);
            }
            break;
        case IDENTIFIER_EXPRN:
            {
                symbol *sym = scope_lookup_current(e->name, st);
                if(sym == NULL) {
                    fprintf(f_error, "Error: variable %s used before declaration at line no. %d\n", e->name, e->line_no);
                    exit(1);
                }
                e->sym = sym;
            }
            break;
        case LITERAL_EXPRN:
        case UNKNOWN_EXPRN:
            break;
    }
}

