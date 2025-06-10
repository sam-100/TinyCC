#include "exprn.h"
#include <stdlib.h>
#include "utils.h"
#include "declarations.h"
#include <string.h>
#include "enums.h"

exprn *create_exprn(exprn *lhs, operator_t op, exprn *rhs) {
    exprn *e = (exprn*)malloc(sizeof(exprn));
    e->kind = BINARY_EXPRN;
    e->left = lhs;
    e->right = rhs;
    e->op = op;
    return e;
}

exprn *negate_exprn(exprn *expn) {
    exprn *e = (exprn*)malloc(sizeof(exprn));
    e->kind = BINARY_EXPRN;
    e->left = expn;
    e->right = create_exprn_int(-1);
    e->op = OP_MUL;
    return e;
}

exprn *create_exprn_id(char *name) {
    exprn *e = (exprn*)malloc(sizeof(exprn));
    e->kind = IDENTIFIER_EXPRN;
    e->name = name;
    return e;
}

exprn *create_exprn_int(int val) {
    exprn *e = (exprn*)malloc(sizeof(exprn));
    e->kind = LITERAL_EXPRN;
    e->type = TYPE_INTEGER;
    e->value.i_val = val;
    return e;
}
exprn *create_exprn_char(char val) {
    exprn *e = (exprn*)malloc(sizeof(exprn));
    e->kind = LITERAL_EXPRN;
    e->type = TYPE_CHARACTER;
    e->value.c_val = val;
    return e;
}
exprn *create_exprn_bool(bool val) {
    exprn *e = (exprn*)malloc(sizeof(exprn));
    e->kind = LITERAL_EXPRN;
    e->type = TYPE_BOOLEAN;
    e->value.b_val = val;
    return e;
}

void print_exprn(exprn *e, char *tabs) {
    fprintf(f_ast, "%sexprn \n", tabs);
    fprintf(f_ast, "%sline_no: %d;\n", tabs, e->line_no);
    fprintf(f_ast, "%s{\n", tabs);
    
    tabs = strcat(tabs, "\t");
    switch(e->kind)
    {
        case BINARY_EXPRN:
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


void exprn_resolve(exprn *e, symtab_stack *st) {
    if(e->kind == BINARY_EXPRN) {
        exprn_resolve(e->left, st);
        exprn_resolve(e->right, st);
        return;
    }

    if(e->kind == IDENTIFIER_EXPRN) {
        if(scope_lookup(e->name, st) == false) {
            fprintf(f_error, "Error: Symbol %s at line no. %d not declared before.\n", e->name, e->line_no);
            exit(1);
        }
        e->sym = scope_lookup(e->name, st);
        return;
    }

    if(e->kind == LITERAL_EXPRN) {
        // todo: handle literal expressions here
    }
}

void exprn_typecheck(exprn *e, symtab_stack *st) {

}