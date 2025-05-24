#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

extern int yylex(void);

int yywrap(void) {
    return 1;
}

// void yyerror(const char *msg) {
//     fprintf(stderr, msg);
//     exit(-1);
// }

int main(int argc, char **argv) {
    while(yylex());
    printf("Program scanned successfully!\n");
    return 0;
}