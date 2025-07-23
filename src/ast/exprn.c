#include "ast/exprn.h"
#include <stdlib.h>
#include "utils.h"
#include "declarations.h"
#include <string.h>
#include "ast/enums.h"
#include "tac/tac_stmt.h"

exprn *create_exprn(exprn *lhs, operator_t op, exprn *rhs) {
    exprn *e = (exprn*)malloc(sizeof(exprn));
    e->kind = BINARY_EXPRN;
    e->left = lhs;
    e->right = rhs;
    e->op = op;
    return e;
}

exprn *negate_exprn(exprn *expn) {
    exprn *e = (exprn*)malloc(sizeof(exprn));
    e->kind = BINARY_EXPRN;
    e->left = expn;
    e->right = create_exprn_int(-1);
    e->op = OP_MUL;
    return e;
}

exprn *create_exprn_id(char *name) {
    exprn *e = (exprn*)malloc(sizeof(exprn));
    e->kind = IDENTIFIER_EXPRN;
    e->name = name;
    return e;
}

exprn *create_exprn_int(int val) {
    exprn *e = (exprn*)malloc(sizeof(exprn));
    e->kind = LITERAL_EXPRN;
    e->type = TYPE_INTEGER;
    e->value.i_val = val;
    return e;
}
exprn *create_exprn_char(char val) {
    exprn *e = (exprn*)malloc(sizeof(exprn));
    e->kind = LITERAL_EXPRN;
    e->type = TYPE_CHARACTER;
    e->value.c_val = val;
    return e;
}
exprn *create_exprn_bool(bool val) {
    exprn *e = (exprn*)malloc(sizeof(exprn));
    e->kind = LITERAL_EXPRN;
    e->type = TYPE_BOOLEAN;
    e->value.b_val = val;
    return e;
}

