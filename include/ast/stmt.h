#ifndef STMT_H
#define STMT_H

#include "exprn.h"
#include "declarations.h"

typedef struct print_stmt {
    exprn *arg;
    int line_no;
} print_stmt;

typedef struct read_stmt {
    char *arg;
    int line_no;
    symbol *sym;
} read_stmt;

typedef struct var_decl_stmt {
    // var_decl *vd;
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
} var_decl_stmt;

typedef struct func_call_stmt {
    char *name;
    type_t type;
    argument *args;
    int line_no;
    symbol *sym;
} func_call_stmt;

typedef struct return_stmt {
    exprn *ret_expr;
    int line_no;
    symbol *sym;
    func_decl *fd;
} return_stmt;

typedef struct assign_stmt {
    char *name;
    assign_t kind;
    type_t type;
    int line_no;
    symbol *sym;
    union {
        exprn *e;
        struct func_call *fc;
    };
} assign_stmt;

typedef struct statement {
    stmt_t kind;
    int line_no;
    union {
        print_stmt *p_stmt;
        read_stmt *r_stmt;
        var_decl_stmt *vd_stmt;
        func_call_stmt *fc_stmt;
        assign_stmt *as_stmt;
        return_stmt *ret_stmt;
    };
    struct statement *next;
} statement;

/* functions to create statement from various sub-statements */
statement *create_stmt_from_var_decl(var_decl_stmt *vd);
statement *create_stmt_from_assign(assign_stmt *as);
statement *create_stmt_from_return(return_stmt *rt);
statement *create_stmt_from_print(print_stmt *ps);
statement *create_stmt_from_read(read_stmt *rs);
statement *create_stmt_from_func_call(func_call_stmt *fs);
statement *append_stmt(statement *stmt, statement *next_stmt);

/* functions to create statements of various type */
var_decl_stmt *create_var_decl_stmt(char *name, type_t type, exprn *e);
assign_stmt *create_assign_stmt_from_func_call(char *name, func_call *fc);
assign_stmt *create_assign_stmt_from_exprn(char *name, exprn *e);
return_stmt *create_ret_stmt(exprn *e);
print_stmt *create_print_stmt(exprn *e);
read_stmt *create_read_stmt(char *name);
func_call_stmt *create_func_call_stmt(char *name, argument *arg_list);


void construct_symtab_stmt(statement *stmt, symtab_stack *st);
void construct_symtab_var_decl_stmt(var_decl_stmt *vd_stmt, symtab_stack *st);
// void assign_stmt_construct_symtab(assign_stmt *as_stmt, symtab_stack *st);
// void func_call_stmt_construct_symtab(func_call_stmt *fc_stmt, symtab_stack *st);
// void print_stmt_construct_symtab(print_stmt *p_stmt, symtab_stack *st);
// void read_stmt_construct_symtab(read_stmt *r_stmt, symtab_stack *st);
// void ret_stmt_construct_symtab(return_stmt *ret_stmt, symtab_stack *st);


/* methods to construct and resolve symbols for each statement */
void resolve_stmt(statement *stmt, symtab_stack *st);
void resolve_var_decl_stmt(var_decl_stmt *vd_stmt, symtab_stack *st);
void resolve_assign_stmt(assign_stmt *as_stmt, symtab_stack *st);
void resolve_func_call_stmt(func_call_stmt *fc_stmt, symtab_stack *st);
void resolve_print_stmt(print_stmt *p_stmt, symtab_stack *st);
void resolve_read_stmt(read_stmt *r_stmt, symtab_stack *st);
void resolve_ret_stmt(return_stmt *ret_stmt, symtab_stack *st);


void typecheck_stmt(statement *stmt, symtab_stack *st);
void typecheck_var_decl_stmt(var_decl_stmt *vd_stmt, symtab_stack *st);
void typecheck_assign_stmt(assign_stmt *as_stmt, symtab_stack *st);
void typecheck_func_call_stmt(func_call_stmt *fc_stmt, symtab_stack *st);
void typecheck_print_stmt(print_stmt *p_stmt, symtab_stack *st);
void typecheck_read_stmt(read_stmt *r_stmt, symtab_stack *st);
void typecheck_ret_stmt(return_stmt *ret_stmt, symtab_stack *st);
int memory_layout_stmt_list(statement *stmt_list);

void generate_tac_for_statement(statement *stmt, symtab_stack *st, tac_stmt *code, int *temp_cnt);
void generate_tac_for_func_call_stmt(func_call_stmt *stmt, symtab_stack *st, tac_stmt *code, int *temp_cnt);
#endif