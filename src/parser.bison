%{
extern int yylex(void);
extern int yyerror(const char *msg);
%}


%token INTEGER VOID FUNCTION RETURN                             // keyword
%token IDENTIFIER INTEGER_LITERAL
%token COLON SEMICOLON SINGLE_QUOTE DOUBLE_QUOTE COMMA DOT      // symbols
%token OPEN_BRACKET CLOSED_BRACKET OPEN_SQUARE_BRACKET CLOSED_SQUARE_BRACKET OPEN_CURLY_BRACKET CLOSED_CURLY_BRACKET    // brackets
%token PLUS MINUS MULTIPLY DIVIDE EQUALS GREATER_THAN LESS_THAN     // arithmetic operator


%%

start: ;

%%

