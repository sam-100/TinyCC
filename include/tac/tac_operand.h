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

tac_operand *create_tac_operand_temp(type_t type, int *temp_cnt);
tac_operand *create_tac_operand_variable(const char *name, symtab_stack *st);
tac_operand *create_tac_operand_literal_int(int val);
tac_operand *create_tac_operand_literal_bool(bool val);
tac_operand *create_tac_operand_literal_char(char val);
tac_operand *create_tac_operand_func_call(type_t type, const char *name);

char *tac_op_to_string(tac_operand *t_op);
char *get_value(tac_operand *t_op, int local_size);

int getTemp();
void freeTemp(int);

#endif