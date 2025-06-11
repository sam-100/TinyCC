#ifndef EXPRN_H
#define EXPRN_H

#include "enums.h"
#include <stdbool.h>
#include "decl.h"
#include "symtab_stack.h"

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


exprn *create_exprn(exprn *lhs, operator_t op, exprn *rhs);
exprn *negate_exprn(exprn *exprn);
exprn *create_exprn_id(char *name);
exprn *create_exprn_int(int val);
exprn *create_exprn_char(char val);
exprn *create_exprn_bool(bool val);
void print_exprn(exprn *e, char *tabs);

void resolve_exprn(exprn *e, symtab_stack *st);

void typecheck_exprn(exprn *e, symtab_stack *st);

#endif
