#include "ast/func.h"
#include "ast/stmt.h"
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>
#include "symbol_table/symtab_stack.h"

// Create arguments and parameters
argument *create_arg(exprn *e) {
    argument *a = (argument*)malloc(sizeof(argument));
    a->e = e;
    a->next = NULL;
    a->which = 1;
    return a;
}

argument *append_arg(argument *a, argument *na) {
    argument *ptr=a;
    while(ptr->next)
        ptr=ptr->next;
    ptr->next = na;
    na->which = ptr->which+1;
    // printf("argument %s(%d) appended to argument %s(%d).\n", na->e->name, na->which, ptr->e->name, ptr->which);
    return a;
}


parameter *create_param(char *name, type_t type) {
    parameter *p = (parameter*)malloc(sizeof(parameter));
    p->name = name;
    p->type = type;
    p->next = NULL;
    p->which = 1;
    p->offset = 0;
    return p;
}

parameter *append_param(parameter *p, parameter *np) {
    parameter *ptr = p;
    while(ptr->next)
        ptr = ptr->next;
    ptr->next = np;
    np->which = ptr->which+1;
    np->offset = ptr->offset+get_size_of_type(ptr->type);
    // printf("appending parameter %s to %s.\n", np->name, ptr->name);
    return p;
}



// Function call and body
func_call *create_func_call(char *name, argument *arg_list) {
    func_call *fc = (func_call*)malloc(sizeof(func_call));
    fc->name = name;
    fc->arg_list = arg_list;
    fc->sym = NULL;
    return fc;
}

func_body *create_func_body(statement *stmt_list) {
    func_body *fb = (func_body*)malloc(sizeof(func_body));
    fb->stmt_list = stmt_list;
    fb->symtab = NULL;
    fb->local_len = 0;
    fb->temp_cnt = 0;
    return fb;
}



void memory_layout_func_body(func_body *fb) {
    fb->local_len = memory_layout_stmt_list(fb->stmt_list);
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

int generate_tac_for_func_argument(argument *arg, symtab_stack *st, tac_stmt *code, int *temp_cnt) {
    if(arg == NULL)
        return 0;
    
    int arg_cnt = 1 + generate_tac_for_func_argument(arg->next, st, code, temp_cnt);

    tac_stmt *curr = create_tac_stmt();
    curr->kind = TAC_ARGUMENT_STMT;
    curr->op1 = generate_tac_operand_for_exprn(arg->e, st, code, temp_cnt);
    tac_append(code, curr);
    if(curr->op1->kind == TAC_OP_TEMP)
        freeTemp(curr->op1->temp);
    return arg_cnt;
}