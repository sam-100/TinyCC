#include "func.h"
#include "stmt.h"
#include <unistd.h>
#include <stdlib.h>


// Create arguments and parameters
argument *create_arg(exprn *e) {
    argument *a = (argument*)malloc(sizeof(argument));
    a->e = e;
    a->next = NULL;
    return a;
}

argument *append_arg(argument *a, argument *na) {
    a->next = na;
    return a;
}

parameter *create_param(char *name, type_t type) {
    parameter *p = (parameter*)malloc(sizeof(parameter));
    p->name = name;
    p->type = type;
    p->next = NULL;
    return p;
}
parameter *append_param(parameter *p, parameter *np) {
    p->next = np;
    return p;
}

// Function call and body
func_call *create_func_call(char *name, argument *arg_list) {
    func_call *fc = (func_call*)malloc(sizeof(func_call));
    fc->name = name;
    fc->arg_list = arg_list;
    return fc;
}

func_body *create_func_body(statement *stmt_list) {
    func_body *fb = (func_body*)malloc(sizeof(func_body));
    fb->stmt_list = stmt_list;
    return fb;
}


