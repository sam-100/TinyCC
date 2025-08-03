#include "phases/middleend/generate_tac.h"
#include <stdlib.h>
#include "utils.h"

void generate_tac_for_program(program *p) {
    symtab_stack *st = create_symtab_stack();
    scope_push(p->sym_tab, st);
    for(decl *d = p->decl_list; d != NULL; d=d->next) {
        if(d->kind == DECL_VAR)
            continue;
        generate_tac_for_function(d->fd, st);
    }
    scope_pop(st);
}

void generate_tac_for_function(func_decl *fd, symtab_stack *st) {
    fd->code = create_tac_stmt();       // dummy head node
    
    scope_push(fd->symtab, st);
    for(statement *stmt = fd->body->stmt_list; stmt != NULL; stmt = stmt->next) {
        generate_tac_for_statement(stmt, st, fd->code, &fd->body->temp_cnt);
    }
    scope_pop(st);
}

tac_operand *generate_tac_for_func_call(func_call *fc, symtab_stack *st, tac_stmt *code, int *temp_cnt) {
    tac_stmt *curr = create_tac_stmt();
    curr->kind = TAC_COPY_STMT;
    curr->lhs = create_tac_operand_temp(fc->type, temp_cnt);
    
    int arg_cnt = 0;
    arg_cnt = generate_tac_for_func_argument(fc->arg_list, st, code, temp_cnt);

    curr->op1 = (tac_operand*)malloc(sizeof(tac_operand));
    curr->op1->kind = TAC_OP_FUNC_CALL;
    curr->op1->name = fc->name;
    curr->op1->arg_cnt = arg_cnt;
    tac_append(code, curr);
    return curr->lhs;
}

/* Generate tac for function arguments by pushing them in reverse order */
int generate_tac_for_func_argument(argument *arg, symtab_stack *st, tac_stmt *code, int *temp_cnt) {
    if(arg == NULL)
        return 0;
    
    // add a prepare stack element
    tac_stmt *prepare_stack = create_tac_stmt();
    prepare_stack->kind = TAC_PREPARE_STACK;
    tac_append(code, prepare_stack);

    // push arguments in reverse order
    int arg_cnt = 1 + generate_tac_for_func_argument(arg->next, st, code, temp_cnt);

    // push current argument
    tac_stmt *curr = create_tac_stmt();
    curr->kind = TAC_ARGUMENT_STMT;
    curr->op1 = generate_tac_operand_for_exprn(arg->e, st, code, temp_cnt);
    tac_append(code, curr);
    if(curr->op1->kind == TAC_OP_TEMP)
        freeTemp(curr->op1->temp);
    return arg_cnt;
}

void generate_tac_for_statement(statement *stmt, symtab_stack *st, tac_stmt *code, int *temp_cnt) {
    tac_stmt *curr = create_tac_stmt();
    switch(stmt->kind) {
        case STMT_PRINT:
            curr->kind = TAC_PRINT_STMT;
            curr->op1 = generate_tac_operand_for_exprn(stmt->p_stmt->arg, st, code, temp_cnt);
            break;
        case STMT_READ:
            curr->kind = TAC_READ_STMT;
            curr->op1 = create_tac_operand_variable(stmt->r_stmt->arg, st);
            break;
        case STMT_VAR_DECL:
            if(!stmt->vd_stmt->initialized)
                return;
            curr->kind = TAC_COPY_STMT;
            curr->lhs = create_tac_operand_variable(stmt->vd_stmt->name, st);
            curr->op1 = generate_tac_operand_for_exprn(stmt->vd_stmt->rhs, st, code, temp_cnt);
            break;
        case STMT_ASSIGN:
            curr->kind = TAC_COPY_STMT;
            curr->lhs = create_tac_operand_variable(stmt->as_stmt->name, st);
            if(stmt->as_stmt->kind == ASSIGN_EXPRN) {
                curr->op1 = generate_tac_operand_for_exprn(stmt->as_stmt->e, st, code, temp_cnt);
            } else {
                curr->op1 = generate_tac_for_func_call(stmt->as_stmt->fc, st, code, temp_cnt);
            }
            break;
        case STMT_FUNC_CALL:
            curr->kind = TAC_COPY_STMT;
            curr->lhs = create_tac_operand_temp(stmt->fc_stmt->type, temp_cnt);
            curr->op1 = generate_tac_for_func_call_stmt(stmt->fc_stmt, st, code, temp_cnt);
            break;
        case STMT_RETURN:
            if(stmt->ret_stmt->fd->type == TYPE_VOID) {
                curr->kind = TAC_RETURN_VOID_STMT;
            } else {
                curr->kind = TAC_RETURN_STMT;
                curr->op1 = generate_tac_operand_for_exprn(stmt->ret_stmt->ret_expr, st, code, temp_cnt);
            }
            break;
    }
    tac_append(code, curr);

    // free temps here
    if(curr->op1 && curr->op1->kind == TAC_OP_TEMP)
        freeTemp(curr->op1->temp);
    if(curr->op2 && curr->op2->kind == TAC_OP_TEMP)
        freeTemp(curr->op2->temp);
}

tac_operand *generate_tac_for_func_call_stmt(func_call_stmt *fc_stmt, symtab_stack *st, tac_stmt *code, int *temp_cnt) {
    tac_operand *curr = create_tac_operand_func_call(fc_stmt->type, fc_stmt->name);

    // add a prepare stack element
    tac_stmt *prepare_stack = create_tac_stmt();
    prepare_stack->kind = TAC_PREPARE_STACK;
    tac_append(code, prepare_stack);

    // append arguments 
    int arg_cnt = 0;
    for(argument *arg=fc_stmt->args; arg != NULL; arg=arg->next) {
        generate_tac_for_func_argument(arg, st, code, temp_cnt);
        arg_cnt++;
    }
    curr->arg_cnt = arg_cnt;

    return curr;
}


tac_operand *generate_tac_operand_for_exprn(exprn *e, symtab_stack *st, tac_stmt *code, int *temp_cnt) {
    if(e == NULL)
        return NULL;
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
    curr->op1 = generate_tac_operand_for_exprn(e->left, st, code, temp_cnt);
    curr->op2 = generate_tac_operand_for_exprn(e->right, st, code, temp_cnt);
    curr->lhs = create_tac_operand_temp(e->type, temp_cnt);   // generate a new temp variable
    curr->op = e->op;
    tac_append(code, curr);

    if(curr->op1->kind == TAC_OP_TEMP)
        freeTemp(curr->op1->temp);
    if(curr->op2->kind == TAC_OP_TEMP)
        freeTemp(curr->op2->temp);

    return curr->lhs;
}

