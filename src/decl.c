#include "decl.h"
#include <stdlib.h>
#include "utils.h"
#include "enums.h"
#include "func.h"


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

