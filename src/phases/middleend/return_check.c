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
    if(return_check_stmt(fd->body->stmt_list))
        return true;
    if(fd->type == TYPE_VOID) {
        add_return_stmt(fd->body->stmt_list, fd);
        return true;
    }
    return return_check_stmt(fd->body->stmt_list);
}


bool return_check_stmt(statement *stmt) {
    if(stmt == NULL)
        return false;
    if(stmt->kind == STMT_RETURN)
        return true;
    return return_check_stmt(stmt->next);
}

bool add_return_stmt(statement *stmt, func_decl *fd) {
    if(stmt->next == NULL) {
        return_stmt *r_stmt = create_ret_stmt(NULL);
        r_stmt->fd = fd;
        stmt->next = create_stmt_from_return(r_stmt);
        return true;
    }
    return add_return_stmt(stmt->next, fd);
}