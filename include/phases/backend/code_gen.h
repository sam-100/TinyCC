#ifndef CODE_GEN_H
#define CODE_GEN_H

#include "ast/program.h"
#include "ast/decl.h"
#include "ast/stmt.h"
#include "ast/func.h"
#include "ast/exprn.h"
#include "fcntl.h"

void codegen_program(program *p, FILE *f_out);

void codegen_data(program *p, FILE *f_out);
void codegen_bss(program *p, FILE *f_out);
void codegen_text(program *p, FILE *f_out);

void codegen_function(func_decl *fd, FILE *f_out);
void codegen_tac_stmt(tac_stmt *stmt, FILE *f_out, int local_size);
tac_stmt *codegen_tac_function_call(tac_stmt *t_stmt, FILE *f_out, int local_size, int temp_size);

/* helper functions */
void codegen_exit(FILE *f_out);

#endif