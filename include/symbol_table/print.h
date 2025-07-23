#ifndef SYMBOL_TABLE_PRINT_H
#define SYMBOL_TABLE_PRINT_H

#include "symbol_table/symtab.h"

void print_symtab_program(program *p);

void print_symtab_decl(decl *d);
void print_symtab_func_decl(func_decl *fd);

void print_symbol(symbol *sym);
void print_symtab(symtab *stab);

#endif