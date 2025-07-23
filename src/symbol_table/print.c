#include "symbol_table/print.h"
#include "utils.h"
#include "ast/program.h"


void print_symtab_program(const program *p) {
    fprintf(f_symtab, "Global Symbol Table: \n");
    print_symtab(p->sym_tab);

    // print symbol table of each function
    print_symtab_decl(p->decl_list);
}

void print_symtab_decl(const decl *d) {
    if(d == NULL)
        return;
    if(d->kind == DECL_FUNC)
        print_symtab_func_decl(d->fd);
    print_symtab_decl(d->next);
}

void print_symtab_func_decl(const func_decl *fd) {
    if(fd->body == NULL)
        return;
    fprintf(f_symtab, "Function %s() symtab: \n", fd->name);
    fprintf(f_symtab, "{local_len: %d}\n", fd->body->local_len);
    print_symtab(fd->symtab);
}


void print_symbol(const symbol *sym) {
    fprintf(f_symtab, "{\n");
    fprintf(f_symtab, "\tname: %s;\n", sym->name);
    fprintf(f_symtab, "\ttype: %s;\n", get_type_name(sym->type));
    fprintf(f_symtab, "\tkind: %s;\n", get_symbol_kind_name(sym->kind));
    fprintf(f_symtab, "\tscope: %s;\n", get_scope_name(sym->scope));
    // fprintf(f_symtab, "\taddress: %p;\n", sym);

    switch(sym->kind)
    {
        case SYM_VAR:
            fprintf(f_symtab, "\twhich: %d;\n", sym->which);
            fprintf(f_symtab, "\toffset: %d;\n", sym->offset);
        
        case SYM_FUNC:
            fprintf(f_symtab, "\tparameters: \n");
            for(symbol *ptr=sym->next_param; ptr != NULL; ptr=ptr->next_param) {
                fprintf(f_symtab, "\t\tparameter %d [%d]: %s: %s\n", ptr->which, ptr->offset, ptr->name, get_type_name(ptr->type));
            }
            break;
        case SYM_PARAM:
            fprintf(f_symtab, "\twhich: %d;\n", sym->which);
            fprintf(f_symtab, "\toffset: %d;\n", sym->offset);
            break;            
        default:
            fprintf(f_symtab, "Unknown kind of symbol\n");
            break;
    }
    fprintf(f_symtab, "}\n");
}

void print_symtab(const symtab *stab) {
    fprintf(f_symtab, "---------------SYMTAB START---------------\n");
    for(int i=0; i<stab->size; i++) {
        fprintf(f_symtab, "name: %s\n", stab->names[i]);
        print_symbol(stab->symbols[i]);
    }
    fprintf(f_symtab, "---------------SYMTAB END---------------\n\n\n");
}

