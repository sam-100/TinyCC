#ifndef UTILS_H
#define UTILS_H
#include "ast/enums.h"
#include <stdbool.h>

void error(const char *msg, int status);
void initialize();
type_t get_type(int num);
char *itoa(int num);
char *btoa(bool val);
void reverse(char *str);
int get_size_of_type(type_t type);
operation_t get_op_type(operator_t op);
char *op_to_string(operation_t op);
int max(int a, int b);

// string functions 
char *dup_string(const char *str);                              // copy the string 'str' into a new buffer
char *concat_string(const char *str1, const char *str2);        // concatinate strings 'str1' and 'str2' into a new buffer


/* Helper functions to print ast */
char *get_type_name(type_t type);
char *get_op_name(operator_t op);
char *get_literal_value(value val, type_t type);
char *get_scope_name(scope_t scope);
char *get_symbol_kind_name(symbol_t kind);


#endif
