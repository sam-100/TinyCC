#include "func.h"
#include "stmt.h"
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>

// Create arguments and parameters
argument *create_arg(exprn *e) {
    argument *a = (argument*)malloc(sizeof(argument));
    a->e = e;
    a->next = NULL;
    return a;
}

argument *append_arg(argument *a, argument *na) {
    argument *ptr=a;
    while(ptr->next)
        ptr=ptr->next;
    ptr->next = na;
    return a;
}

void print_arg(argument *arg, char *tabs) {
    for(argument *ptr=arg; ptr != NULL; ptr=ptr->next) {
        print_exprn(ptr->e, strcat(tabs, "\t"));
        tabs[strlen(tabs)-1]='\0';
    }
}


parameter *create_param(char *name, type_t type) {
    parameter *p = (parameter*)malloc(sizeof(parameter));
    p->name = name;
    p->type = type;
    p->next = NULL;
    return p;
}
parameter *append_param(parameter *p, parameter *np) {
    parameter *ptr = p;
    while(ptr->next)
        ptr = ptr->next;
    ptr->next = np;
    return p;
}



void print_param(parameter *p) {
    if(p == NULL)
        return;
    fprintf(f_ast, "{%s: %s} ", p->name, get_type_name(p->type));
    print_param(p->next);
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

void print_func_call(func_call *fc, char *tabs) {
    fprintf(f_ast, "%sfunc_call {\n", tabs);

    strcat(tabs, "\t");
    fprintf(f_ast, "%sname: %s;\n", tabs, fc->name);
    fprintf(f_ast, "%sarguments: \n", tabs);
    print_arg(fc->arg_list, tabs);
    tabs[strlen(tabs)-1]='\0';

    fprintf(f_ast, "\n");
    fprintf(f_ast, "%s}\n", tabs);
}

void print_func_body(func_body *fb) {
    if(fb == NULL)
        return;
    
    char *tabs = (char*)malloc(100);
    tabs[0] = '\t';
    tabs[1] = '\0';

    fprintf(f_ast, "\t{\n");
    print_statement(fb->stmt_list, strcat(tabs, "\t"));
    fprintf(f_ast, "\t}\n");

    free(tabs);
}


