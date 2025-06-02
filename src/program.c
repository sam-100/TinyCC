#include "program.h"
#include <stdlib.h>
#include "utils.h"

program *create_program(decl *d) {
    program *p = (program*)calloc(1, sizeof(program));
    p->decl_list = d;
    return p;
}

void print_program(program *p) {
    fprintf(f_ast, "AST of given program: \n\n");
    print_decl(p->decl_list);
}