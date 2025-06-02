#ifndef UTILS_H
#define UTILS_H
#include "enums.h"
#include <stdbool.h>

void error(const char *msg, int status);
void initialize();
type_t get_type(int num);


#endif
