#include "phases/frontend/resolve_name.h"
#include <stdlib.h>


void resolve_program(program *p) {
    symtab_stack *st = create_symtab_stack();
    
    scope_push(p->sym_tab, st);
    resolve_decl(p->decl_list, st);
    scope_exit(st);

    destroy_symtab_stack(st);
}

void resolve_decl(decl *d, symtab_stack *st) {
    if(d == NULL)
        return;
    
    switch(d->kind)
    {
        case DECL_VAR:
            resolve_var_decl(d->vd, st);
            break;
        case DECL_FUNC:
            resolve_func_decl(d->fd, st);
            break;
    }
    resolve_decl(d->next, st);
}

void resolve_var_decl(var_decl *vd, symtab_stack *st) {    
    if(vd->initialized)
        resolve_exprn(vd->rhs, st);
}

void resolve_func_decl(func_decl *fd, symtab_stack *st) {
    // fd->sym->next_param = create_symbol_param(fd->param_list);
    
    scope_push(fd->symtab, st);        // enter function scope
    for(parameter *p=fd->param_list; p != NULL; p=p->next) {
        p->sym = scope_lookup(p->name, st);
    }
    if(fd->param_list)
        fd->sym->next_param = scope_lookup(fd->param_list->name, st);

    if(fd->body)    
        resolve_func_body(fd->body, st);
    scope_pop(st);         // exit function scope
    return;
}

void resolve_arg(argument *arg, symtab_stack *st) {
    if(arg == NULL)
        return;
    
    resolve_exprn(arg->e, st);
    arg->sym = arg->e->sym;

    resolve_arg(arg->next, st);
}

void resolve_func_call(func_call *fc, symtab_stack *st) {
    if(scope_lookup(fc->name, st) == false) {
        fprintf(f_error, "Error: undeclared function '%s' called at line no. %d\n", fc->name, fc->line_no);
        exit(1);
    }
    
    fc->sym = scope_lookup(fc->name, st);
    resolve_arg(fc->arg_list, st);
}

void resolve_func_body(func_body *fb, symtab_stack *st) {
    resolve_stmt(fb->stmt_list, st);
    fb->symtab = scope_get_current(st);
}



void resolve_var_decl_stmt(var_decl_stmt *vd_stmt, symtab_stack *st) {
    if(vd_stmt->initialized)
        resolve_exprn(vd_stmt->rhs, st);
}

void resolve_assign_stmt(assign_stmt *as_stmt, symtab_stack *st) {
    // check for previous definition of lhs
    if(scope_lookup(as_stmt->name, st) == false) {
        fprintf(f_error, "Symbol %s at line no. %d is not defined before\n", as_stmt->name, as_stmt->line_no);
        exit(1);
    }
    as_stmt->sym = scope_lookup(as_stmt->name, st);

    // resolving rhs 
    switch(as_stmt->kind)
    {
        case ASSIGN_EXPRN:
            resolve_exprn(as_stmt->e, st);
            break;
        case ASSIGN_FUNC_CALL:
            resolve_func_call(as_stmt->fc, st);
            break;
    }
    return;
}

void resolve_func_call_stmt(func_call_stmt *fc_stmt, symtab_stack *st) {
    // check if function is defined before
    if(scope_lookup(fc_stmt->name, st) == false) {
        fprintf(f_error, "Error: undeclared function '%s' called at line no. %d\n", fc_stmt->name, fc_stmt->line_no);
        exit(1);
    }
    fc_stmt->sym = scope_lookup(fc_stmt->name, st);

    resolve_arg(fc_stmt->args, st);
}

void resolve_print_stmt(print_stmt *p_stmt, symtab_stack *st) {
    resolve_exprn(p_stmt->arg, st);
}


void resolve_read_stmt(read_stmt *r_stmt, symtab_stack *st) {
    if(scope_lookup(r_stmt->arg, st) == false) {
        fprintf(f_error, "Reading into undeclared symbol '%s' at line_no: %d\n", r_stmt->arg, r_stmt->line_no);
        exit(1);
    }
    // r_stmt->sym = scope_lookup(r_stmt->arg, st);
}

void resolve_ret_stmt(return_stmt *ret_stmt, symtab_stack *st) {
    resolve_exprn(ret_stmt->ret_expr, st);
    if(ret_stmt->ret_expr)
        ret_stmt->sym = ret_stmt->ret_expr->sym;
    ret_stmt->fd = scope_get_curr_func(st);
    return;
}


void resolve_stmt(statement *stmt, symtab_stack *st) {
    if(stmt == NULL)
        return;
    
    switch(stmt->kind)
    {
        case STMT_VAR_DECL:
            resolve_var_decl_stmt(stmt->vd_stmt, st);
            break;
        case STMT_ASSIGN:
            resolve_assign_stmt(stmt->as_stmt, st);
            break;
        case STMT_FUNC_CALL:
            resolve_func_call_stmt(stmt->fc_stmt, st);
            break;
        case STMT_PRINT:
            resolve_print_stmt(stmt->p_stmt, st);
            break;
        case STMT_READ:
            resolve_read_stmt(stmt->r_stmt, st);
            break;
        case STMT_RETURN:
            resolve_ret_stmt(stmt->ret_stmt, st);
            break;
    }

    resolve_stmt(stmt->next, st);
}

void resolve_exprn(exprn *e, symtab_stack *st) {
    if(e == NULL)
        return;
    
    if(e->kind == ARITHMETIC_EXPRN || e->kind == BOOLEAN_EXPRN || e->kind == COMPARISON_EXPRN) {
        resolve_exprn(e->left, st);
        resolve_exprn(e->right, st);
        return;
    }

    if(e->kind == IDENTIFIER_EXPRN) {
        if(scope_lookup(e->name, st) == false) {
            fprintf(f_error, "Error: Symbol %s at line no. %d not declared before.\n", e->name, e->line_no);
            exit(1);
        }
        e->sym = scope_lookup(e->name, st);
        return;
    }

    if(e->kind == LITERAL_EXPRN) {
        // todo: handle literal expressions here
    }
}
