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
    operand->temp = getTemp();
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
