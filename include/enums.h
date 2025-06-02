#ifndef ENUMS_H
#define ENUMS_H

typedef enum {
    TYPE_VOID, 
    TYPE_INTEGER, 
    TYPE_CHARACTER, 
    TYPE_BOOLEAN
} type_t;

typedef enum {
    VAR_DECLARATION, 
    VAR_DEFINITION, 
    FUNC_DECLARATION, 
    FUNC_DEFINITION, 
} global_decl_t;

typedef enum {
    STMT_VAR_DECL, 
    STMT_ASSIGN, 
    STMT_RETURN, 
    STMT_PRINT, 
    STMT_READ, 
    STMT_FUNC_CALL, 
} stmt_t;


typedef enum {
    VAR_DECL, 
    FUNC_DECL
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

#endif