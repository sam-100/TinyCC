#include "stmt.h"
#include <unistd.h>
#include <stdlib.h>

// Creating statements from sub_stmts
statement *create_stmt_from_var_decl(var_decl_stmt *vd) {
    statement *stmt = (statement*)malloc(sizeof(statement));
    stmt->kind = STMT_VAR_DECL;
    stmt->vd_stmt = vd;
    stmt->next = NULL;
    return stmt;
}
statement *create_stmt_from_assign(assign_stmt *as) {
    statement *stmt = (statement*)malloc(sizeof(statement));
    stmt->kind = STMT_ASSIGN;
    stmt->as_stmt = as;
    stmt->next = NULL;
    return stmt;
}
statement *create_stmt_from_return(return_stmt *rs) {
    statement *stmt = (statement*)malloc(sizeof(statement));
    stmt->kind = STMT_RETURN;
    stmt->ret_stmt = rs;
    stmt->next = NULL;
    return stmt;
}
statement *create_stmt_from_print(print_stmt *ps) {
    statement *stmt = (statement*)malloc(sizeof(statement));
    stmt->kind = STMT_PRINT;
    stmt->p_stmt = ps;
    stmt->next = NULL;
    return stmt;
}
statement *create_stmt_from_read(read_stmt *rs) {
    statement *stmt = (statement*)malloc(sizeof(statement));
    stmt->kind = STMT_READ;
    stmt->r_stmt = rs;
    stmt->next = NULL;
    return stmt;
}
statement *create_stmt_from_func_call(func_call_stmt *fs) {
    statement *stmt = (statement*)malloc(sizeof(statement));
    stmt->kind = STMT_FUNC_CALL;
    stmt->fc_stmt = fs;
    stmt->next = NULL;
    return stmt;
}
statement *append_stmt(statement *stmt, statement *next_stmt) {
    stmt->next = next_stmt;
    return stmt;
}


// Creating sub_stmts
var_decl_stmt *create_var_decl_stmt(var_decl *vd) {
    var_decl_stmt *stmt = (var_decl_stmt*)malloc(sizeof(var_decl_stmt));
    stmt->vd = vd;
    return stmt;
}

assign_stmt *create_assign_stmt_from_func_call(char *name, func_call *fc) {
    assign_stmt *stmt = (assign_stmt*)malloc(sizeof(assign_stmt));
    stmt->name = name;
    stmt->kind = ASSIGN_FUNC_CALL;
    stmt->fc = fc;
    return stmt;
}

assign_stmt *create_assign_stmt_from_exprn(char *name, exprn *e) {
    assign_stmt *stmt = (assign_stmt*)malloc(sizeof(assign_stmt));
    stmt->name = name;
    stmt->kind = ASSIGN_EXPRN;
    stmt->e = e;
    return stmt;
}

return_stmt *create_ret_stmt(exprn *e) {
    return_stmt *stmt = (return_stmt*)malloc(sizeof(return_stmt));
    stmt->ret_expr = e;
    return stmt;
}

print_stmt *create_print_stmt(exprn *e) {
    print_stmt *stmt = (print_stmt*)malloc(sizeof(print_stmt));
    stmt->arg = e;
    return stmt;
}

read_stmt *create_read_stmt(char *name) {
    read_stmt *stmt = (read_stmt*)malloc(sizeof(read_stmt));
    stmt->arg = name;
    return stmt;
}

func_call_stmt *create_func_call_stmt(char *name, argument *arg_list) {
    func_call_stmt *stmt = (func_call_stmt*)malloc(sizeof(func_call_stmt));
    stmt->name = name;
    stmt->args = arg_list;
    return stmt;
}
