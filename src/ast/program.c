#include "ast/program.h"
#include <stdlib.h>
#include "utils.h"
// #include "symbol_table/symtab_stack.h"
#include "symbol_table/print.h"

program *create_program(decl *d) {
    program *p = (program*)calloc(1, sizeof(program));
    p->decl_list = d;
    return p;
}


void print_symtab_program(program *p) {
    fprintf(f_symtab, "Global Symbol Table: \n");
    print_symtab(p->sym_tab);

    // print symbol table of each function
    print_symtab_decl(p->decl_list);
}

void memory_layout_program(program *p) {
    for(decl *d=p->decl_list; d != NULL; d=d->next) {
        if(d->kind == DECL_VAR)
            continue;
        memory_layout_func_decl(d->fd);
    }
}

void generate_tac_for_program(program *p) {
    symtab_stack *st = create_symtab_stack();
    scope_push(p->sym_tab, st);
    for(decl *d = p->decl_list; d != NULL; d=d->next) {
        if(d->kind == DECL_VAR)
            continue;
        generate_tac_for_function(d->fd, st);
    }
    scope_pop(st);
}

void print_tac_of_program(program *p, FILE *f_out) {
    fprintf(f_out, "--------------- Three Address code --------------\n\n");
    for(decl *d=p->decl_list; d != NULL; d=d->next) {
        if(d->kind == DECL_VAR)
            continue;
        print_tac_of_function(d->fd, f_out);
    }
}