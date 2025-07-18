#ifndef TAC_H
#define TAC_H

#include "declarations.h"
#include "ast/enums.h"
#include "symbol_table/symbol.h"

typedef struct tac_operand tac_operand;

typedef enum {
    TAC_VARIABLE, 
    TAC_TEMP, 
    TAC_LITERAL_INT, 
    TAC_LITERAL_BOOL, 
    TAC_LITERAL_CHAR, 
    TAC_ARGUMENT, 
    TAC_FUNC_CALL, 
} tac_operand_t;

typedef enum {
    TAC_PRINT_STMT, 
    TAC_READ_STMT, 
    TAC_RETURN_STMT, 
    TAC_ASSIGN_STMT, 
    TAC_FUNC_CALL_STMT, 
} tac_stmt_t;

struct tac_operand {
    tac_operand_t kind;
    union {
        char *variable;
        int temp;
        int literal_int;
        bool literal_bool; 
        char literal_char; 
    };
    symbol *sym;
};

typedef struct tac_stmt {
    char *lhs;
    tac_stmt_t kind;
    symbol *sym;
    operator_t op;
    tac_operand *op1, *op2;
    int arg_cnt;
} tac_stmt;

#endif