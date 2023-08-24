#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

/*A function that handles errors while reading a line from a source file*/
void handle_error(int error_code, int line_counter) {
    printf("Line %d: ", line_counter);  /* Indicating which line caused the error*/
    switch (error_code) {
        case ERROR_FILE_READ:
            printf("Error - the source file is incorrect %d\n", line_counter);
            break;
        case ERROR_EMPTY_FILE:
            printf("Error - The file is empty%d\n", line_counter);
            break;
        case ERROR_EOF_REACHED:
            printf("Out of source file%d\n", line_counter);
            break;
        case ERROR_LINE_LENGTH:
            printf("Line is too long%d\n", line_counter);
            break;
        case ERROR_WORD_LENGTH:
            printf("Word is too long%d\n", line_counter);
            break;
        case ERROR_SYMBOL_LENGTH:
            printf("Symbol is too long%d\n", line_counter);
            break;
        case ERROR_INVALID_WORD:
            printf("Error - Invalid word%d\n", line_counter);  /* action that does not exist */
            break;
        case ERROR_INVALID_SYMBOL:
            printf("Error - Invalid symbol%d\n", line_counter);  /* action that does not exist */
            break;
        case ERROR_INVALID_OPERATION:
            printf("Error - Invalid operation%d\n", line_counter);  /* action that does not exist */
            break;
        case ERROR_WRONG_OPERAND_COUNT:
            printf("Error - Incorrect number of operands%d\n", line_counter);  /* Incorrect number of operands */
            break;
        case ERROR_INVALID_OPERAND_TYPE:
            printf("Error - Operand type doesn't match the operation%d\n", line_counter);  /* An operand type that does not match the operation*/
            break;
        case ERROR_REGISTER_NOT_FOUND:
            printf("Error - register not found%d\n", line_counter);  /* Register name does not exist*/
            break;
        case ERROR_TOO_MANY_OPERANDS:
		printf("Error - Too many operands provided%d\n", line_counter);  /* Too many operands*/
            break;
	case ERROR_MEMORY_ALLOCATION:
		printf("Error - memory allocation failed%d\n", line_counter); /*memory allocation*/
	case LABEL_EXIST:
		printf("Error - label already exist%d\n", line_counter); /*label exist*/
    }
}
