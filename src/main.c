#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "declarations.h"
#include "arguments.h"
#include "utils.h"

#include "ast/program.h"
#include "ast/print.h"

#include "symbol_table/print.h"

#include "tac/print.h"

#include "phases/frontend/construct_symtab.h"
#include "phases/frontend/resolve_name.h"
#include "phases/frontend/typecheck.h"
#include "phases/middleend/generate_tac.h"
#include "phases/middleend/memory_layout.h"

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
    printf("Three address code generated successfully!\n");
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
