#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void error(const char *msg, int status) {
    fprintf(stderr, "%s\n", msg);
    exit(status);
}