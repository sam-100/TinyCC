#ifndef TAC_ENUMS
#define TAC_ENUMS

typedef enum {
    TAC_VARIABLE, 
    TAC_TEMP, 
    TAC_LITERAL_INT, 
    TAC_LITERAL_BOOL, 
    TAC_LITERAL_CHAR, 
    TAC_ARGUMENT, 
    TAC_FUNC_CALL, 
} tac_operand_t;

typedef enum {
    TAC_PRINT_STMT, 
    TAC_READ_STMT, 
    TAC_RETURN_STMT, 
    TAC_ASSIGN_STMT, 
    TAC_FUNC_CALL, 
} tac_stmt_t;

#endif