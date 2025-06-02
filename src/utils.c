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

char *get_type_name(type_t type) {
    switch(type)
    {
        case TYPE_VOID:
            return "void";
        case TYPE_INTEGER:
            return "integer";
        case TYPE_BOOLEAN:
            return "bool";
        case TYPE_CHARACTER:
            return "char";
        default:
            return "unknown-type";
    }
}

char get_op_name(operator_t op) {
    switch(op)
    {
        case OP_PLUS:
            return '+';
        case OP_MINUS:
            return '-';
        case OP_MUL:
            return '*';
        case OP_DIV:
            return '/';
        default:
            return '?';
    }
}

char *btoa(bool val) {
    if(val == true)
        return "true";
    return "false";
}

