#include "print-ast.h"
#include <stdio.h>
#include "utils.h"
#include "decl.h"

extern FILE *f_ast;


/* Here functions to print the ast */
void print_program(program *p) {
    fprintf(f_ast, "Program {\n");
    print_decl(p->decl_list);
    fprintf(f_ast, "}\n");
}

void print_decl(decl *d) {
    if(d == NULL)
        return;
    
    fprintf(f_ast, "Declaration {\n");
    switch(d->kind)
    {
        case VAR_DECLARATION:
            print_var_decl(d->vd);
            break;
        case FUNC_DECLARATION:
            print_func_decl(d->fd);
            break;
    }
    fprintf(f_ast, "}\n");
    print_decl(d->next);
}

void print_var_decl(var_decl *vd) {
    if(vd == NULL)
        return;
    fprintf(f_ast, "Var Declaration {\n");
    fprintf(f_ast, "Name: %s;\n", vd->name);
    fprintf(f_ast, "Type: %s;\n", get_type_name(vd->type));
    if(vd->initialized)
        print_exprn(vd->rhs);
    fprintf(f_ast, "}\n");
}

void print_func_decl(func_decl *fd) {
    if(fd == NULL)
        return;
    fprintf(f_ast, "Func Declaration {\n");
    fprintf(f_ast, "Name: %s;\n", fd->name);
    fprintf(f_ast, "Type: %s;\n", get_type_name(fd->type));
    print_param(fd->param_list);
    print_body(fd->body);
    fprintf(f_ast, "}\n");
}

void print_exprn(exprn *e) {
    if(e == NULL)
        return;
    fprintf(f_ast, "Exprn {\n");
    fprintf(f_ast, "Type: %s;\n", get_type_name(e->type));
    if(e->kind == BINARY_EXPRN) {
        print_exprn(e->left);
        fprintf(f_ast, "%c\n", get_op_name(e->op));
        print_exprn(e->right);
    } else if(e->kind == LITERAL_EXPRN) {
        switch(e->type)
        {
            case TYPE_INTEGER:
                fprintf(f_ast, "Value: %d;\n", e->value.i_val);
                break;
            case TYPE_CHARACTER:
                fprintf(f_ast, "Value: %c;\n", e->value.c_val);
                break;
            case TYPE_BOOLEAN:
                fprintf(f_ast, "Value: %s;\n", btoa(e->value.b_val));
        }
    } else {
        fprintf(f_ast, "%s\n", e->name);
    }
    fprintf(f_ast, "}\n");
}

void print_param(parameter *p) {

}

void print_body(func_body *fb) {

}


/* Other utility functions */
char *get_type_name(type_t type) {
    switch(type)
    {
        case TYPE_VOID:
            return "void";
        case TYPE_INTEGER:
            return "integer";
        case TYPE_BOOLEAN:
            return "bool";
        case TYPE_CHARACTER:
            return "char";
        default:
            return "unknown-type";
    }
}

char get_op_name(operator_t op) {
    switch(op)
    {
        case OP_PLUS:
            return '+';
        case OP_MINUS:
            return '-';
        case OP_MUL:
            return '*';
        case OP_DIV:
            return '/';
        default:
            return '?';
    }
}

char *btoa(bool val) {
    if(val == true)
        return "true";
    return "false";
}

