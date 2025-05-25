#ifndef AST_HH
#define AST_HH

typedef enum type {
    VOID, 
    INTEGER, 
    CHARACTER, 
    BOOLEAN
} type_t;

typedef struct {
    char *name;
    type_t type;

} var_decl;

typedef struct {
    
} func_decln;

typedef struct {

} func_defn;

#endif