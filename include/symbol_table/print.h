#ifndef SYMBOL_TABLE_PRINT_H
#define SYMBOL_TABLE_PRINT_H

#include "symbol_table/symtab.h"

void print_symtab_program(const program *p);

void print_symtab_decl(const decl *d);
void print_symtab_func_decl(const func_decl *fd);

void print_symbol(const symbol *sym);
void print_symtab(const symtab *stab);
void print_symtab_block_stmt(const block_stmt *stmt, const func_decl *fd);

#endif