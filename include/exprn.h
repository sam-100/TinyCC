#ifndef EXPRN_H
#define EXPRN_H

#include "enums.h"
#include <stdbool.h>

typedef struct exprn {
    char *name;
    type_t type;
    exprn_t kind;
    operator_t op;
    struct exprn *left, *right;
    value value;
} exprn;


exprn *create_exprn(exprn *lhs, operator_t op, exprn *rhs);
exprn *negate_exprn(exprn *exprn);
exprn *create_exprn_id(char *name);
exprn *create_exprn_int(int val);
exprn *create_exprn_char(char val);
exprn *create_exprn_bool(bool val);
void print_exprn(exprn *e, char *tabs);

#endif
