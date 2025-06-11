#include "func.h"
#include "stmt.h"
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>
#include "symtab_stack.h"

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

void print_arg(argument *arg, char *tabs) {
    for(argument *ptr=arg; ptr != NULL; ptr=ptr->next) {
        fprintf(f_ast, "%sargument {\n", tabs);
        fprintf(f_ast, "%s\twhich: %d;\n", tabs, ptr->which);
        print_exprn(ptr->e, strcat(tabs, "\t"));
        tabs[strlen(tabs)-1]='\0';
        fprintf(f_ast, "%s}\n", tabs);
    }
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
    fc->sym = NULL;
    return fc;
}

func_body *create_func_body(statement *stmt_list) {
    func_body *fb = (func_body*)malloc(sizeof(func_body));
    fb->stmt_list = stmt_list;
    fb->symtab = NULL;
    return fb;
}

void print_func_call(func_call *fc, char *tabs) {
    fprintf(f_ast, "%sfunc_call {\n", tabs);

    strcat(tabs, "\t");
    fprintf(f_ast, "%sname: %s;\n", tabs, fc->name);
    fprintf(f_ast, "%sarguments: \n", tabs);
    print_arg(fc->arg_list, strcat(tabs, "\t"));
    tabs[strlen(tabs)-2]='\0';

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


void func_call_resolve(func_call *fc, symtab_stack *st) {
    if(scope_lookup(fc->name, st) == false) {
        fprintf(f_error, "Error: undeclared function '%s' called at line no. %d\n", fc->name, fc->line_no);
        exit(1);
    }
    
    fc->sym = scope_lookup(fc->name, st);
    arg_resolve(fc->arg_list, st);
}

void func_call_typecheck(func_call *fc, symtab_stack *st) {
    fc->type = fc->sym->type;

    argument *arg = fc->arg_list;
    symbol *param = fc->sym->next_param;

    while(arg != NULL && param != NULL) {
        exprn_typecheck(arg->e, st);
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


void func_body_construct_symtab(func_body *body, symtab_stack *st) {
    stmt_construct_symtab(body->stmt_list, st);
}


void func_body_resolve(func_body *fb, symtab_stack *st) {
    stmt_resolve(fb->stmt_list, st);
    fb->symtab = scope_get_current(st);
}

/* Task:
    - resolve the parameter passed and its next parameters
    - add symbol to par->sym
    - add symbol to symbol-table
    - 
*/
symbol *parameter_construct_symtab(parameter *par, symtab_stack *st) {
    if(par == NULL)
        return NULL;

    if(scope_lookup_current(par->name, st)) {
        fprintf(f_error, "Parameter %s declared again at line no. %d\n", par->name, par->line_no);
        return NULL;
    }

    symbol *sym = create_symbol(par->name, par->type, SCOPE_PARAMETER, SYM_PARAM, -1, -1, NULL);
    scope_bind(par->name, sym, st);
    sym->next_param = parameter_construct_symtab(par->next, st);
    
    par->sym = sym; 
    return sym;
}

void arg_resolve(argument *arg, symtab_stack *st) {
    if(arg == NULL)
        return;
    
    exprn_resolve(arg->e, st);
    arg->sym = arg->e->sym;

    arg_resolve(arg->next, st);
}


void func_body_typecheck(func_body *fb, symtab_stack *st) {
    if(fb == NULL)
        return;
    
    scope_push(fb->symtab, st);
    stmt_typecheck(fb->stmt_list, st);
    scope_pop(st);
}

