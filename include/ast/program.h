#ifndef PROGRAM_H
#define PROGRAM_H

#include "ast/decl.h"

typedef struct program {
    decl *decl_list;
    symtab *sym_tab;
} program;


program *create_program(decl *d);
void print_program(program *p);

void construct_symtab_program(program *p);
void resolve_program(program *p);
void print_symtab_program(program *p);
void typecheck_program(program *p);
void memory_layout_program(program *p);
void generate_tac_for_program(program *p);
void print_tac_of_program(program *p, FILE *f_out);

#endif