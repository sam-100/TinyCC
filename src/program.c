#include "program.h"
#include <stdlib.h>

program *create_program(decl *d) {
    program *p = (program*)calloc(1, sizeof(program));
    p->decl_list = d;
    return p;
}

