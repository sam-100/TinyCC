#include "tac/tac_stmt.h"
#include "tac/tac_operand.h"
#include "ast/exprn.h"
#include "ast/stmt.h"
#include <stdlib.h>

tac_stmt *tac_append(tac_stmt *first, tac_stmt *second) {
    if(first == NULL)
        return second;
    
    tac_stmt *ptr = first;
    while(ptr->next != NULL)
        ptr = ptr->next;
    ptr->next = second;
    return first;
}

tac_stmt *get_last(tac_stmt *ptr) {
    while(ptr->next)
        ptr=ptr->next;
    return ptr;
}

tac_stmt *create_tac_stmt() {
    tac_stmt *t = (tac_stmt*)malloc(sizeof(tac_stmt));
    return t;
}