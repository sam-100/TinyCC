#ifndef TAC_ENUMS
#define TAC_ENUMS

typedef enum {
    TAC_OP_VARIABLE, 
    TAC_OP_TEMP, 
    TAC_OP_LITERAL_INT, 
    TAC_OP_LITERAL_BOOL, 
    TAC_OP_LITERAL_CHAR, 
    TAC_OP_FUNC_CALL, 
} tac_operand_t;

typedef enum {
    TAC_PRINT_STMT, 
    TAC_READ_STMT, 
    TAC_RETURN_STMT, 
    TAC_RETURN_VOID_STMT, 
    TAC_ASSIGN_STMT, 
    TAC_FUNC_CALL_STMT, 
    TAC_COPY_STMT, 
    TAC_ARGUMENT_STMT, 
} tac_stmt_t;

#endif