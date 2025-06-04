#ifndef DECL_H
#define DECL_H

#include "enums.h"
#include "exprn.h"
#include "func.h"
#include "symtab_stack.h"

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
    struct func_body *body;
} func_decl;

typedef struct decl {
    decl_t kind;
    union {
        var_decl *vd;
        func_decl *fd;
    };
    struct decl *next;
} decl;

decl *create_decl_from_var(var_decl *vd);
decl *create_decl_from_func(func_decl *fd);
decl *append_decl(decl *d, decl *nd);
var_decl *create_var_decl(char *name, type_t type, exprn *e);
func_decl *create_func_decl(char *name, type_t type, parameter *param_list, func_body *body);

/* Functions to print declaration */
void print_decl(decl *d);
void print_var_decl(var_decl *vd);
void print_func_decl(func_decl *fd);

void decl_resolve(decl *d, symtab_stack *st);
void var_decl_resolve(var_decl *vd, symtab_stack *st);
void func_decl_resolve(func_decl *fd, symtab_stack *st);

void decl_typecheck(decl *d, symtab_stack *st);
void func_decl_typecheck(func_decl *fd, symtab_stack *st);

#endif