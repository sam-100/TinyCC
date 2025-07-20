#ifndef TAC_OPERAND_H
#define TAC_OPERAND_H

#include "tac/enums.h"
#include "symbol_table/symbol.h"

#define MAX_TEMP 100

extern int temp_store[MAX_TEMP];

typedef struct tac_operand {
    tac_operand_t kind;
    type_t type;
    union {
        char *name;
        int temp;
        int literal_int;
        bool literal_bool; 
        char literal_char; 
    };
    symbol *sym;
    int arg_cnt;
} tac_operand;

tac_operand *create_tac_operand_temp(type_t type);
tac_operand *create_tac_operand_variable(const char *name, symtab_stack *st);
tac_operand *create_tac_operand_literal_int(int val);
tac_operand *create_tac_operand_literal_bool(bool val);
tac_operand *create_tac_operand_literal_char(char val);


int getTemp();
void freeTemp(int);

#endif