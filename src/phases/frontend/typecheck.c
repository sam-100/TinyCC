#include "phases/frontend/typecheck.h"
#include <stdlib.h>
#include "utils.h"

void typecheck_program(program *p) {
    symtab_stack *st = create_symtab_stack();

    scope_push(p->sym_tab, st);
    typecheck_decl(p->decl_list, st);
    scope_pop(st);
    
    free(st);
    return;
}

void typecheck_decl(decl *d, symtab_stack *st) {
    if(d == NULL)
        return;
    
    switch(d->kind)
    {
        case DECL_VAR:
            typecheck_var_decl(d->vd, st);
            break;
        case DECL_FUNC:
            typecheck_func_decl(d->fd, st);
            break;
    }
    typecheck_decl(d->next, st);
}

void typecheck_func_decl(func_decl *fd, symtab_stack *st) {
    typecheck_func_body(fd->body, st);
}

void typecheck_var_decl(var_decl *vd, symtab_stack *st) {
    if(vd->initialized == false)
        return;
    
    typecheck_exprn(vd->rhs, st);
    if(vd->type != vd->rhs->type) {
        fprintf(f_error, "Error: Variable %s of type %s assigned incompatable exprn of type %s at line no: %d", vd->name, get_type_name(vd->type), get_type_name(vd->rhs->type), vd->line_no);
        exit(2);
    }
}

void typecheck_stmt(statement *stmt, symtab_stack *st) {
    if(stmt == NULL)
        return;

    switch(stmt->kind)
    {
        case STMT_VAR_DECL:
            typecheck_var_decl_stmt(stmt->vd_stmt, st);
            break;
        case STMT_ASSIGN:
            typecheck_assign_stmt(stmt->as_stmt, st);
            break;
        case STMT_FUNC_CALL:
            typecheck_func_call_stmt(stmt->fc_stmt, st);
            break;
        case STMT_PRINT:
            typecheck_print_stmt(stmt->p_stmt, st);
            break;
        case STMT_READ:
            typecheck_read_stmt(stmt->r_stmt, st);
            break;
        case STMT_RETURN:
            typecheck_ret_stmt(stmt->ret_stmt, st);
            break;
    }

    typecheck_stmt(stmt->next, st);
}

void typecheck_var_decl_stmt(var_decl_stmt *vd_stmt, symtab_stack *st) {
    if(vd_stmt->initialized == false)
        return;
    
    typecheck_exprn(vd_stmt->rhs, st);
    if(vd_stmt->type != vd_stmt->rhs->type) {
        fprintf(f_error, "Error: Varialbe of type %s initialized with expression of type %s.\n", get_type_name(vd_stmt->type), get_type_name(vd_stmt->rhs->type));
        exit(2);
    }
}

void typecheck_assign_stmt(assign_stmt *as_stmt, symtab_stack *st) {
    type_t type = scope_lookup(as_stmt->name, st)->type;
    switch(as_stmt->kind)
    {
        case ASSIGN_EXPRN:
            typecheck_exprn(as_stmt->e, st);
            if(type != as_stmt->e->type) {
                fprintf(f_error, "Error (line_no %d): Varialbe of type %s assigned with expression of type %s.\n", as_stmt->line_no, get_type_name(as_stmt->type), get_type_name(as_stmt->e->type));
                exit(2);
            }
            break;
        case ASSIGN_FUNC_CALL:
            typecheck_func_call(as_stmt->fc, st);
            if(type != as_stmt->fc->sym->type) {
                fprintf(f_error, "Error (line_no %d): Varialbe of type %s assigned with function call with return type %s.\n", as_stmt->line_no, get_type_name(as_stmt->type), get_type_name(as_stmt->fc->sym->type));
                exit(2);
            }
            break;

    }
}

void typecheck_func_call_stmt(func_call_stmt *fc_stmt, symtab_stack *st) {
    symbol *func_decl_symbol = lookup_symbol(fc_stmt->name, root->sym_tab);
    argument *arg = fc_stmt->args;
    symbol *param = func_decl_symbol->next_param;

    while(arg != NULL && param != NULL) {
        if(arg->e->type != param->type) {
            fprintf(f_error, "Error (line_no %d): parameter '%s' of type %s can't be initialized with argument of type %s.\n", fc_stmt->line_no, param->name, get_type_name(param->type), get_type_name(fc_stmt->type));
            exit(2);
        }
        arg = arg->next;
        param = param->next_param;
    }

    if(arg != NULL) {
        fprintf(f_error, "Error (line_no %d): too many arguments to function %s.\n", fc_stmt->line_no, fc_stmt->name);
        exit(2);
    }
    if(param != NULL) {
        fprintf(f_error, "Error (line_no %d): too few arguments to function call %s.\n", fc_stmt->line_no, fc_stmt->name);
    }
}

void typecheck_print_stmt(print_stmt *p_stmt, symtab_stack *st) {
    typecheck_exprn(p_stmt->arg, st);
}

void typecheck_read_stmt(read_stmt *r_stmt, symtab_stack *st) {
    // todo: 
    if(scope_lookup(r_stmt->arg, st) == NULL) {
        fprintf(f_error, "Error (line_no %d): symbol %s not declared before.\n", r_stmt->line_no, r_stmt->arg);
        exit(2);
    }
}
void typecheck_ret_stmt(return_stmt *ret_stmt, symtab_stack *st) {
    if(ret_stmt->fd->type == TYPE_VOID && ret_stmt->ret_expr == NULL)
        return;
    
    if(ret_stmt->ret_expr == NULL) {
        fprintf(f_error, "Error (line_no %d): Cannot return with no expression from a function of type %s.\n", ret_stmt->line_no, get_type_name(ret_stmt->fd->type));
        exit(2);
    }
    if(ret_stmt->fd->type == TYPE_VOID && ret_stmt->ret_expr != NULL) {
        fprintf(f_error, "Error (line_no %d): Cannot return any expression from a function of void type.\n", ret_stmt->line_no);
        exit(2);
    }
    
    typecheck_exprn(ret_stmt->ret_expr, st);
    if(ret_stmt->fd->type != ret_stmt->ret_expr->type) {
        fprintf(f_error, "Error (line_no %d): Cannot return an expression of type '%s' from function of type '%s'.\n", 
            ret_stmt->line_no, 
            get_type_name(ret_stmt->ret_expr->type), 
            get_type_name(ret_stmt->fd->type));
        exit(2);
    }

}

void typecheck_func_call(func_call *fc, symtab_stack *st) {
    fc->type = fc->sym->type;

    argument *arg = fc->arg_list;
    symbol *param = fc->sym->next_param;

    while(arg != NULL && param != NULL) {
        typecheck_exprn(arg->e, st);
        if(arg->e->type != param->type) {
            fprintf(f_error, "Error (line_no %d): parameter '%s' of type %s can't be initialized with argument of type %s.\n", fc->line_no, param->name, get_type_name(param->type), get_type_name(arg->e->type));
            exit(2);
        }

        arg = arg->next;
        param = param->next_param;
    }

    if(arg != NULL) {
        fprintf(f_error, "Error (line_no %d): too many arguments to function %s.\n", fc->line_no, fc->name);
        exit(2);
    }
    if(param != NULL) {
        fprintf(f_error, "Error (line_no %d): too few arguments to function call %s.\n", fc->line_no, fc->name);
    }

}

void typecheck_func_body(func_body *fb, symtab_stack *st) {
    if(fb == NULL)
        return;
    
    scope_push(fb->symtab, st);
    typecheck_stmt(fb->stmt_list, st);
    scope_pop(st);
}

void typecheck_exprn(exprn *e, symtab_stack *st) {
    if(e->kind == BINARY_EXPRN) {
        typecheck_exprn(e->left, st);
        typecheck_exprn(e->right, st);

        if(e->left->type != e->right->type) {
            fprintf(f_error, "Error (line_no %d): binary operands of different types (lhs %s, rhs %s)for operator %s.\n", e->line_no, get_type_name(e->left->type), get_type_name(e->right->type), get_op_name(e->op));
            exit(2);
        } 
        type_t type = e->left->type;
        if(get_op_type(e->op) == OP_ARITHMETIC && type != TYPE_INTEGER) {
            fprintf(f_error, "Error (line_no %d): Operanand operator type mismatch. [ lhs %s, rhs %s]\n", e->line_no, get_type_name(e->left->type), get_type_name(e->right->type));
        }
        e->type = type;
        return;
    }

    if(e->kind == IDENTIFIER_EXPRN) {
        symbol *sym = scope_lookup(e->name, st);
        e->type = sym->type;
        return;
    }
}

