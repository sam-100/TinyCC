#include "ast/print.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

/* Functions to print program */
void print_program(const program *p) {
    fprintf(f_ast, "AST of given program: \n\n");
    print_decl(p->decl_list);
}

/* Functions to print declaration */
void print_decl(const decl *d) {
    if(d == NULL)
        return;
    
    if(d->kind == DECL_VAR) {
        print_var_decl(d->vd);
    } else if(d->kind == DECL_FUNC) {
        print_func_decl(d->fd);
    } else {
        fprintf(f_ast, "Unknown declaration: %d\n", d->kind);
    }
    print_decl(d->next);
}

void print_var_decl(const var_decl *vd) {
    fprintf(f_ast, "VAR DECLARATION {\n");
    fprintf(f_ast, "\tname=%s;\n", vd->name);
    fprintf(f_ast, "\ttype=%s;\n", get_type_name(vd->type));
    fprintf(f_ast, "\tline_no=%d;\n", vd->line_no);
    fprintf(f_ast, "}\n");
}

void print_func_decl(const func_decl *fd) {
    fprintf(f_ast, "FUNC DECLARATION {\n");
    fprintf(f_ast, "\tname: %s;\n", fd->name);
    fprintf(f_ast, "\ttype: %s;\n", get_type_name(fd->type));
    fprintf(f_ast, "\tline_no: %d;\n", fd->line_no);
    fprintf(f_ast, "\tparameters: ");
    print_param(fd->param_list);
    fprintf(f_ast, ";\n");
    if(fd->body != NULL) {
        fprintf(f_ast, "\tbody: \n");
        char *tabs = (char*)malloc(100);
        tabs[0] = '\t';
        tabs[1] = '\0';
        print_stmt_block(fd->body, tabs);
        free(tabs);
    }
    fprintf(f_ast, "}\n");
}


/* Functions to print function body, function call, arguments, and parameters */
void print_arg(const argument *arg, char *tabs) {
    for(const argument *ptr=arg; ptr != NULL; ptr=ptr->next) {
        fprintf(f_ast, "%sargument {\n", tabs);
        fprintf(f_ast, "%s\twhich: %d;\n", tabs, ptr->which);
        print_exprn(ptr->e, strcat(tabs, "\t"));
        tabs[strlen(tabs)-1]='\0';
        fprintf(f_ast, "%s}\n", tabs);
    }
}

void print_param(const parameter *p) {
    if(p == NULL)
        return;
    fprintf(f_ast, "{%s: %s} ", p->name, get_type_name(p->type));
    print_param(p->next);
}

void print_func_call(const func_call *fc, char *tabs) {
    fprintf(f_ast, "%sfunc_call {\n", tabs);

    strcat(tabs, "\t");
    fprintf(f_ast, "%sname: %s;\n", tabs, fc->name);
    fprintf(f_ast, "%sarguments: \n", tabs);
    print_arg(fc->arg_list, strcat(tabs, "\t"));
    tabs[strlen(tabs)-2]='\0';

    fprintf(f_ast, "\n");
    fprintf(f_ast, "%s}\n", tabs);
}


/* functions to print statements of various types */
void print_statement(const statement *stmt, char *tabs) {
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
        case STMT_BLOCK:
            print_stmt_block(stmt->blk_stmt, tabs);
            break;
        case STMT_IF:
            print_stmt_if(stmt->if_stmt, tabs);
            break;
        default:
            fprintf(f_ast, "%sInvalid statement with code %d\n", tabs, (int)stmt->kind);
            break;
    }
    print_statement(stmt->next, tabs);
}

void print_stmt_var_decl(const var_decl_stmt *vd_stmt, char *tabs) {
    fprintf(f_ast, "%svar_decl_stmt {\n", tabs);
    fprintf(f_ast, "%s\tname: %s;\n", tabs, vd_stmt->name);
    fprintf(f_ast, "%s\ttype: %s;\n", tabs, get_type_name(vd_stmt->type));
    fprintf(f_ast, "%s\tline_no: %d;\n", tabs, vd_stmt->line_no);
    fprintf(f_ast, "%s\tinit: %s;\n", tabs, btoa(vd_stmt->initialized));
    fprintf(f_ast, "%s}\n", tabs);
}

void print_stmt_assignment(const assign_stmt *asstmt, char *tabs) {
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

void print_stmt_func_call(const func_call_stmt *fc_stmt, char *tabs) {
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

void print_stmt_print(const print_stmt *p_stmt, char *tabs) {
    fprintf(f_ast, "%sprint_stmt {\n", tabs);
    fprintf(f_ast, "%s\tline_no: %d;\n", tabs, p_stmt->line_no);
    fprintf(f_ast, "%s\targuments: \n", tabs);
    print_exprn(p_stmt->arg, strcat(tabs, "\t\t"));
    tabs[strlen(tabs)-2]='\0';
    fprintf(f_ast, "%s}\n", tabs);
}

void print_stmt_read(const read_stmt *r_stmt, char *tabs) {
    fprintf(f_ast, "%sread_stmt {\n", tabs);
    fprintf(f_ast, "%s\tline_no: %d;\n", tabs, r_stmt->line_no);
    fprintf(f_ast, "%s\targument: %s\n", tabs, r_stmt->arg);
    fprintf(f_ast, "%s}\n", tabs);
}

void print_stmt_return(const return_stmt *ret_stmt, char *tabs) {
    fprintf(f_ast, "%sreturn_stmt {\n", tabs);
    // fprintf(f_ast, "type: %s\n", get_type_name(ret_stmt->type));
    fprintf(f_ast, "%s\tline_no: %d;\n", tabs, ret_stmt->line_no);
    fprintf(f_ast, "%s\targuments: \n", tabs);
    print_exprn(ret_stmt->ret_expr, strcat(tabs, "\t\t"));
    tabs[strlen(tabs)-2]='\0';
    fprintf(f_ast, "%s}\n", tabs);

}

void print_stmt_block(const block_stmt *stmt, char *tabs) {
    fprintf(f_ast, "%sBLOCK (line_no: %d)\n", tabs, stmt->line_no);
    if(stmt->stmt_list == NULL)
        return;
    
    fprintf(f_ast, "%s{\n", tabs);
    print_statement(stmt->stmt_list, strcat(tabs, "\t"));
    tabs[strlen(tabs)-2]='\0';
    fprintf(f_ast, "%s}\n", tabs);
}

void print_stmt_if(const if_stmt *stmt, char *tabs) {
    fprintf(f_ast, "%sif_stmt {\n", tabs);
    fprintf(f_ast, "%scondition:\n", tabs);
    print_exprn(stmt->condition, strcat(tabs, "\t"));
    tabs[strlen(tabs)-2]='\0';
    fprintf(f_ast, "%sBlock:\n", tabs);
    print_stmt_block(stmt->block, strcat(tabs, "\t"));
    tabs[strlen(tabs)-2]='\0';
    fprintf(f_ast, "%s}\n", tabs);
}

/* Function to print the expression */
void print_exprn(const exprn *e, char *tabs) {
    if(e == NULL)
        return;
    
    fprintf(f_ast, "%sexprn \n", tabs);
    fprintf(f_ast, "%sline_no: %d;\n", tabs, e->line_no);
    fprintf(f_ast, "%s{\n", tabs);
    
    tabs = strcat(tabs, "\t");
    switch(e->kind)
    {
        case ARITHMETIC_EXPRN:
        case BOOLEAN_EXPRN:
        case COMPARISON_EXPRN:
            fprintf(f_ast, "%slhs:\n", tabs);
            print_exprn(e->left, strcat(tabs, "\t"));
            tabs[strlen(tabs)-1]='\0';
            fprintf(f_ast, "%soperator: %s\n", tabs, get_op_name(e->op));
            fprintf(f_ast, "%srhs:\n", tabs);
            print_exprn(e->right, strcat(tabs, "\t"));
            tabs[strlen(tabs)-1]='\0';
            break;
        case IDENTIFIER_EXPRN:
            fprintf(f_ast, "%sname: %s\n", tabs, e->name);
            break;
        case LITERAL_EXPRN:
            fprintf(f_ast, "%sliteral: %s\n", tabs, get_literal_value(e->value, e->type));
            break;
        default:
            break;
    }
    tabs[strlen(tabs)-1] = '\0';
    fprintf(f_ast, "%s}\n", tabs);
}


