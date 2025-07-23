#ifndef PROGRAM_H
#define PROGRAM_H

#include "ast/decl.h"

typedef struct program {
    decl *decl_list;
    symtab *sym_tab;
} program;


/* create program */
program *create_program(decl *d);


#endif