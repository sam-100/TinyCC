#ifndef ENUMS_H
#define ENUMS_H

#include <stdbool.h>


typedef enum {
    TYPE_VOID, 
    TYPE_INTEGER, 
    TYPE_CHARACTER, 
    TYPE_BOOLEAN
} type_t;

typedef enum {
    STMT_VAR_DECL, 
    STMT_ASSIGN, 
    STMT_RETURN, 
    STMT_PRINT, 
    STMT_READ, 
    STMT_FUNC_CALL, 
    STMT_BLOCK, 
} stmt_t;


typedef enum {
    DECL_VAR, 
    DECL_FUNC
} decl_t;

typedef enum {
    ARITHMETIC_EXPRN, 
    COMPARISON_EXPRN, 
    BOOLEAN_EXPRN, 
    IDENTIFIER_EXPRN, 
    LITERAL_EXPRN, 
    UNKNOWN_EXPRN, 
} exprn_t;

typedef enum {
    ASSIGN_EXPRN, 
    ASSIGN_FUNC_CALL,
} assign_t;

typedef enum {
    /* arithmetic operators */
    OP_PLUS, 
    OP_MINUS, 
    OP_MUL, 
    OP_DIV, 

    /* comparison operators */
    OP_LT, 
    OP_LE, 
    OP_EQ, 
    OP_GE, 
    OP_GT, 

    /* boolean operators */
    OP_AND, 
    OP_OR, 
    OP_NOT, 
} operator_t;

typedef union {
        int i_val;
        bool b_val;
        char c_val;
} value;

typedef enum {
    SCOPE_GLOBAL, 
    SCOPE_PARAMETER, 
    SCOPE_LOCAL
} scope_t;

typedef enum {
    SYM_VAR, 
    SYM_PARAM, 
    SYM_FUNC
} symbol_t;
#endif