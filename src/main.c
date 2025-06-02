#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "arguments.h"
#include "print-ast.h"
#include "utils.h"

extern int yylex(void);
extern int yyparse(void);
program *root;

int yywrap(void) {
    return 1;
}

void yyerror(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(-1);
}

int main(int argc, char **argv) {
    initialize();
    process_arguments(argc, argv);
    yyparse();
    print_program(root);
    printf("Program parsed successfully!\n");
    return 0;
}