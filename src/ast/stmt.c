#include "ast/stmt.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "ast/decl.h"
#include "utils.h"
#include "declarations.h"
#include "ast/program.h"

// Creating statements from sub_stmts
statement *create_stmt_from_var_decl(var_decl_stmt *vd) {
    statement *stmt = (statement*)malloc(sizeof(statement));
    stmt->kind = STMT_VAR_DECL;
    stmt->vd_stmt = vd;
    stmt->line_no = vd->line_no;
    stmt->next = NULL;
    return stmt;
}
statement *create_stmt_from_assign(assign_stmt *as) {
    statement *stmt = (statement*)malloc(sizeof(statement));
    stmt->kind = STMT_ASSIGN;
    stmt->as_stmt = as;
    stmt->line_no = as->line_no;
    stmt->next = NULL;
    return stmt;
}
statement *create_stmt_from_return(return_stmt *rs) {
    statement *stmt = (statement*)malloc(sizeof(statement));
    stmt->kind = STMT_RETURN;
    stmt->ret_stmt = rs;
    stmt->line_no = rs->line_no;
    stmt->next = NULL;
    return stmt;
}
statement *create_stmt_from_print(print_stmt *ps) {
    statement *stmt = (statement*)malloc(sizeof(statement));
    stmt->kind = STMT_PRINT;
    stmt->p_stmt = ps;
    stmt->line_no = ps->line_no;
    stmt->next = NULL;
    return stmt;
}
statement *create_stmt_from_read(read_stmt *rs) {
    statement *stmt = (statement*)malloc(sizeof(statement));
    stmt->kind = STMT_READ;
    stmt->r_stmt = rs;
    stmt->line_no = rs->line_no;
    stmt->next = NULL;
    return stmt;
}
statement *create_stmt_from_func_call(func_call_stmt *fs) {
    statement *stmt = (statement*)malloc(sizeof(statement));
    stmt->kind = STMT_FUNC_CALL;
    stmt->fc_stmt = fs;
    stmt->line_no = fs->line_no;
    stmt->next = NULL;
    return stmt;
}

statement *create_stmt_from_block(block_stmt *blk_stmt) {
    statement *stmt = (statement*)malloc(sizeof(statement));
    stmt->kind = STMT_BLOCK;
    stmt->blk_stmt = blk_stmt;
    stmt->line_no = blk_stmt->line_no;
    stmt->next = NULL;
    return stmt;
}

statement *append_stmt(statement *stmt, statement *next_stmt) {
    statement *ptr = stmt;
    while(ptr->next)
        ptr = ptr->next;
    ptr->next = next_stmt;
    return stmt;
}


// Creating sub_stmts
var_decl_stmt *create_var_decl_stmt(char *name, type_t type, exprn *e) {
    var_decl_stmt *stmt = (var_decl_stmt*)malloc(sizeof(var_decl_stmt));
    stmt->name = name;
    stmt->type = type;
    if(e != NULL) {
        stmt->initialized = true;
        stmt->rhs = e;
        if(e->kind == LITERAL_EXPRN) {
            stmt->value.b_val = e->value.b_val;
            stmt->value.c_val = e->value.c_val;
            stmt->value.i_val = e->value.i_val;
        }
    } else {
        stmt->initialized = false;
    }
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

block_stmt *create_block_stmt(statement *stmt_list) {
    block_stmt *stmt = (block_stmt*)malloc(sizeof(block_stmt));
    stmt->stmt_list = stmt_list;
    return stmt;
}


void construct_symtab_var_decl_stmt(var_decl_stmt *vd_stmt, symtab_stack *st) {
    if(scope_lookup_current(vd_stmt->name, st) != NULL) {
        fprintf(f_error, "Symbol %s at declared again at line no. %d.\n", vd_stmt->name, vd_stmt->line_no);
        exit(1);
    }

    vd_stmt->sym = create_symbol_var_local(vd_stmt->name, vd_stmt->type, -1, -1);
    scope_bind(vd_stmt->name, vd_stmt->sym, st);
}


