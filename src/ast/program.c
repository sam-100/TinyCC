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


