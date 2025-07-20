#include "tac/tac_operand.h"
#include "ast/exprn.h"
#include "ast/enums.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

int temp_store[MAX_TEMP];

tac_operand *create_tac_operand_temp(type_t type) {
    tac_operand *operand = (tac_operand*)malloc(sizeof(tac_operand));
    operand->temp = getTemp();
    operand->kind = TAC_OP_TEMP;
    operand->type = type;
    return operand;
}

tac_operand *create_tac_operand_variable(const char *name, symtab_stack *st) {
    tac_operand *curr = (tac_operand*)malloc(sizeof(tac_operand));
    curr->kind = TAC_OP_VARIABLE;
    curr->name = strdup(name);
    curr->sym = scope_lookup(name, st);
    curr->type = curr->sym->type;
    return curr;
}

tac_operand *create_tac_operand_literal_int(int val) {
    tac_operand *curr = (tac_operand*)malloc(sizeof(tac_operand));
    curr->kind = TAC_OP_LITERAL_INT;
    curr->literal_int = val;
    curr->type = TYPE_INTEGER;
    return curr;
}

tac_operand *create_tac_operand_literal_bool(bool val) {
    tac_operand *curr = (tac_operand*)malloc(sizeof(tac_operand));
    curr->kind = TAC_OP_LITERAL_BOOL;
    curr->literal_bool = val;
    curr->type = TYPE_BOOLEAN;
    return curr;
}

tac_operand *create_tac_operand_literal_char(char val) {
    tac_operand *curr = (tac_operand*)malloc(sizeof(tac_operand));
    curr->kind = TAC_OP_LITERAL_CHAR;
    curr->literal_char = val;
    curr->type = TYPE_CHARACTER;
    return curr;
}


int getTemp() {
    for(int i=0; i<MAX_TEMP; i++) {
        if(temp_store[i] == 0) {
            temp_store[i] = 1;
            return i;
        }
    }
    error("Temporary variables out of stock.", 2);
    return -1;
}

void freeTemp(int temp) {
    if(temp_store[temp] == 0) {
        error("Freeing un-allocated temporary variable.", 2);
    }
    temp_store[temp] = 0;
}

char *tac_op_to_string(tac_operand *t_op) {
    char *str = malloc(100);
    str[0] = '\0';
    switch(t_op->kind)
    {
        case TAC_OP_VARIABLE:
            return t_op->name;
        case TAC_OP_TEMP:
            strcat(str, "temp_");
            strcat(str, itoa(t_op->temp));
            return str;
        case TAC_OP_LITERAL_INT:
            return itoa(t_op->literal_int);
        case TAC_OP_LITERAL_BOOL:
            return btoa(t_op->literal_bool);
        case TAC_OP_LITERAL_CHAR:
            return &t_op->literal_char;
        case TAC_OP_FUNC_CALL:
            sprintf(str, "call %s, %d", t_op->name, t_op->arg_cnt);
            return str;
    }
    
    return NULL;
}