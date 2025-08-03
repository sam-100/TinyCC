#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include <string.h>
#include "declarations.h"
#include "tac/tac_stmt.h"

extern char *input_name;
void initialize() {
    for(int i=0; i<MAX_TEMP; i++)
        temp_store[i] = 0;
    
    // initializing 
    input_name = (char*)malloc(50);
    f_nowhere = fopen("/dev/null", "rw");
    f_tokens = f_nowhere;
    f_ast = f_nowhere;
    f_error = stderr;
    f_symtab = f_nowhere;
    f_tac = f_nowhere;
    f_asm = fopen("output/out.asm", "w");
}

void error(const char *msg, int status) {
    fprintf(f_error, "%s\n", msg);
    if(status)
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

operation_t get_op_type(operator_t op) {
    if(op == OP_PLUS || op == OP_MINUS || op == OP_MUL || op == OP_DIV)
        return OP_ARITHMETIC;
    return -1;        
}

char *itoa(int num) {
    if(num == 0)
        return "0";
    
    char *str = malloc(10);
    int i=0;
    if(num < 0) {
        num = -num;
        str[i++] = '-';
    }
    for(; i<10 && num; i++) {
        str[i] = (char)('0'+num%10);
        num /= 10;
    }
    reverse(str);
    return str;
}

void reverse(char *str) {
    int len = strlen(str);
    for(int i=0; i<len/2; i++) {
        char temp = str[i];
        str[i] = str[len-1-i];
        str[len-1-i] = temp;
    }
}

int get_size_of_type(type_t type) {
    switch(type)
    {
        case TYPE_INTEGER:
            return 4;
        case TYPE_BOOLEAN:
        case TYPE_CHARACTER:
            return 1;
        default:
            return -1;
    }
}

int align_up(int num, int factor) {
    int x = num/factor;
    if(num%factor == 0)
        return num;
    return (num/factor)*factor + factor;
}

int abs(int a) {
    return (a > 0) ? a : -a;
}

/* String functions */
char *dup_string(const char *str) {
    int len = strlen(str);
    char *new_str = (char*)malloc(len+1);
    strcpy(new_str, str);
    return new_str;
}

char *concat_string(const char *str1, const char *str2) {
    int len1, len2;
    len1 = strlen(str1);
    len2 = strlen(str2);
    char *str = (char*)malloc(len1+len2+1);
    strcpy(str, str1);
    strcpy(str+len1, str2);
    return str;
}

/* Helper functions to print ast */
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

char *get_op_name(operator_t op) {
    switch(op)
    {
        case OP_PLUS:
            return "PLUS";
        case OP_MINUS:
            return "MINUS";
        case OP_MUL:
            return "MULTIPLY";
        case OP_DIV:
            return "DIVIDE";
        default:
            return "UNKNOWN-OPERATOR";
    }
}

char *op_to_string(operation_t op) {
    if(op == OP_PLUS)
        return "+";
    if(op == OP_MINUS)
        return "-";
    if(op == OP_MUL)
        return "*";
    if(op == OP_DIV)
        return "/";
    return NULL;
}

char *btoa(bool val) {
    if(val == true)
        return "true";
    return "false";
}

int max(int a, int b) {
    return a > b ? a : b;
}

char *get_literal_value(value val, type_t type) {
    switch(type)
    {
        case TYPE_INTEGER:
            return itoa(val.i_val);
        case TYPE_CHARACTER:
            char *str = malloc(2);
            str[0] = val.c_val;
            str[1] = '\0';
            return str;
        case TYPE_BOOLEAN:
            return btoa(val.b_val);
        default:
            return "unknown type of expression";
            break;
    }
}

char *get_scope_name(scope_t scope) {
    switch(scope)
    {
        case SCOPE_GLOBAL:
            return "GLOBAL";
        case SCOPE_LOCAL:
            return "LOCAL";
        case SCOPE_PARAMETER:
            return "PARAMETER";
    }
    return "UNKNOWN SCOPE";
}

char *get_symbol_kind_name(symbol_t kind) {
    if(kind == SYM_VAR)
        return "VARIABLE";
    if(kind == SYM_PARAM)
        return "PARAMETER";
    if(kind == SYM_FUNC)
        return "FUNCTION";
    return "UNKNOWN TYPE";
}

const char *get_tac_stmt_name(tac_stmt_t kind) {
    switch(kind)
    {
        case TAC_PRINT_STMT:
            return "TAC_PRINT_STMT";
        case TAC_READ_STMT:
            return "TAC_READ_STMT";
        case TAC_RETURN_STMT:
            return "TAC_RETURN_STMT";
        case TAC_RETURN_VOID_STMT:
            return "TAC_RETURN_VOID_STMT";
        case TAC_ASSIGN_STMT:
            return "TAC_ASSIGN_STMT";
        case TAC_FUNC_CALL_STMT:
            return "TAC_FUNC_CALL_STMT";
        case TAC_COPY_STMT:
            return "TAC_COPY_STMT";
        case TAC_ARGUMENT_STMT:
            return "TAC_ARGUMENT_STMT";
        case TAC_PREPARE_STACK:
            return "TAC_PREPARE_STACK";
    };
    return "invalid-stmt";
}