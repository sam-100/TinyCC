#ifndef TAC_H
#define TAC_H

#include "ast/enums.h"
#include "symbol_table/symbol.h"
#include "tac/enums.h"
#include "tac/tac_operand.h"

typedef struct tac_stmt {
    tac_operand *lhs, *op1, *op2;
    tac_stmt_t kind;
    operator_t op;
    int arg_cnt;
    tac_stmt *next;
} tac_stmt;

tac_stmt *tac_append(tac_stmt *first, tac_stmt *second);
tac_stmt *get_last(tac_stmt *t);
tac_stmt *create_tac_stmt();


#endif