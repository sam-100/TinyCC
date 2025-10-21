#include "ast/exprn.h"
#include <stdlib.h>
#include "utils.h"
#include "declarations.h"
#include <string.h>
#include "ast/enums.h"
#include "tac/tac_stmt.h"

exprn *create_exprn(exprn *lhs, operator_t op, exprn *rhs) {        // create a binary expression [arithmetic, boolean, comparison]
    exprn *e = (exprn*)malloc(sizeof(exprn));
    e->kind = get_op_kind(op);
    e->left = lhs;
    e->right = rhs;
    e->op = op;
    return e;
}

exprn *create_not_exprn(exprn *rhs) {
    exprn *e = (exprn*)malloc(sizeof(exprn));
    e->kind == BOOLEAN_EXPRN;
    e->right = rhs;
    e->op = OP_NOT;
    return e;
}

exprn *negate_exprn(exprn *expn) {
    exprn *e = (exprn*)malloc(sizeof(exprn));
    e->kind = ARITHMETIC_EXPRN;
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

exprn *create_exprn_assign(char *name, exprn *rhs) {
    exprn *e = (exprn*)malloc(sizeof(exprn));
    e->kind = ASSIGNMENT_EXPRN;
    e->name = name;
    e->right = rhs;
    return e;
}


/* helper functions */
exprn_t get_op_kind(operator_t op) {
    switch(op)
    {
        case OP_PLUS:
        case OP_MINUS:
        case OP_MUL:
        case OP_DIV:
            return ARITHMETIC_EXPRN;
        case OP_AND:
        case OP_OR:
        case OP_NOT:
            return BOOLEAN_EXPRN;
        case OP_GT:
        case OP_GE:
        case OP_EQ:
        case OP_LE:
        case OP_LT:
            return COMPARISON_EXPRN;
        default:
            return UNKNOWN_EXPRN;
    }
}