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
    struct func_body *body;
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

decl *create_decl_from_var(var_decl *vd);
decl *create_decl_from_func(func_decl *fd);
decl *append_decl(decl *d, decl *nd);
var_decl *create_var_decl(char *name, type_t type, exprn *e);
func_decl *create_func_decl(char *name, type_t type, parameter *param_list, func_body *body);

/* Functions to print declaration */
void print_decl(decl *d);
void print_var_decl(var_decl *vd);
void print_func_decl(func_decl *fd);

void construct_symtab_decl(decl *d, symtab_stack *st);
void construct_symtab_var_decl(var_decl *vd, symtab_stack *st);
void construct_symtab_func_decl(func_decl *fd, symtab_stack *st);

void resolve_decl(decl *d, symtab_stack *st);
void resolve_var_decl(var_decl *vd, symtab_stack *st);
void resolve_func_decl(func_decl *fd, symtab_stack *st);

void typecheck_decl(decl *d, symtab_stack *st);
void typecheck_var_decl(var_decl *vd, symtab_stack *st);
void typecheck_func_decl(func_decl *fd, symtab_stack *st);

void print_symtab_decl(decl *d);
void print_symtab_func_decl(func_decl *fd);

void memory_layout_func_decl(func_decl *fd);

void generate_tac_for_function(func_decl *fd, symtab_stack *st);

#endif