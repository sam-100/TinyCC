#include "phases/backend/code_gen.h"
#include "utils.h"
#include "ast/decl.h"
#include <string.h>

void codegen_program(program *p, FILE *f_out) {
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
    fprintf(f_out, "global _start\n");
    fprintf(f_out, "_start: \n");
    fprintf(f_out, "\tcall main\n");
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

    fprintf(f_out, "\tpush qword rbp\n");
    fprintf(f_out, "\tmov qword rbp, rsp\n");
    fprintf(f_out, "\tsub qword rsp, %s\n", itoa(local_size + temp_size));

    // 2. process the statements
    // fprintf(f_out, "\t\t ... statements ... \t\t\n");

    // 3. function epilogue and return instruction
    fprintf(f_out, "\tadd qword rsp, %s\n", itoa(local_size+temp_size));
    fprintf(f_out, "\tpop qword rbp\n");
    fprintf(f_out, "\tret\n");
    fprintf(f_out, "\n");
}

void codegen_exit(FILE *f_out) {
    fprintf(f_out, "\tmov rax, 60\n");
    fprintf(f_out, "\tmov rdi, 0\n");
    fprintf(f_out, "\tsyscall\n");
}