#include "arguments.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "utils.h"

FILE *f_input, *f_tokens, *f_ast, *f_nowhere, *f_error;
char *input_name;
extern FILE *yyin;


void process_arguments(int argc, char **argv) {
    // No arguments case
    if(argc == 1) {
        printf("Usage: %s <input_file> [--show-tokens] [--show-ast]\n", argv[0]);
        exit(1);
    }

    // initializing 
    input_name = (char*)malloc(50);
    f_nowhere = fopen("/dev/null", "rw");
    f_tokens = f_nowhere;
    f_ast = f_nowhere;
    

    // processing the arguments
    int i=1; 
    while(i < argc) {
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
        // if(strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
        //     if(i+1 == argc) {
        //         error("Output filename not provided after '-o' flag", -1);
        //     }
        //     close(2);
        //     open(argv[i+1], O_WRONLY);
        //     i+=2;
        //     continue;
        // }
        
        input_name = strcpy(input_name, argv[i]);
        stdin = fopen(argv[i], "r");
        if(!stdin) {
            error("Unable to open input file", -1);
        }
        i++;
        
        // fprintf(stderr, "Invalid argument: %s\n", argv[i]);
        // exit(1);
    }

    
}
