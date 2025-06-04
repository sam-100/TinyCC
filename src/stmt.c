#include "stmt.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "decl.h"
#include "utils.h"


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
statement *append_stmt(statement *stmt, statement *next_stmt) {
    statement *ptr = stmt;
    while(ptr->next)
        ptr = ptr->next;
    ptr->next = next_stmt;
    return stmt;
}

void print_statement(statement *stmt, char *tabs) {
    if(stmt == NULL)
        return;
    
    switch(stmt->kind)
    {
        case STMT_VAR_DECL:
            print_stmt_var_decl(stmt->vd_stmt, tabs);
            break;
        case STMT_ASSIGN:
            print_stmt_assignment(stmt->as_stmt, tabs);
            break;
        case STMT_FUNC_CALL:
            print_stmt_func_call(stmt->fc_stmt, tabs);
            break;
        case STMT_PRINT:
            print_stmt_print(stmt->p_stmt, tabs);
            break;
        case STMT_READ:
            print_stmt_read(stmt->r_stmt, tabs);
            break;
        case STMT_RETURN:
            print_stmt_return(stmt->ret_stmt, tabs);
            break;
        default:
            fprintf(f_ast, "%sInvalid statement with code %d\n", tabs, (int)stmt->kind);
            break;
    }
    print_statement(stmt->next, tabs);
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


void print_stmt_var_decl(var_decl_stmt *vd_stmt, char *tabs) {
    fprintf(f_ast, "%svar_decl_stmt {\n", tabs);
    fprintf(f_ast, "%s\tname: %s;\n", tabs, vd_stmt->vd->name);
    fprintf(f_ast, "%s\ttype: %s;\n", tabs, get_type_name(vd_stmt->vd->type));
    fprintf(f_ast, "%s\tline_no: %d;\n", tabs, vd_stmt->line_no);
    fprintf(f_ast, "%s}\n", tabs);
}

void print_stmt_assignment(assign_stmt *asstmt, char *tabs) {
    fprintf(f_ast, "%sassign_stmt {\n", tabs);
    fprintf(f_ast, "%s\tline_no: %d;\n", tabs, asstmt->line_no);
    fprintf(f_ast, "%s\tlhs: %s;\n", tabs, asstmt->name);
    fprintf(f_ast, "%s\trhs: \n", tabs);
    switch(asstmt->kind)
    {
        case ASSIGN_EXPRN:
            print_exprn(asstmt->e, strcat(tabs, "\t\t"));
            tabs[strlen(tabs)-2] = '\0';
            break;
        case ASSIGN_FUNC_CALL:
            print_func_call(asstmt->fc, strcat(tabs, "\t\t"));
            tabs[strlen(tabs)-2] = '\0';
            break;
        default:
            fprintf(f_ast, "%s\tInvalid assignment statement code %d\n", tabs, asstmt->kind);
            break;
    }
    fprintf(f_ast, "%s}\n", tabs);
}

void print_stmt_func_call(func_call_stmt *fc_stmt, char *tabs) {
    fprintf(f_ast, "%sfunc_call_stmt {\n", tabs);
    strcat(tabs, "\t");
    fprintf(f_ast, "%sname: %s;\n", tabs, fc_stmt->name);
    fprintf(f_ast, "%s\tline_no: %d;\n", tabs, fc_stmt->line_no);
    // fprintf(f_ast, "%stype: %s;\n", tabs, get_type_name(fc_stmt->type));
    fprintf(f_ast, "%sarguments: \n", tabs);
    print_arg(fc_stmt->args, strcat(tabs, "\t"));
    tabs[strlen(tabs)-1]='\0';
    tabs[strlen(tabs)-1]='\0';
    fprintf(f_ast, "%s}\n", tabs);
}

void print_stmt_print(print_stmt *p_stmt, char *tabs) {
    fprintf(f_ast, "%sprint_stmt {\n", tabs);
    fprintf(f_ast, "%s\tline_no: %d;\n", tabs, p_stmt->line_no);
    fprintf(f_ast, "%s\targuments: \n", tabs);
    print_exprn(p_stmt->arg, strcat(tabs, "\t\t"));
    tabs[strlen(tabs)-2]='\0';
    fprintf(f_ast, "%s}\n", tabs);
}

void print_stmt_read(read_stmt *r_stmt, char *tabs) {
    fprintf(f_ast, "%sread_stmt {\n", tabs);
    fprintf(f_ast, "%s\tline_no: %d;\n", tabs, r_stmt->line_no);
    fprintf(f_ast, "%s\targument: %s\n", tabs, r_stmt->arg);
    fprintf(f_ast, "%s}\n", tabs);
}

void print_stmt_return(return_stmt *ret_stmt, char *tabs) {
    fprintf(f_ast, "%sreturn_stmt {\n", tabs);
    fprintf(f_ast, "%s\tline_no: %d;\n", tabs, ret_stmt->line_no);
    fprintf(f_ast, "%s\targuments: \n", tabs);
    print_exprn(ret_stmt->ret_expr, strcat(tabs, "\t\t"));
    tabs[strlen(tabs)-2]='\0';
    fprintf(f_ast, "%s}\n", tabs);

}


void stmt_resolve(statement *stmt, symtab_stack *st) {
    if(stmt == NULL)
        return;
    
    switch(stmt->kind)
    {
        case STMT_VAR_DECL:
            var_decl_stmt_resolve(stmt->vd_stmt, st);
            break;
        case STMT_ASSIGN:
            assign_stmt_resolve(stmt->as_stmt, st);
            break;
        case STMT_FUNC_CALL:
            func_call_stmt_resolve(stmt->fc_stmt, st);
            break;
        case STMT_PRINT:
            print_stmt_resolve(stmt->p_stmt, st);
            break;
        case STMT_READ:
            read_stmt_resolve(stmt->r_stmt, st);
            break;
        case STMT_RETURN:
            ret_stmt_resolve(stmt->ret_stmt, st);
            break;
        
    }

    stmt_resolve(stmt->next, st);
}


void var_decl_stmt_resolve(var_decl_stmt *vd_stmt, symtab_stack *st) {
    var_decl_resolve(vd_stmt->vd, st);
    vd_stmt->sym = vd_stmt->vd->sym;
}

void assign_stmt_resolve(assign_stmt *as_stmt, symtab_stack *st) {
    if(scope_lookup(as_stmt->name, st) == false) {
        fprintf(f_error, "Symbol %s at line no. %d is not defined before\n", as_stmt->name, as_stmt->line_no);
        return;
    }

    as_stmt->sym = scope_lookup(as_stmt->name, st);

    // resolving rhs 
    switch(as_stmt->kind)
    {
        case ASSIGN_EXPRN:
            exprn_resolve(as_stmt->e, st);
            break;
        case ASSIGN_FUNC_CALL:
            func_call_resolve(as_stmt->fc, st);
            break;
    }
    return;
}

void func_call_stmt_resolve(func_call_stmt *fc_stmt, symtab_stack *st) {
    if(scope_lookup(fc_stmt->name, st) == false) {
        fprintf(f_error, "Error: undeclared function '%s' called at line no. %d\n", fc_stmt->name, fc_stmt->line_no);
        exit(1);
    }

    fc_stmt->sym = scope_lookup(fc_stmt->name, st);

    arg_resolve(fc_stmt->args, st);
}

void print_stmt_resolve(print_stmt *p_stmt, symtab_stack *st) {
    exprn_resolve(p_stmt->arg, st);
}

void read_stmt_resolve(read_stmt *r_stmt, symtab_stack *st) {
    if(scope_lookup(r_stmt->arg, st) == false) {
        fprintf(f_error, "Reading into undeclared symbol '%s' at line_no: %d\n", r_stmt->arg, r_stmt->line_no);
        exit(1);
    }
    r_stmt->sym = scope_lookup(r_stmt->arg, st);
}

void ret_stmt_resolve(return_stmt *ret_stmt, symtab_stack *st) {
    exprn_resolve(ret_stmt->ret_expr, st);
    ret_stmt->sym = ret_stmt->ret_expr->sym;
    return;
}

void stmt_typecheck(statement *stmt, symtab_stack *st) {
    if(stmt == NULL)
        return;

    switch(stmt->kind)
    {
        case STMT_VAR_DECL:
            break;
        case STMT_ASSIGN:
            break;
        case STMT_FUNC_CALL:
            break;
        case STMT_PRINT:
            break;
        case STMT_READ:
            break;
        case STMT_RETURN:
            break;
    }

    stmt_typecheck(stmt->next, st);
}