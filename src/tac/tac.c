#include "tac/tac.h"
#include "ast/func.h"

// tac_stmt *create_tac_parameter(parameter *param) {
//     tac_stmt *t = (tac_stmt*)malloc(sizeof(tac_stmt));
//     t->kind = TAC_PARAMETER;
    
//     t->t_param = (tac_parameter*)malloc(sizeof(tac_parameter));
//     t->t_param->name = param->name;
//     t->t_param->type = param->type;

//     t->index = param->sym->which;
//     t->offset = param->offset;
//     return t;
// }