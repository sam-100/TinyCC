#include "decl.h"
#include <stdlib.h>
#include "utils.h"
#include "enums.h"
#include "func.h"
#include <stdio.h>


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
    
    // fprintf(f_ast, "\t name=%s, type=%s, initialized=%s\n", vd->name, get_type_name(vd->type), btoa(vd->initialized));
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

void decl_resolve(decl *d, symtab_stack *st) {
    if(d == NULL)
        return;
    
    switch(d->kind)
    {
        case DECL_VAR:
            var_decl_resolve(d->vd, st);
            break;
        case DECL_FUNC:
            func_decl_resolve(d->fd, st);
            break;
    }
    decl_resolve(d->next, st);
}

void var_decl_resolve(var_decl *vd, symtab_stack *st) {
    if(scope_lookup_current(vd->name, st)) {
        fprintf(stderr, "Error: redeclaration of symbol %s at line %d\n", vd->name, vd->line_no);
        return;
    }
    
    // vd->sym = create_symbol(vd->name, SYM_VAR, scope_type(st), vd->type, -1, -1, vd->initialized);
    vd->sym = create_symbol_var_global(vd->name, vd->type, -1, -1);
    scope_bind(vd->name, vd->sym, st);
}

void func_decl_resolve(func_decl *fd, symtab_stack *st) {
    if(scope_lookup_current(fd->name, st)) {
        fprintf(stderr, "Error: redeclaration of symbol %s at line %d\n", fd->name, fd->line_no);
        return;
    }

    // fd->sym = create_symbol_from_func_decl(fd, st);
    // create and bind a new symbol for function in global symbol table
    // fd->sym = create_symbol(fd->name, SYM_FUNC, scope_type(st), fd->type, -1, -1, fd->body != 0);
    fd->sym = create_symbol_func(fd->name, fd->type, NULL);
    scope_bind(fd->name, fd->sym, st);

    scope_enter(st);        // enter function scope
    fd->sym->next_param = parameter_resolve(fd->param_list, st);
    fd->symtab = scope_get_current(st);       // save function scope

    if(fd->body)
        func_body_resolve(fd->body, st);
    scope_exit(st);         // exit function scope
    return;
}

void decl_print_symtab(decl *d) {
    if(d == NULL)
        return;
    if(d->kind == DECL_FUNC)
        func_decl_print_symtab(d->fd);
    decl_print_symtab(d->next);
}

void func_decl_print_symtab(func_decl *fd) {
    if(fd->body == NULL)
        return;
    fprintf(f_symtab, "Function %s() symtab: \n", fd->name);
    print_symtab(fd->symtab);
}

void decl_typecheck(decl *d, symtab_stack *st) {
    if(d == NULL)
        return;
    
    switch(d->kind)
    {
        case DECL_VAR:
            var_decl_typecheck(d->vd, st);
            break;
        case DECL_FUNC:
            func_decl_typecheck(d->fd, st);
            break;
    }
    decl_typecheck(d->next, st);
}

void func_decl_typecheck(func_decl *fd, symtab_stack *st) {
    func_body_typecheck(fd->body, st);
}

void var_decl_typecheck(var_decl *vd, symtab_stack *st) {
    if(vd->initialized == false)
        return;
    
    exprn_typecheck(vd->rhs, st);
    if(vd->type != vd->rhs->type) {
        fprintf(f_error, "Variable %s of type %s assigned incompatable exprn of type %s at line no: %d", vd->name, get_type_name(vd->type), get_type_name(vd->rhs->type), vd->line_no);
        exit(2);
    }
}