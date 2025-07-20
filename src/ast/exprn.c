#include "ast/exprn.h"
#include <stdlib.h>
#include "utils.h"
#include "declarations.h"
#include <string.h>
#include "ast/enums.h"
#include "tac/tac_stmt.h"

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
    if(e == NULL)
        return;
    
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


void resolve_exprn(exprn *e, symtab_stack *st) {
    if(e == NULL)
        return;
    
    if(e->kind == BINARY_EXPRN) {
        resolve_exprn(e->left, st);
        resolve_exprn(e->right, st);
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

void typecheck_exprn(exprn *e, symtab_stack *st) {
    if(e->kind == BINARY_EXPRN) {
        typecheck_exprn(e->left, st);
        typecheck_exprn(e->right, st);

        if(e->left->type != e->right->type) {
            fprintf(f_error, "Error (line_no %d): binary operands of different types (lhs %s, rhs %s)for operator %s.\n", e->line_no, get_type_name(e->left->type), get_type_name(e->right->type), get_op_name(e->op));
            exit(2);
        } 
        type_t type = e->left->type;
        if(get_op_type(e->op) == OP_ARITHMETIC && type != TYPE_INTEGER) {
            fprintf(f_error, "Error (line_no %d): Operanand operator type mismatch. [ lhs %s, rhs %s]\n", e->line_no, get_type_name(e->left->type), get_type_name(e->right->type));
        }
        e->type = type;
        return;
    }

    if(e->kind == IDENTIFIER_EXPRN) {
        symbol *sym = scope_lookup(e->name, st);
        e->type = sym->type;
        return;
    }
}

tac_operand *generate_tac_operand_for_exprn(exprn *e, symtab_stack *st, tac_stmt *code) {
    if(e->kind == LITERAL_EXPRN) {
        if(e->type == TYPE_INTEGER)
            return create_tac_operand_literal_int(e->value.i_val);
        if(e->type == TYPE_CHARACTER)
            return create_tac_operand_literal_char(e->value
            .c_val);
        if(e->type == TYPE_BOOLEAN)
            return create_tac_operand_literal_bool(e->value.b_val);
        
        error("Invalild type error", 2);
        return NULL;
    }
    
    if(e->kind == IDENTIFIER_EXPRN) {
        tac_operand *operand = create_tac_operand_variable(e->name, st);
        return operand;
    }

    // Binary expression :- 
    tac_stmt *curr = create_tac_stmt();
    curr->kind = TAC_ASSIGN_STMT;
    curr->op1 = generate_tac_operand_for_exprn(e->left, st, code);
    curr->op2 = generate_tac_operand_for_exprn(e->right, st, code);
    curr->lhs = create_tac_operand_temp(e->type);   // generate a new temp variable
    curr->op = e->op;
    tac_append(code, curr);

    if(curr->op1->kind == TAC_OP_TEMP)
        freeTemp(curr->op1->temp);
    if(curr->op2->kind == TAC_OP_TEMP)
        freeTemp(curr->op2->temp);

    return curr->lhs;
}

