#ifndef ARGUMENTS_HH
#define ARGUMENTS_HH

#include <stdio.h>
#include <string.h>

#define MAX_ARGUMENTS 10

enum stop_after_t {
    STOP_AFTER_PARSING,
    STOP_AFTER_SYMTAB,
    STOP_AFTER_NAME_RESOLUTION,
    STOP_AFTER_TYPECHECK,
    STOP_AFTER_TAC_GEN,
    STOP_AFTER_CODEGEN,
    STOP_NEVER
};

void process_arguments(int argc, char **argv);

#endif