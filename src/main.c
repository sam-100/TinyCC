#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

extern int yylex(void);
extern int yyparse(void);

int yywrap(void) {
    return 1;
}

void yyerror(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(-1);
}

int main(int argc, char **argv) {
    yyparse();
    return 0;
}