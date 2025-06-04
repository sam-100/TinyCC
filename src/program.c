#include "program.h"
#include <stdlib.h>
#include "utils.h"
#include "symtab_stack.h"

program *create_program(decl *d) {
    program *p = (program*)calloc(1, sizeof(program));
    p->decl_list = d;
    return p;
}

void print_program(program *p) {
    fprintf(f_ast, "AST of given program: \n\n");
    print_decl(p->decl_list);
}

void program_resolve(program *p) {
    symtab_stack *st = (symtab_stack*)malloc(sizeof(symtab_stack));

    scope_enter(st);
    decl_resolve(p->decl_list, st);
    p->sym_tab = scope_get_current(st);
    scope_exit(st);
    
    return;
}