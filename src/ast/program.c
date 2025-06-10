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

void program_construct_symtab(program *p) {
    symtab_stack *st = create_symtab_stack();
    scope_enter(st);
    decl_construct_symtab(p->decl_list, st);
    p->sym_tab = scope_get_current(st);
    scope_exit(st);
    destroy_symtab_stack(st);
}

void program_resolve(program *p) {
    symtab_stack *st = create_symtab_stack();
    
    scope_push(p->sym_tab, st);
    decl_resolve(p->decl_list, st);
    scope_exit(st);

    destroy_symtab_stack(st);
}

void program_print_symtab(program *p) {
    fprintf(f_symtab, "Global Symbol Table: \n");
    print_symtab(p->sym_tab);
    decl_print_symtab(p->decl_list);
}

void program_typecheck(program *p) {
    symtab_stack *st = create_symtab_stack();

    scope_push(p->sym_tab, st);
    decl_typecheck(p->decl_list, st);
    scope_pop(st);
    
    free(st);
    return;
}