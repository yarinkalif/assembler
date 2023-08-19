#include <stdio.h>
#include <stdlib.h>


#define MAX_LENGTH_LINE 10000
#define MAX_OPCODES 16
#define MACHINE_CODE_LENGTH 30
#define MAX_MEMORY_SIZE 924

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
	INSTRUCTION_GROUP_1,
	INSTRUCTION_GROUP_2,
	INSTRUCTION_GROUP_3
} instruction_type;

enum size_byte{
	WORD = 12
};

/*the bytes of word in instruction group 1*/
typedef union instruction_1 {
	struct instruction_1_line {
		unsigned int operandDst: 3
		unsigned int opcode: 4
		unsigned int operandsrc: 3
		unsigned int str: 2
	} instruction;
	int size = 12;
} instructionGroup1;

/*the bytes of word in instruction group 2*/
typedef union instruction_2 {
	struct instruction_2_line {
		unsigned int operandDst: 0
		unsigned int opcode: 4
		unsigned int operandsrc: 3
		unsigned int str: 2
	} instruction;
	int size = 12;
} instructionGroup2;

/*the bytes of word in instruction group 3*/
typedef union instruction_3 {
	struct instruction_3_line {
		unsigned int operandDst: 0
		unsigned int opcode: 4
		unsigned int operandsrc: 0
		unsigned int str: 2
	} instruction;
	int size = 12;
} instructionGroup2;
