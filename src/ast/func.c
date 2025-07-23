#include "ast/func.h"
#include "ast/stmt.h"
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>
#include "symbol_table/symtab_stack.h"

// Create arguments and parameters
argument *create_arg(exprn *e) {
    argument *a = (argument*)malloc(sizeof(argument));
    a->e = e;
    a->next = NULL;
    a->which = 1;
    return a;
}

argument *append_arg(argument *a, argument *na) {
    argument *ptr=a;
    while(ptr->next)
        ptr=ptr->next;
    ptr->next = na;
    na->which = ptr->which+1;
    // printf("argument %s(%d) appended to argument %s(%d).\n", na->e->name, na->which, ptr->e->name, ptr->which);
    return a;
}


parameter *create_param(char *name, type_t type) {
    parameter *p = (parameter*)malloc(sizeof(parameter));
    p->name = name;
    p->type = type;
    p->next = NULL;
    p->which = 1;
    p->offset = 0;
    return p;
}

parameter *append_param(parameter *p, parameter *np) {
    parameter *ptr = p;
    while(ptr->next)
        ptr = ptr->next;
    ptr->next = np;
    np->which = ptr->which+1;
    np->offset = ptr->offset+get_size_of_type(ptr->type);
    // printf("appending parameter %s to %s.\n", np->name, ptr->name);
    return p;
}



// Function call and body
func_call *create_func_call(char *name, argument *arg_list) {
    func_call *fc = (func_call*)malloc(sizeof(func_call));
    fc->name = name;
    fc->arg_list = arg_list;
    fc->sym = NULL;
    return fc;
}

func_body *create_func_body(statement *stmt_list) {
    func_body *fb = (func_body*)malloc(sizeof(func_body));
    fb->stmt_list = stmt_list;
    fb->symtab = NULL;
    fb->local_len = 0;
    fb->temp_cnt = 0;
    return fb;
}


