#include <stdlib.h>
#include <stdio.h>
#include "ast/enums.h"
#include "ast/func.h"
#include "ast/decl.h"
#include "utils.h"


decl *create_decl_from_var(var_decl *vd) {
    decl *d = (decl*)calloc(1, sizeof(decl));
    d->kind = DECL_VAR;
    d->vd = vd;
    d->next = NULL;
    return d;
}

decl *create_decl_from_func(func_decl *fd) {
    decl *d = (decl*)calloc(1, sizeof(decl));
    d->kind = DECL_FUNC;
    d->fd = fd;
    d->next = NULL;
    return d;
}


decl *append_decl(decl *d, decl *nd) {
    decl *ptr = d;
    while(ptr->next)
        ptr = ptr->next;
    ptr->next = nd;
    return d;
}

var_decl *create_var_decl(char *name, type_t type, exprn *e) {
    var_decl *vd = (var_decl*)malloc(sizeof(var_decl));
    vd->name = name;
    vd->type = type;
    if(e != NULL) {
        vd->initialized = true;
        vd->rhs = e;
        if(e->type == LITERAL_EXPRN) {
            vd->value.b_val = e->value.b_val;
            vd->value.c_val = e->value.c_val;
            vd->value.i_val = e->value.i_val;
        }
    } else {
        vd->initialized = false;
        vd->rhs = NULL;
    }
    return vd;
}

func_decl *create_func_decl(char *name, type_t type, parameter *param_list, func_body *body) {
    func_decl *fd = (func_decl*)malloc(sizeof(func_decl));
    fd->name = name;
    fd->type = type;
    fd->param_list = param_list;
    fd->body = body;
    return fd;
}


/* Functions to print declaration */
void print_decl(decl *d) {
    if(d == NULL)
        return;
    
    if(d->kind == DECL_VAR) {
        print_var_decl(d->vd);
    } else if(d->kind == DECL_FUNC) {
        print_func_decl(d->fd);
    } else {
        fprintf(f_ast, "Unknown declaration: %d\n", d->kind);
    }
    print_decl(d->next);
}

void print_var_decl(var_decl *vd) {
    fprintf(f_ast, "VAR DECLARATION {\n");
    fprintf(f_ast, "\tname=%s;\n", vd->name);
    fprintf(f_ast, "\ttype=%s;\n", get_type_name(vd->type));
    fprintf(f_ast, "\tline_no=%d;\n", vd->line_no);
    fprintf(f_ast, "}\n");
}

void print_func_decl(func_decl *fd) {
    fprintf(f_ast, "FUNC DECLARATION {\n");
    fprintf(f_ast, "\tname: %s;\n", fd->name);
    fprintf(f_ast, "\ttype: %s;\n", get_type_name(fd->type));
    fprintf(f_ast, "\tline_no: %d;\n", fd->line_no);
    fprintf(f_ast, "\tparameters: ");
    print_param(fd->param_list);
    fprintf(f_ast, ";\n");
    if(fd->body != NULL) {
        fprintf(f_ast, "\tbody: \n");
        print_func_body(fd->body);
    }
    fprintf(f_ast, "}\n");
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

void construct_symtab_var_decl(var_decl *vd, symtab_stack *st) {
    if(scope_lookup_current(vd->name, st)) {
        fprintf(stderr, "Error: redeclaration of symbol %s at line %d\n", vd->name, vd->line_no);
        return;
    }
    vd->sym = create_symbol_var_global(vd->name, vd->type, -1, -1);
    scope_bind(vd->name, vd->sym, st);
}

void resolve_var_decl(var_decl *vd, symtab_stack *st) {    
    if(vd->initialized)
        resolve_exprn(vd->rhs, st);
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
    construct_symtab_func_body(fd->body, st);
    fd->symtab = scope_get_current(st);       // save function scope
    scope_exit(st);
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

void print_symtab_decl(decl *d) {
    if(d == NULL)
        return;
    if(d->kind == DECL_FUNC)
        print_symtab_func_decl(d->fd);
    print_symtab_decl(d->next);
}

void print_symtab_func_decl(func_decl *fd) {
    if(fd->body == NULL)
        return;
    fprintf(f_symtab, "Function %s() symtab: \n", fd->name);
    fprintf(f_symtab, "{local_len: %d}\n", fd->body->local_len);
    print_symtab(fd->symtab);
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

void memory_layout_func_decl(func_decl *fd) {
    int index = 1, offset = 16;
    for(parameter *p=fd->param_list; p != NULL; p=p->next) {
        p->sym->which = index;
        p->sym->offset = offset;
        index++;
        offset += get_size_of_type(p->sym->type);
    }

    // todo: local variables
    memory_layout_func_body(fd->body);
}

void generate_tac_for_function(func_decl *fd, symtab_stack *st) {
    fd->code = create_tac_stmt();       // dummy head node
    
    scope_push(fd->symtab, st);
    for(statement *stmt = fd->body->stmt_list; stmt != NULL; stmt = stmt->next) {
        generate_tac_for_statement(stmt, st, fd->code, &fd->body->temp_cnt);
    }
    scope_pop(st);
}

void print_tac_of_function(func_decl *fd, FILE *f_out) {
    fprintf(f_out, "FUNCTION %s BEGIN (temp_cnt = %d):\n", fd->name, fd->body->temp_cnt);
    print_tac_stmt(fd->code->next, f_out);
    fprintf(f_out, "FUNCTION END\n\n");
}