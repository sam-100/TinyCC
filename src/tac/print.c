#include "tac/print.h"
#include <stdio.h>

void print_tac_of_program(program *p, FILE *f_out) {
    fprintf(f_out, "--------------- Three Address code --------------\n\n");
    for(decl *d=p->decl_list; d != NULL; d=d->next) {
        if(d->kind == DECL_VAR)
            continue;
        print_tac_of_function(d->fd, f_out);
    }
}

void print_tac_of_function(func_decl *fd, FILE *f_out) {
    fprintf(f_out, "FUNCTION %s BEGIN (temp_cnt = %d):\n", fd->name, fd->body->temp_cnt);
    print_tac_stmt(fd->code->next, f_out);
    fprintf(f_out, "FUNCTION END\n\n");
}