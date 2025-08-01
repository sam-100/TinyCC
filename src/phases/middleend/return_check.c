#include "phases/middleend/return_check.h"
#include "utils.h"

bool return_check_program(program *p) {
    for(decl *d=p->decl_list; d != NULL; d=d->next) {
        if(d->kind == DECL_VAR)
            continue;
        if(!return_check_function(d->fd)) {
            fprintf(f_error, "The function %s does not return from all paths.\n", d->fd->name);
            return false;
        }
    }
    return true;
}

bool return_check_function(func_decl *fd) {
    if(fd->type == TYPE_VOID)
        return true;
    return return_check_stmt(fd->body->stmt_list);
}


bool return_check_stmt(statement *stmt) {
    if(stmt == NULL)
        return false;
    if(stmt->kind == STMT_RETURN)
        return true;
    return return_check_stmt(stmt->next);
}