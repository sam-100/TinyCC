#ifndef DECL_H
#define DECL_H

#include "enums.h"
#include "exprn.h"
#include "func.h"
#include "symbol_table/symtab_stack.h"

typedef struct var_decl {
    char *name;
    type_t type;
    int line_no;
    exprn *rhs;
    bool initialized;
    symbol *sym;
    union {
        int i_val;
        bool b_val;
        char c_val;
    } value;
} var_decl;

typedef struct func_decl {
    char *name;
    type_t type;
    int line_no;
    symbol *sym;
    symtab *symtab;
    struct parameter *param_list;
    struct block_stmt *body;
    tac_stmt *code;
} func_decl;

typedef struct decl {
    decl_t kind;
    union {
        var_decl *vd;
        func_decl *fd;
    };
    struct decl *next;
} decl;

/* create declarations */
decl *create_decl_from_var(var_decl *vd);
decl *create_decl_from_func(func_decl *fd);
decl *append_decl(decl *d, decl *nd);
var_decl *create_var_decl(char *name, type_t type, exprn *e);
func_decl *create_func_decl(char *name, type_t type, parameter *param_list, block_stmt *body);

int get_local_size(func_decl *fd);
int get_temp_size(func_decl *fd);

#endif