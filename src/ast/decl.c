#include <stdlib.h>
#include <stdio.h>
#include "ast/enums.h"
#include "ast/func.h"
#include "ast/decl.h"
#include "symbol_table/print.h"
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

int get_local_size(func_decl *fd) {
    return fd->body->local_len;
}

int get_temp_size(func_decl *fd) {
    return fd->body->temp_cnt*8;
}