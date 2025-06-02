#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

void initialize() {

}

void error(const char *msg, int status) {
    fprintf(stderr, "%s\n", msg);
    exit(status);
}

type_t get_type(int t) {
    switch(t) {
        case INTEGER:
            return TYPE_INTEGER;
        case BOOLEAN:
            return TYPE_BOOLEAN;
        case CHARACTER:
            return TYPE_CHARACTER;
        case VOID:
            return TYPE_VOID;
    }
}
