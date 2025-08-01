#ifndef RETURN_CHECK
#define RETURN_CHECK

#include "ast/program.h"
#include "ast/stmt.h"
#include "ast/decl.h"

bool return_check_program(program *p);
bool return_check_function(func_decl *fd);
bool return_check_stmt(statement *stmt);
bool add_return_stmt(statement *stmt, func_decl *fd);      // add return statements to the void function
#endif