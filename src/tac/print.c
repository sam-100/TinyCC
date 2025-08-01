#include "tac/print.h"
#include <stdio.h>
#include "utils.h"

void print_tac_of_program(const program *p, FILE *f_out) {
    fprintf(f_out, "--------------- Three Address code --------------\n\n");
    for(decl *d=p->decl_list; d != NULL; d=d->next) {
        if(d->kind == DECL_VAR)
            continue;
        print_tac_of_function(d->fd, f_out);
    }
}

void print_tac_of_function(const func_decl *fd, FILE *f_out) {
    fprintf(f_out, "FUNCTION %s BEGIN (temp_cnt = %d):\n", fd->name, fd->body->temp_cnt);
    print_tac_stmt(fd->code->next, f_out);
    fprintf(f_out, "FUNCTION END\n\n");
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
            fprintf(file, "\treturn %s\n", tac_op_to_string(t->op1));
            break;
        case TAC_RETURN_VOID_STMT:
            fprintf(file, "\treturn\n");
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