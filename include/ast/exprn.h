#ifndef EXPRN_H
#define EXPRN_H

#include "enums.h"
#include <stdbool.h>
#include "ast/decl.h"
#include "symbol_table/symtab_stack.h"
#include "tac/tac_stmt.h"

typedef struct exprn {
    char *name;
    type_t type;
    exprn_t kind;
    int line_no;
    operator_t op;
    symbol *sym;
    struct exprn *left, *right;
    value value;
} exprn;

/* create expression */
exprn *create_exprn(exprn *lhs, operator_t op, exprn *rhs);
exprn *negate_exprn(exprn *exprn);
exprn *create_exprn_id(char *name);
exprn *create_exprn_int(int val);
exprn *create_exprn_char(char val);
exprn *create_exprn_bool(bool val);


tac_operand *generate_tac_operand_for_exprn(exprn *e, symtab_stack *st, tac_stmt *code, int *temp_cnt);

#endif
