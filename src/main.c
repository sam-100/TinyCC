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
#include "phases/middleend/return_check.h"
#include "phases/backend/code_gen.h"


extern int yylex(void);
extern int yyparse(void);
program *root;

extern char *input_name, *output_dir, *output_filename;

int yywrap(void);
void yyerror(const char *msg);

enum stop_after_t stop_after = STOP_NEVER;

int main(int argc, char **argv) {
    initialize();
    process_arguments(argc, argv);

    // scanning parsing and ast creation
    yyparse();
    printf("Program parsed successfully!\n");
    fflush(f_tokens);

    if(stop_after == STOP_AFTER_PARSING) {
        print_program(root);
        fflush(f_ast);
        return 0;
    }

    // Symbol table construction
    construct_symtab_program(root);
    printf("Symbol table constructed.\n");
    print_symtab_program(root);
    fflush(f_symtab);

    if(stop_after == STOP_AFTER_SYMTAB) {
        print_symtab_program(root);
        fflush(f_symtab);
        return 0;
    }
    
    // name resolution
    resolve_program(root);
    printf("Symbol table resolved.\n");
    
    if(stop_after == STOP_AFTER_NAME_RESOLUTION) {
        print_symtab_program(root);
        fflush(f_symtab);
        return 0;
    }
    
    // return checking
    if(!return_check_program(root))
        error("Error: return-check error.", 1);
    printf("return check done.\n");

    // type checking
    typecheck_program(root);
    printf("Typechecking done.\n");

    if(stop_after == STOP_AFTER_TYPECHECK) {
        print_symtab_program(root);
        fflush(f_symtab);
        return 0;
    }

    // print the ast now
    print_program(root);
    fflush(f_ast);
    
    // memory layout stage
    memory_layout_program(root);
    printf("Offsets set for parameters and local variables.\n");

    // construct_symtab_program(root);
    // printf("Symbol table constructed.\n");
    // print_symtab_program(root);


    // resolve_program(root);
    // printf("Name resolution of program done.\n");
    
    // generate three address code
    generate_tac_for_program(root);
    printf("Three address code generated successfully!\n");
    print_tac_of_program(root, f_tac);

    if(stop_after == STOP_AFTER_TAC_GEN) {
        print_tac_of_program(root, f_tac);
        fflush(f_tac);
        return 0;
    }
    
    // generate assembly code
    codegen_program(root, f_asm);
    printf("Assembly code generated successfully!\n");

    if(stop_after == STOP_AFTER_CODEGEN) {
        fflush(f_asm);
        return 0;
    }

    // assemble, link, and generate executable  
    char *assemble_command, *link_command;
    assemble_command = (char*)malloc(512);
    link_command = (char*)malloc(512);
    snprintf(assemble_command, 512,
        "nasm -f elf64 -o %s/out.o %s/out.asm", output_dir, output_dir
    );
    snprintf(link_command, 512,
        "ld %s/out.o bin/print_int.o bin/read_int.o bin/integer_to_string.o bin/string_to_integer.o -o %s/%s.out", output_dir, output_dir, output_filename
    );

    system(assemble_command);
    system(link_command);
    printf("Executable generated successfully!\n");
    
    // cleanup();
    return 0;
}

// void cleanup() {
//     // todo: 
// }

int yywrap(void) {
    return 1;
}

void yyerror(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(-1);
}
