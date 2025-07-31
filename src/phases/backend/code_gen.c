#include "phases/backend/code_gen.h"
#include "utils.h"
#include "ast/decl.h"
#include <string.h>
#include "utils.h"


void codegen_program(program *p, FILE *f_out) {
    fprintf(f_out, "extern read_int\n");
    fprintf(f_out, "extern print_int\n");
    fprintf(f_out, "\n\n");
    
    codegen_data(p, f_out);
    codegen_bss(p, f_out);
    codegen_text(p, f_out);
}


void codegen_data(program *p, FILE *f_out) {
    fprintf(f_out, "section .data\n");
    
    for(decl *d=p->decl_list; d != NULL; d=d->next) {
        if(d->kind == DECL_FUNC)
            continue;
        if(!d->vd->initialized)
            continue;
        
    }
    fprintf(f_out, "\n\n");
}

void codegen_bss(program *p, FILE *f_out) {
    fprintf(f_out, "section .bss\n");
    for(decl *d=p->decl_list; d != NULL; d=d->next) {
        if(d->kind == DECL_FUNC)
            continue;
        if(d->vd->initialized)
            continue;
        fprintf(f_out, "\t%s: resb %d; \n", d->vd->name, get_size_of_type(d->vd->type));
    }
    fprintf(f_out, "\n\n");
}

void codegen_text(program *p, FILE *f_out) {
    fprintf(f_out, "section .text\n");
    fprintf(f_out, "\tglobal _start\n");
    fprintf(f_out, "_start: \n");
    fprintf(f_out, "\tcall main\n\n");
    codegen_exit(f_out);

    for(decl *d=p->decl_list; d != NULL; d=d->next) {
        if(d->kind == DECL_VAR)
            continue;
        func_decl *fd = d->fd;
        codegen_function(fd, f_out);
    }

}

void codegen_function(func_decl *fd, FILE *f_out) {
    fprintf(f_out, "\tglobal %s\n", fd->name);
    fprintf(f_out, "%s: \n", fd->name);

    // 1. function prologue and stack setup
    int local_size, temp_size;
    local_size = get_local_size(fd);
    temp_size = get_temp_size(fd);
    int stack_allocation = local_size + temp_size;

    fprintf(f_out, "\tpush rbp\n");
    fprintf(f_out, "\tmov rbp, rsp\n");
    fprintf(f_out, "\tsub rsp, %s\n\n", itoa(local_size + temp_size));

    // 2. process the statements
    tac_stmt *t_stmt = fd->code->next;
    while(t_stmt) {
        if(t_stmt->kind == TAC_ARGUMENT_STMT) {
            t_stmt = codegen_tac_function_call(t_stmt, f_out, local_size, temp_size);
            continue;
        }
        codegen_tac_stmt(t_stmt, f_out, local_size);
        t_stmt = t_stmt->next;
    }

}

void codegen_exit(FILE *f_out) {
    fprintf(f_out, ".exit:\n");
    fprintf(f_out, "\tmov rax, 60\n");
    fprintf(f_out, "\tmov rdi, 0\n");
    fprintf(f_out, "\tsyscall\n");
}

void codegen_tac_stmt(tac_stmt *stmt, FILE *f_out, int local_size) {
    if(stmt->kind == TAC_COPY_STMT) {
        if(stmt->op1->kind == TAC_OP_FUNC_CALL) {
            fprintf(f_out, "\tcall %s\n", stmt->op1->name);
            fprintf(f_out, "\tmov %s, eax\n", get_address(stmt->lhs, local_size));
            return;
        }
        fprintf(f_out, "\tmov eax, %s\n", get_address(stmt->op1, local_size));
        fprintf(f_out, "\tmov %s, eax\n", get_address(stmt->lhs, local_size));
        fprintf(f_out, "\n");
        return;
    }
    if(stmt->kind == TAC_ASSIGN_STMT) {
        fprintf(f_out, "\tmov eax, %s\n", get_address(stmt->op1, local_size));
        fprintf(f_out, "\tmov ecx, %s\n", get_address(stmt->op2, local_size));
        
        switch(stmt->op)
        {
            case OP_PLUS:
                fprintf(f_out, "\tadd eax, ecx\n");
                break;
            case OP_MINUS:
                fprintf(f_out, "\tsub eax, ecx\n");
                break;
            case OP_MUL:
                fprintf(f_out, "\timul eax, ecx\n");
                break;
            case OP_DIV:
                fprintf(f_out, "\tcdq\n");
                fprintf(f_out, "\tidiv ecx\n");
                break;
        }

        fprintf(f_out, "\tmov %s, eax\n", get_address(stmt->lhs, local_size));
        fprintf(f_out, "\n");
        return;
    }
    if(stmt->kind == TAC_PRINT_STMT) {
        fprintf(f_out, "\tmov eax, %s\n", get_address(stmt->op1, local_size));
        switch(stmt->op1->type)
        {
            case TYPE_INTEGER:
                fprintf(f_out, "\tcall print_int\n");
                break;
            case TYPE_CHARACTER:
                fprintf(f_out, "\tcall print_char\n");
                break;
            case TYPE_BOOLEAN:
                fprintf(f_out, "\tcall print_bool\n");
                break;
        }
        fprintf(f_out, "\n");
        return;
    }
    if(stmt->kind == TAC_READ_STMT) {
        fprintf(f_out, "\tmov rax, %s\n", get_address(stmt->op1, local_size));
        switch(stmt->op1->type)
        {
            case TYPE_INTEGER:
                fprintf(f_out, "\tcall read_int\n");
                break;
            case TYPE_CHARACTER:
                fprintf(f_out, "\tcall read_char\n");
                break;
            case TYPE_BOOLEAN:
                fprintf(f_out, "\tcall read_bool\n");
                break;
        }
        fprintf(f_out, "\n");
        return;
    }
    if(stmt->kind == TAC_RETURN_STMT) {
        fprintf(f_out, "\tmov eax, %s\n", get_address(stmt->op1, local_size));
        fprintf(f_out, "\tret\n");
        fprintf(f_out, "\n");
        return;
    }
}

static int get_argument_cnt(tac_stmt *t_stmt) {
    if(t_stmt->kind == TAC_ARGUMENT_STMT)
        return 1 + get_argument_cnt(t_stmt->next);
    return 0;
}

tac_stmt *codegen_tac_function_call(tac_stmt *t_stmt, FILE *f_out, int local_size, int temp_size) {
    tac_stmt *curr_stmt = t_stmt;

    int arg_size, padding, curr_frame_size;
    arg_size = 4 * get_argument_cnt(t_stmt);
    curr_frame_size = local_size + temp_size + arg_size;
    padding = align_up(curr_frame_size, 16) - curr_frame_size;
    
    // 1. Add padding to the stack
    fprintf(f_out, "\tsub rsp, %d\n", padding);
    
    // 2. Push the arguments
    while(curr_stmt->kind == TAC_ARGUMENT_STMT) {
        // fprintf(f_out, "\tmov eax, %s\n", get_address(curr_stmt->op1, local_size));
        // fprintf(f_out, "\tpush eax\n");
        fprintf(f_out, "\tpush qword %s\n", get_address(curr_stmt->op1, local_size));
        curr_stmt = curr_stmt->next;
    }

    // 3. Call the function
    fprintf(f_out, "\tcall %s\n", curr_stmt->op1->name);
    fprintf(f_out, "\tmov eax, %s\n", get_address(curr_stmt->lhs, local_size));

    // 4. Restore the stack
    fprintf(f_out, "\tadd rsp, %d\n\n", padding + arg_size);

    return curr_stmt->next;
}

