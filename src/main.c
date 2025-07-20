#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "arguments.h"
#include "ast/program.h"
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

    // scanning parsing and ast creation
    yyparse();
    print_program(root);
    printf("Program parsed successfully!\n");
    
    // Symbol table construction
    construct_symtab_program(root);
    printf("Symbol table constructed.\n");

    // name resolution
    resolve_program(root);
    printf("Symbol table resolved.\n");

    
    // type checking
    typecheck_program(root);
    printf("Typechecking done.\n");
    
    // memory layout stage
    memory_layout_program(root);
    printf("Offsets set for parameters and local variables.\n");
    
    
    // generate three address code
    generate_tac_for_program(root);
    print_tac_of_program(root, f_tac);
    
    print_symtab_program(root);
    return 0;
}

int yywrap(void) {
    return 1;
}

void yyerror(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(-1);
}
