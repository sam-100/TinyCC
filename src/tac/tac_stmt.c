#include "tac/tac_stmt.h"
#include "tac/tac_operand.h"
#include "ast/exprn.h"
#include "ast/stmt.h"
#include <stdlib.h>
#include "utils.h"

tac_stmt *tac_append(tac_stmt *first, tac_stmt *second) {
    if(first == NULL)
        return second;
    
    tac_stmt *ptr = first;
    while(ptr->next != NULL)
        ptr = ptr->next;
    ptr->next = second;
    return first;
}

tac_stmt *get_last(tac_stmt *ptr) {
    while(ptr->next)
        ptr=ptr->next;
    return ptr;
}

tac_stmt *create_tac_stmt() {
    tac_stmt *t = (tac_stmt*)malloc(sizeof(tac_stmt));
    t->next = NULL;
    return t;
}

void print_tac_stmt(tac_stmt *t, FILE *file) {
    switch(t->kind) 
    {
        case TAC_COPY_STMT:
            fprintf(file, "\t%s = %s\n", 
                tac_op_to_string(t->lhs), 
                tac_op_to_string(t->op1)
            );
            break;
        case TAC_ASSIGN_STMT:
            fprintf(file, "\t%s = %s %s %s\n", 
                tac_op_to_string(t->lhs), 
                tac_op_to_string(t->op1), 
                op_to_string(t->op), 
                tac_op_to_string(t->op2)
            );
            break;
        case TAC_PRINT_STMT:
            fprintf(file, "\tprint %s\n", 
                tac_op_to_string(t->op1)
            );
            break;
        case TAC_READ_STMT:
            fprintf(file, "\tread %s\n", 
                tac_op_to_string(t->op1)
            );
            break;
        case TAC_RETURN_STMT:
            fprintf(file, "\treturn %s\n", 
                tac_op_to_string(t->op1)
            );
            break;
        case TAC_FUNC_CALL_STMT:
            fprintf(file, "\t%s\n", 
                tac_op_to_string(t->op1)
            );
            break;
        case TAC_ARGUMENT_STMT:
            fprintf(file, "\targ %s\n", 
                tac_op_to_string(t->op1)
            );
            break;
    }

    if(t->next)
        print_tac_stmt(t->next, file);
}