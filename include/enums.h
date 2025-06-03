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
} stmt_t;


typedef enum {
    DECL_VAR, 
    DECL_FUNC
} decl_t;

typedef enum {
    BINARY_EXPRN, 
    IDENTIFIER_EXPRN, 
    LITERAL_EXPRN
} exprn_t;

typedef enum {
    ASSIGN_EXPRN, 
    ASSIGN_FUNC_CALL,
} assign_t;

typedef enum {
    OP_PLUS, 
    OP_MINUS, 
    OP_MUL, 
    OP_DIV, 
} operator_t;

typedef union {
        int i_val;
        bool b_val;
        char c_val;
} value;

typedef enum {
    GLOBAL, 
    PARAMETER, 
    LOCAL
} symbol_t;

#endif