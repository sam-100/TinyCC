#include "arguments.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "utils.h"

FILE *f_input, *f_tokens, *f_ast, *f_nowhere, *f_error, *f_symtab, *f_tac, *f_asm;
char *input_name = NULL;
char *output_dir = NULL;
char *output_filename = NULL;
extern FILE *yyin;

extern enum stop_after_t stop_after;

void process_arguments(int argc, char **argv) {
    // No arguments case
    if(argc < 2) {
        printf("Usage: \n");
        printf("\t %s <input_file> \n", argv[0]);
        printf("\t\t[--show-tokens] \n");
        printf("\t\t[--show-ast] \n");
        printf("\t\t[--show-symtab] \n");
        printf("\t\t[--show-tac] \n");
        printf("\t\t[--sa-parse] \n");
        printf("\t\t[--sa-symtab] \n");
        printf("\t\t[--sa-name-res] \n");
        printf("\t\t[--sa-typecheck] \n");
        printf("\t\t[--sa-tac-gen] \n");
        printf("\t\t[--sa-codegen] \n");
        printf("\t\t[--outdir=<output-directory-name>]\n");
        printf("\t\t[--outfile=<output-filename-without-extension>]\n");
        printf("Example: %s --show-tokens --sa-parse --outdir=output input.tinyc\n", argv[0]);
        exit(1);
    }


    // Here we go through all arguments
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "--show-tokens") == 0) {
            f_tokens = fopen("output/tokens.txt", "w");
        } else if(strcmp(argv[i], "--show-ast") == 0) {
            f_ast = fopen("output/ast.txt", "w");
        } else if(strcmp(argv[i], "--show-symtab") == 0) {
            f_symtab = fopen("output/symtab.txt", "w");
        } else if(strcmp(argv[i], "--show-tac") == 0) {
            f_tac = fopen("output/tac.txt", "w");
        } else if(strcmp(argv[i], "--sa-parse") == 0) {
            stop_after = STOP_AFTER_PARSING;
        } else if(strcmp(argv[i], "--sa-symtab") == 0) {
            stop_after = STOP_AFTER_SYMTAB;
        } else if(strcmp(argv[i], "--sa-name-res") == 0) {
            stop_after = STOP_AFTER_NAME_RESOLUTION;
        } else if(strcmp(argv[i], "--sa-typecheck") == 0) {
            stop_after = STOP_AFTER_TYPECHECK;
        } else if(strcmp(argv[i], "--sa-tac-gen") == 0) {
            stop_after = STOP_AFTER_TAC_GEN;
        } else if(strcmp(argv[i], "--sa-codegen") == 0) {
            stop_after = STOP_AFTER_CODEGEN;
        } else if(strncmp(argv[i], "--outdir=", 9) == 0) {
            char *outdir = argv[i] + 9;
            // Create output directory if it doesn't exist
            char cmd[256];
            snprintf(cmd, sizeof(cmd), "mkdir -p %s", outdir);
            system(cmd);
            // Set output file paths
            char path[256];
            snprintf(path, sizeof(path), "%s/tokens.txt", outdir);
            f_tokens = fopen(path, "w");
            snprintf(path, sizeof(path), "%s/ast.txt", outdir);
            f_ast = fopen(path, "w");
            snprintf(path, sizeof(path), "%s/symtab.txt", outdir);
            f_symtab = fopen(path, "w");
            snprintf(path, sizeof(path), "%s/tac.txt", outdir);
            f_tac = fopen(path, "w");
            snprintf(path, sizeof(path), "%s/out.asm", outdir);
            f_asm = fopen(path, "w");
        } else if (strncmp(argv[i], "--outfile=", 10) == 0) {
            output_filename = argv[i] + 10; 
            printf("Output filename set to %s\n", output_filename);
            fflush(stdout);
        } else {
            // Assume this is the input file
            if(input_name == NULL) {
                input_name = argv[i];
                f_input = fopen(input_name, "r");
                if(f_input == NULL) {
                    perror("Error opening input file");
                    exit(1);
                }
                yyin = f_input;
            } else {
                printf("Multiple input files specified. Please provide only one input file.\n");
                exit(1);
            }
        }
    }

    // Set default files if not opened
    if(output_dir == NULL) {
        // create a directory named output
        // system("mkdir -p output");
        output_dir = ".";
    }

    if(output_filename == NULL) {
        output_filename = "a";
    }

    if(f_asm == f_nowhere) {
        char path[256];
        snprintf(path, sizeof(path), "%s/out.asm", output_dir);
        f_asm = fopen(path, "w");
    }


}
