#ifndef TAC_PRINT_H
#define TAC_PRINT_H

#include "ast/program.h"


void print_tac_of_program(const program *p, FILE *f_out);
void print_tac_of_function(const func_decl *fd, FILE *f_out);


#endif