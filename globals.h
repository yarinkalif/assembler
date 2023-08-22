#include <stdio.h>
#include <stdlib.h>


#define MAX_LENGTH_LINE 81
#define MAX_OPCODES 16
#define MACHINE_CODE_LENGTH 12
#define MAX_MEMORY_SIZE 1024
#define MAX_LABEL_LENGTH 31
#define MAX_SYMBOL_LENGTH 31
#define NEXT_ADDRESS 1
#define SYMBOL_TYPE_DATA 'd'
#define IC 100
#define DC 0

/* Enum for error codes */
typedef enum {
    ERROR_FILE_READ,            
    ERROR_EMPTY_FILE ,           
    ERROR_EOF_REACHED,           
    ERROR_LINE_LENGTH, 
    ERROR_WORD_LENGTH, 
    ERROR_SYMBOL_LENGTH, 
    ERROR_INVALID_WORD, 
    ERROR_INVALID_SYMBOL, 
    ERROR_INVALID_OPERATION,     
    ERROR_WRONG_OPERAND_COUNT,   
    ERROR_INVALID_OPERAND_TYPE,  
    ERROR_REGISTER_NOT_FOUND,       
    ERROR_TOO_MANY_OPERANDS  
	ERROR_MEMORY_ALLOCATION   
} ErrorCode;

/*A function that handles errors while reading a line from a source file*/
void handle_error(int error_code, int line_counter) {
    printf("Line %d: ", line_counter);  /* Indicating which line caused the error*/
    switch (error_code) {
        case ERROR_FILE_READ:
            printf("Error - the source file is incorrect\n", line_counter);
            break;
        case ERROR_EMPTY_FILE:
            printf("Error - The file is empty\n", line_counter);
            break;
        case ERROR_EOF_REACHED:
            printf("Out of source file\n", line_counter);
            break;
        case ERROR_LINE_LENGTH:
            printf("Line is too long\n", line_counter);
            break;
        case ERROR_WORD_LENGTH:
            printf("Word is too long\n", line_counter);
            break;
        case ERROR_SYMBOL_LENGTH:
            printf("Symbol is too long\n", line_counter);
            break;
        case ERROR_INVALID_WORD:
            printf("Error - Invalid word\n", line_counter);  /* action that does not exist */
            break;
        case ERROR_INVALID_SYMBOL:
            printf("Error - Invalid symbol\n", line_counter);  /* action that does not exist */
            break;
        case ERROR_INVALID_OPERATION:
            printf("Error - Invalid operation\n", line_counter);  /* action that does not exist */
            break;
        case ERROR_WRONG_OPERAND_COUNT:
            printf("Error - Incorrect number of operands\n", line_counter);  /* Incorrect number of operands */
            break;
        case ERROR_INVALID_OPERAND_TYPE:
            printf("Error - Operand type doesn't match the operation\n", line_counter);  /* An operand type that does not match the operation*/
            break;
        case ERROR_REGISTER_NOT_FOUND:
            printf("Error - register not found\n", line_counter);  /* Register name does not exist*/
            break;
        case ERROR_TOO_MANY_OPERANDS:
		printf("Error - Too many operands provided\n", line_counter);  /* Too many operands*/
            break;
	case ERROR_MEMORY_ALLOCATION:
		printf("Error - memory allocation failed\n", line_counter); /*memory allocation*/
    }
}

symbols;
symbols_entry;
symbols_extern;

/*hold opcode information*/
struct opcodeInfo {
	char *name;
	int *code;
};

/*table of the opcodes and their hexadecimal codes*/
struct opcodeInfo opcodeTable[MAX_OPCODES] = {
	{"mov", 0};
	{"cmp", 1};
	{"add", 2};
	{"sub", 3};
	{"lea", 6};
	{"not", 4};
	{"clr", 5};
	{"inc", 7};
	{"dec", 8};
	{"jmp", 9};
	{"bne", 10};
	{"red", 11};
	{"prn", 12};
	{"jsr", 13};
	{"rts", 14};
	{"stop", 15};
};

typedef struct data_image *data_image_ptr;

typedef struct data_image {
	long address;
	char src_code[MAX_LENGTH_LINE];
	char machine_code[MACHINE_CODE_LENGTH];
	data_image_ptr next;
} data_image;

typedef enum instruction_type {
	INSTRUCTION_GROUP_1 = 1,
	INSTRUCTION_GROUP_2,
	INSTRUCTION_GROUP_3
} instruction_type;

enum size_byte{
	WORD = 12
};

typedef enum {
    REGISTER,
    LABEL,
    STRING,
    NUMBER
} OperandType;

typedef enum type_of_guidance{ 
  
	DATA = 1,
	STRING,
	ENTRY,
	EXTERN
}type_guide;

/*the bytes of word in instruction group 1 using bitfiels*/
typedef union instruction_1 {
	struct instruction_1_line {
		unsigned int ARE: 2
		unsigned int operandDst: 3
		unsigned int opcode: 4
		unsigned int operandSrc: 3
	} instruction;
	int size = 12;
} instructionGroup1;

/*the bytes of word in instruction group 2 using bitfiels*/
typedef union instruction_2 {
	struct instruction_2_line {
		unsigned int ARE: 2
		unsigned int operandDst: 0
		unsigned int opcode: 4
		unsigned int operandSrc: 3
	} instruction;
	int size = 12;
} instructionGroup2;

/*the bytes of word in instruction group 3 using bitfiels*/
typedef union instruction_3 {
	struct instruction_3_line {
		unsigned int str: 2
		unsigned int operandDst: 0
		unsigned int opcode: 4
		unsigned int operandSrc: 0
	} instruction;
	int size = 12;
} instructionGroup3;

typedef union guidanceData{
	struct guidance_word{
		unsigned int word: 12;	
	}guidance;
	int size: 12;
}DataCodE;
