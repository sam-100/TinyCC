#ifndef TYPECHECK_H
#define TYPECHECK_H

#include "ast/program.h"
#include "ast/decl.h"
#include "ast/func.h"
#include "ast/stmt.h"
#include "ast/exprn.h"

void typecheck_program(program *p);

void typecheck_decl(decl *d, symtab_stack *st);
void typecheck_var_decl(var_decl *vd, symtab_stack *st);
void typecheck_func_decl(func_decl *fd, symtab_stack *st);

void typecheck_stmt(statement *stmt, symtab_stack *st);
void typecheck_block_stmt(block_stmt *blk_stmt, symtab_stack *st);
void typecheck_var_decl_stmt(var_decl_stmt *vd_stmt, symtab_stack *st);
void typecheck_assign_stmt(assign_stmt *as_stmt, symtab_stack *st);
void typecheck_func_call_stmt(func_call_stmt *fc_stmt, symtab_stack *st);
void typecheck_print_stmt(print_stmt *p_stmt, symtab_stack *st);
void typecheck_read_stmt(read_stmt *r_stmt, symtab_stack *st);
void typecheck_if_stmt(if_stmt *stmt, symtab_stack *st);
void typecheck_ret_stmt(return_stmt *ret_stmt, symtab_stack *st);

void typecheck_func_call(func_call *fc, symtab_stack *st);
void typecheck_func_body(func_body *fb, symtab_stack *st);

void typecheck_exprn(exprn *e, symtab_stack *st);


#endif