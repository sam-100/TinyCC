#ifndef PROGRAM_H
#define PROGRAM_H

#include "decl.h"

typedef struct program {
    decl *decl_list;
} program;


program *create_program(decl *d);
void print_program(program *p);

#endif