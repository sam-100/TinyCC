#ifndef GENERATE_TAC_H
#define GENERATE_TAC_H

#include "ast/program.h"
#include "ast/decl.h"
#include "ast/stmt.h"
#include "ast/func.h"
#include "symbol_table/symtab_stack.h"

void generate_tac_for_program(program *p);
void generate_tac_for_function(func_decl *fd, symtab_stack *st);

void generate_tac_for_statement(statement *stmt, symtab_stack *st, tac_stmt *code, int *temp_cnt);
tac_operand *generate_tac_for_func_call_stmt(func_call_stmt *stmt, symtab_stack *st, tac_stmt *code, int *temp_cnt);

tac_operand *generate_tac_for_func_call(func_call *fc, symtab_stack *st, tac_stmt *code, int *temp_cnt);
int generate_tac_for_func_argument(argument *arg, symtab_stack *s, tac_stmt *code, int *temp_cnt);

tac_operand *generate_tac_operand_for_exprn(exprn *e, symtab_stack *st, tac_stmt *code, int *temp_cnt);


#endif