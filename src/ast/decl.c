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