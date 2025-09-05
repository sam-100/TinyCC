#include "phases/middleend/memory_layout.h"
#include "utils.h"

void memory_layout_program(program *p) {
    for(decl *d=p->decl_list; d != NULL; d=d->next) {
        if(d->kind == DECL_VAR)
            continue;
        memory_layout_func_decl(d->fd);
    }
}

void memory_layout_func_decl(func_decl *fd) {
    int index = 1, offset = 16;
    for(parameter *p=fd->param_list; p != NULL; p=p->next) {
        p->sym->which = index;
        p->sym->offset = offset;
        index++;
        offset += 8;
    }

    memory_layout_block_stmt(fd->body);
}

void memory_layout_block_stmt(block_stmt *blk_stmt) {
    blk_stmt->local_len = memory_layout_stmt_list(blk_stmt->stmt_list);
}

int memory_layout_stmt_list(statement *stmt_list) {
    int index, offset;
    index=0;
    offset=0;
    for(statement *stmt=stmt_list; stmt != NULL; stmt=stmt->next) {
        if(stmt->kind == STMT_VAR_DECL) {
            index++;
            offset -= 8;
            stmt->vd_stmt->sym->which=index;
            stmt->vd_stmt->sym->offset=abs(offset);
        }
    }
    return -offset;
}

