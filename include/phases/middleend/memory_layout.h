#ifndef MEMORY_LAYOUT_H
#define MEMORY_LAYOUT_H

#include "ast/program.h"
#include "ast/decl.h"
#include "ast/stmt.h"
#include "ast/func.h"

void memory_layout_program(program *p);
void memory_layout_func_decl(func_decl *fd);
int memory_layout_stmt_list(statement *stmt_list);
void memory_layout_block_stmt(block_stmt *blk_stmt);

#endif
