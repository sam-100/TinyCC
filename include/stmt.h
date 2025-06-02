#ifndef STMT_H
#define STMT_H

#include "exprn.h"
#include "declarations.h"

typedef struct print_stmt {
    exprn *arg;
} print_stmt;

typedef struct read_stmt {
    char *arg;
} read_stmt;

typedef struct var_decl_stmt {
    var_decl *vd;
} var_decl_stmt;

typedef struct func_call_stmt {
    char *name;
    type_t *type;
    argument *args;
} func_call_stmt;

typedef struct return_stmt {
    exprn *ret_expr;
} return_stmt;

typedef struct assign_stmt {
    char *name;
    assign_t kind;
    union {
        exprn *e;
        struct func_call *fc;
    };
} assign_stmt;

typedef struct statement {
    stmt_t kind;
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


statement *create_stmt_from_var_decl(var_decl_stmt *vd);
statement *create_stmt_from_assign(assign_stmt *as);
statement *create_stmt_from_return(return_stmt *rt);
statement *create_stmt_from_print(print_stmt *ps);
statement *create_stmt_from_read(read_stmt *rs);
statement *create_stmt_from_func_call(func_call_stmt *fs);
statement *append_stmt(statement *stmt, statement *next_stmt);

var_decl_stmt *create_var_decl_stmt(var_decl *vd);
assign_stmt *create_assign_stmt_from_func_call(char *name, func_call *fc);
assign_stmt *create_assign_stmt_from_exprn(char *name, exprn *e);
return_stmt *create_ret_stmt(exprn *e);
print_stmt *create_print_stmt(exprn *e);
read_stmt *create_read_stmt(char *name);
func_call_stmt *create_func_call_stmt(char *name, argument *arg_list);


#endif