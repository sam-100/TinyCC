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


tac_operand *generate_tac_operand_for_exprn(exprn *e, symtab_stack *st, tac_stmt *code, int *temp_cnt) {
    if(e->kind == LITERAL_EXPRN) {
        if(e->type == TYPE_INTEGER)
            return create_tac_operand_literal_int(e->value.i_val);
        if(e->type == TYPE_CHARACTER)
            return create_tac_operand_literal_char(e->value
            .c_val);
        if(e->type == TYPE_BOOLEAN)
            return create_tac_operand_literal_bool(e->value.b_val);
        
        error("Invalild type error", 2);
        return NULL;
    }
    
    if(e->kind == IDENTIFIER_EXPRN) {
        tac_operand *operand = create_tac_operand_variable(e->name, st);
        return operand;
    }

    // Binary expression :- 
    tac_stmt *curr = create_tac_stmt();
    curr->kind = TAC_ASSIGN_STMT;
    curr->op1 = generate_tac_operand_for_exprn(e->left, st, code, temp_cnt);
    curr->op2 = generate_tac_operand_for_exprn(e->right, st, code, temp_cnt);
    curr->lhs = create_tac_operand_temp(e->type, temp_cnt);   // generate a new temp variable
    curr->op = e->op;
    tac_append(code, curr);

    if(curr->op1->kind == TAC_OP_TEMP)
        freeTemp(curr->op1->temp);
    if(curr->op2->kind == TAC_OP_TEMP)
        freeTemp(curr->op2->temp);

    return curr->lhs;
}

