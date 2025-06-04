#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "arguments.h"
#include "program.h"
#include "utils.h"
#include "declarations.h"


extern int yylex(void);
extern int yyparse(void);
program *root;



int yywrap(void);
void yyerror(const char *msg);


int main(int argc, char **argv) {
    initialize();
    process_arguments(argc, argv);
    yyparse();
    print_program(root);
    printf("Program parsed successfully!\n");
    
    // name resolution
    program_resolve(root);

    // print symbol tables
    program_print_symtab(root);

    // type checking
    // program_typecheck(root);


    return 0;
}

int yywrap(void) {
    return 1;
}

void yyerror(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(-1);
}
