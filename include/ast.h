#ifndef AST_HH
#define AST_HH

#include <stdbool.h>

/* Forward declarations here */
typedef struct declaration declaration;

/* Enums for type identification inside unions */
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
    OP_PLUS, 
    OP_MINUS, 
    OP_MUL, 
    OP_DIV, 
} operator_t;

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

/* Forward declarations here */
// struct exprn;
// struct var_decl;
// struct func_decl;
// struct decl;
// struct parameter;
// struct argument;
// struct print_stmt;
// struct read_stmt;
// struct var_decl_stmt;
// struct func_call_stmt;
// struct assign_stmt;
// struct ret_stmt;
// struct statement;
// struct func_call;
// struct func_body;
// struct program;


/* structs to implement different nodes of the ast */

// expression:- 
typedef struct exprn {
    char *name;
    type_t type;
    exprn_t kind;
    operator_t op;
    struct exprn *left, *right;
    union {
        int i_val;
        bool b_val;
        char c_val;
    } value;
} exprn;

// declarations:- 
typedef struct var_decl {
    char *name;
    type_t type;
    exprn *rhs;
    bool initialized;
    union {
        int i_val;
        bool b_val;
        char c_val;
    } value;
} var_decl;

typedef struct func_decl {
    char *name;
    type_t type;
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

// parameter and arguments:- 
typedef struct parameter {
    char *name;
    type_t type;
    struct parameter *next;
} parameter;

typedef struct argument {
    exprn *e;
    struct argument *next;
} argument;

// statements:- 
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

// function call:- 
typedef struct func_call {
    char *name;
    argument *arg_list;
} func_call;

// function body:- 
typedef struct func_body {
    statement *stmt_list;
} func_body;


// program:- 
typedef struct program {
    decl *decl_list;
} program;


/* Factory functions to create and initialize above data-structures */

exprn *create_exprn_int(int val);
exprn *create_exprn_char(char val);
exprn *create_exprn_bool(bool val);

program *create_program(decl *d);
decl *create_decl_from_var(var_decl *vd);
decl *create_decl_from_func(func_decl *fd);
decl *append_decl(decl *d, decl *nd);

var_decl *create_var_decl(char *name, type_t type, exprn *e);
func_decl *create_func_decl(char *name, type_t type, parameter *param_list, func_body *body);

type_t get_type(int num);

exprn *create_exprn(exprn *lhs, operator_t op, exprn *rhs);
exprn *negate_exprn(exprn *exprn);
exprn *create_exprn_id(char *name);
exprn *create_exprn_int(int val);
exprn *create_exprn_char(char val);
exprn *create_exprn_bool(bool val);

argument *create_arg(exprn *e);
argument *append_arg(argument *a, argument *na);

parameter *create_param(char *name, type_t type);
parameter *append_param(parameter *p, parameter *np);

func_call *create_func_call(char *name, argument *arg_list);
func_body *create_func_body(statement *stmt_list);

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

