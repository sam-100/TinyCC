#ifndef PROGRAM_H
#define PROGRAM_H

#include "decl.h"

typedef struct program {
    decl *decl_list;
    symtab *sym_tab;
} program;


program *create_program(decl *d);
void print_program(program *p);

void program_construct_symtab(program *p);
void program_resolve(program *p);
void program_print_symtab(program *p);
void program_typecheck(program *p);

#endif