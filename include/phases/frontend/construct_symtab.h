#ifndef CONSTRUCT_SYMTAB_H
#define CONSTRUCT_SYMTAB_H

#include "ast/program.h"
#include "ast/decl.h"
#include "ast/func.h"
#include "ast/stmt.h"
#include "ast/exprn.h"

void construct_symtab_program(program *p);

void construct_symtab_decl(decl *d, symtab_stack *st);
void construct_symtab_var_decl(var_decl *vd, symtab_stack *st);
void construct_symtab_func_decl(func_decl *fd, symtab_stack *st);

symbol *construct_symtab_parameter(parameter *par, symtab_stack *st);
void construct_symtab_func_body(func_body *body, symtab_stack *st);

void construct_symtab_stmt(statement *stmt, symtab_stack *st);
void construct_symtab_var_decl_stmt(var_decl_stmt *vd_stmt, symtab_stack *st);
void construct_symtab_block_stmt(block_stmt *stmt, symtab_stack *st);
void construct_symtab_if_stmt(if_stmt *stmt, symtab_stack *st);


#endif