#include "ast/program.h"
#include <stdlib.h>
#include "utils.h"
#include "symbol_table/symtab_stack.h"

program *create_program(decl *d) {
    program *p = (program*)calloc(1, sizeof(program));
    p->decl_list = d;
    return p;
}

void print_program(program *p) {
    fprintf(f_ast, "AST of given program: \n\n");
    print_decl(p->decl_list);
}

void construct_symtab_program(program *p) {
    symtab_stack *st = create_symtab_stack();
    scope_enter(st);
    construct_symtab_decl(p->decl_list, st);
    p->sym_tab = scope_get_current(st);
    scope_exit(st);
    destroy_symtab_stack(st);
}

void resolve_program(program *p) {
    symtab_stack *st = create_symtab_stack();
    
    scope_push(p->sym_tab, st);
    resolve_decl(p->decl_list, st);
    scope_exit(st);

    destroy_symtab_stack(st);
}

void print_symtab_program(program *p) {
    fprintf(f_symtab, "Global Symbol Table: \n");
    print_symtab(p->sym_tab);

    // print symbol table of each function
    print_symtab_decl(p->decl_list);
}

void typecheck_program(program *p) {
    symtab_stack *st = create_symtab_stack();

    scope_push(p->sym_tab, st);
    typecheck_decl(p->decl_list, st);
    scope_pop(st);
    
    free(st);
    return;
}

void memory_layout_program(program *p) {
    for(decl *d=p->decl_list; d != NULL; d=d->next) {
        if(d->kind == DECL_VAR)
            continue;
        memory_layout_func_decl(d->fd);
    }
}
