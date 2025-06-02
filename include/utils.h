#ifndef UTILS_H
#define UTILS_H
#include "enums.h"
#include <stdbool.h>

void error(const char *msg, int status);
void initialize();
type_t get_type(int num);

/* Helper functions to print ast */
char *get_type_name(type_t type);
char get_op_name(operator_t op);
char *btoa(bool val);

#endif
