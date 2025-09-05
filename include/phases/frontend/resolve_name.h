#ifndef RESOLVE_NAME_H
#define RESOLVE_NAME_H

#include "ast/program.h"
#include "ast/decl.h"
#include "ast/func.h"
#include "ast/stmt.h"
#include "ast/exprn.h"

void resolve_program(program *p);

void resolve_decl(decl *d, symtab_stack *st);
void resolve_var_decl(var_decl *vd, symtab_stack *st);
void resolve_func_decl(func_decl *fd, symtab_stack *st);

void resolve_arg(argument *arg, symtab_stack *st);
void resolve_func_call(func_call *fc, symtab_stack *st);

void resolve_stmt(statement *stmt, symtab_stack *st);
void resolve_var_decl_stmt(var_decl_stmt *vd_stmt, symtab_stack *st);
void resolve_assign_stmt(assign_stmt *as_stmt, symtab_stack *st);
void resolve_func_call_stmt(func_call_stmt *fc_stmt, symtab_stack *st);
void resolve_print_stmt(print_stmt *p_stmt, symtab_stack *st);
void resolve_read_stmt(read_stmt *r_stmt, symtab_stack *st);
void resolve_ret_stmt(return_stmt *ret_stmt, symtab_stack *st);
void resolve_block_stmt(block_stmt *blk_stmt, symtab_stack *st);
void resolve_if_stmt(if_stmt *if_stmt, symtab_stack *st);

void resolve_exprn(exprn *e, symtab_stack *st);



#endif