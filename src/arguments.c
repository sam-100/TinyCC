#include "arguments.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "utils.h"

FILE *f_input, *f_tokens, *f_ast, *f_nowhere, *f_error, *f_symtab, *f_tac, *f_asm;
char *input_name = NULL;
extern FILE *yyin;


void process_arguments(int argc, char **argv) {
    // No arguments case
    if(argc < 2) {
        printf("Usage: %s <input_file> [--show-tokens] [--show-ast] [--show-symtab] [--show-tac]\n", argv[0]);
        exit(1);
    }


    // processing the arguments
    int i=1; 
    while(i < argc) {
    // for(int i=1; i<argc; i++)
        if(strcmp(argv[i], "--show-tokens") == 0) {
            f_tokens = fopen("output/tokens.txt", "w");
            i++;
            continue;
        }
        if(strcmp(argv[i], "--show-ast") == 0) {
            f_ast = fopen("output/ast.txt", "w");
            i++;
            continue;
        }
        if(strcmp(argv[i], "--show-symtab") == 0) {
            f_symtab = fopen("output/symtab.txt", "w");
            i++;
            continue;
        }
        if(strcmp(argv[i], "--show-tac") == 0) {
            f_tac = fopen("output/tac.txt", "w");
            i++;
            continue;
        }
        
        // if(input_name != NULL) {
        //     error("Error: multiple input files provided as input.", -1);
        // }
        input_name = strcpy(input_name, argv[i]);
        stdin = fopen(argv[i], "r");
        if(!stdin) {
            error("Error: Unable to open input file", -1);
        }
        i++;
    }
}
