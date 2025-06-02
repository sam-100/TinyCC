#include "decl.h"
#include <stdlib.h>

decl *create_decl_from_var(var_decl *vd) {
    decl *d = (decl*)calloc(1, sizeof(decl));
    d->kind = VAR_DECL;
    d->vd = vd;
    d->next = NULL;
    return d;
}

decl *create_decl_from_func(func_decl *fd) {
    decl *d = (decl*)calloc(1, sizeof(decl));
    d->kind = FUNC_DECL;
    d->fd = fd;
    d->next = NULL;
    return d;
}

decl *append_decl(decl *d, decl *nd) {
    d->next = nd;
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


