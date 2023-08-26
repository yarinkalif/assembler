#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include "globals.h"
#include "utils.h"
#include "binary.h"


/*this function represent the line instruction in binary*/
void line_instruction_binary(char *machineCode, char *keyWord, int listOfInstruction, int numberLine) {
	int currOpcode = 0;
	instruction_word currLine1;
	instruction_word currLine2;
	instruction_word currLine3;

	int typeOfKeyWord = get_instruction_type(keyWord, &currOpcode);

	switch (typeOfKeyWord) {
		case INSTRUCTION_GROUP_1:
			currLine1 = create_instruction_1(keyWord, currOpcode, typeOfKeyWord, numberLine);
			int_to_binary(machineCode, currLine1.size, WORD);
			break;

		case INSTRUCTION_GROUP_2:
			currLine2 = create_instruction_2(keyWord, currOpcode, typeOfKeyWord, numberLine);
			int_to_binary(machineCode, currLine2.size, WORD);
			break;
		case INSTRUCTION_GROUP_3:
			currLine3 = create_instruction_3(keyWord, currOpcode, typeOfKeyWord, numberLine);
			int_to_binary(machineCode, currLine3.size, WORD);
			break;
	}
}



/*identify the operand type*/
OperandType identify_operand_type(char *operand) {
    if (operand[0] == '@' && operand[1] == 'r' && operand[2] >= '0' && operand[2] <= '7' && operand[3] == '\0') {
        return OPERAND_REGISTER;
    } else if (isdigit(operand[0]) || (operand[0] == '-' && isdigit(operand[1]))) {
        return OPERAND_NUMBER;
    } else if (operand[0] == '"' && operand[strlen(operand) - 1] == '"') {
        return OPERAND_STRING;
    } else {
        return OPERAND_LABEL;
    }
}

/*this function create the instruction of group 1 - the group with two operands*/
instruction_word create_instruction_1(char *operands, int currOpcode, int typeOfKeyWord, int numberLine) {
	instruction_word instr;
	instr.instruction_line.opcode = currOpcode;

	char *operand1 = strtok((char *)operands, ",");
	char *operand2 = strtok(NULL, ",");

	if (!operand1 || !operand2) {
		printf("error: missing operand\n");
		instr.size = 0;
		return instr;
	}
	/*idenify the operand types*/
	OperandType operand_1_type = identify_operand_type(operand1);
	OperandType operand_2_type = identify_operand_type(operand2);

	switch (operand_1_type) {
		case OPERAND_REGISTER:
			instr.instruction_line.operandSrc = operand1[2] - '0'; /*convert int to char*/
			break;
		case OPERAND_LABEL:
			break;
		case OPERAND_STRING:
			instr.instruction_line.operandSrc = operand1;
			break;
		case OPERAND_NUMBER:
			instr.instruction_line.operandSrc = operand1;
			break;
	}
	switch (operand_2_type) {
		case OPERAND_REGISTER:
			instr.instruction_line.operandDst = operand1[2] - '0'; /*convert int to char*/
			break;
		case OPERAND_LABEL:
			break;
		case OPERAND_STRING:
			instr.instruction_line.operandDst = operand1;
			break;
		case OPERAND_NUMBER:
			instr.instruction_line.operandDst = operand1;
			break;
	}
	instr.instruction_line.ARE = 0;
	return instr;
}	

/*this function create the instruction of group 2 - the group with two operands*/
instruction_word create_instruction_2(char *operands, int currOpcode, int typeOfKeyWord, int numberLine) {
	instruction_word instr;
	instr.instruction_line.opcode = currOpcode;

	if (operands == NULL) {
		printf("error: missing operand\n");
		return instr;
	}
	OperandType operand_type = identify_operand_type(operands);

	switch (operand_type) { /*the source operand is always 0*/
		case OPERAND_REGISTER:
			instr.instruction_line.operandSrc = 0;
			instr.instruction_line.operandDst = operands[2] - '0'; /*convert int to char*/
			break;
		case OPERAND_LABEL:
			break;
	}	
	instr.instruction_line.ARE = 0;	
	return instr;
}

instruction_word create_instruction_3(char *operands, int currOpcode, int typeOfKeyWord, int numberLine) {
	instruction_word instr;
	instr.instruction_line.opcode = currOpcode;
	instr.instruction_line.operandSrc = 0; /*the source operand is always 0*/
	instr.instruction_line.operandDst = 0; /*the destination operand is always 0*/
	instr.instruction_line.ARE = 0;

	return instr;
}



void line_guidence_binary(char *machineCode, char *keyWord, long dataList, int typeOfGuidence, int numberLine) {
	DataCode currData; 
	DataCode currStr;
	char currChar;

	switch(typeOfGuidence) {
		case DATA:
			currData.guidance.word = dataList;
			int_to_binary(machineCode, currData.size, WORD);
			break;
		case STRING:
			currStr.guidance.word = currChar;
			int_to_binary(machineCode, currStr.size, WORD);	
			break;
	} /*end of switch*/	
}




/*this function convert integer to binary represantation*/
void int_to_binary(char *machineCode, int curr, int numOfBit) {
	unsigned mask = 1;

	for (; mask; mask << 1) {
		if (numOfBit != 0) {
			char bit;
			bit = (mask & curr)? '1':'0'; /*Check if the current bit is 1 or 0*/
			strncat(machineCode, &bit, 1); /*Append the bit to the machineCode string*/
			numOfBit--; /*Decrease the number of remaining bytes*/
		}
	}
	strcat(machineCode, "\0"); /*Add the EOF marker to the end of the code*/
	strrev(machineCode); /*change the order of bits to match the actual binary representation*/
}

static char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


char *base64_encode(unsigned char *input, size_t inputLength) {
	size_t outputLength = 4*((inputLength+2)/3);
	char* encodedData = (char*)malloc(outputLength + 1);
	if (encodedData == NULL) {
		return NULL;
	}	
	size_t i, j=0;
	for (i = 0; i < inputLength; i += 3) {
		uint32_t value = 0;
		int count = 0;
		for (j = 0; j < 3; j++) {
			value <<= 8;
			if (i + j < inputLength) {
				value |= input[i + j];
				count++;
			}
		}

		for (j=0; j<4; j++) {
			encodedData[i*4/3+j] = count > j ? base64_chars[(value >> (6*(3-j))) & 0x3F] : '=';
		}
	}

	encodedData[outputLength] = '\0';
	return encodedData;
}

char *encode_binary_word_to_base64(uint16_t binaryWord) {
	/*convert the 12-bit binary word to 2 bytes*/
	unsigned char bytes[2];
	bytes[0] = (binaryWord >> 4) & 0xFF;
	bytes[1] = ((binaryWord & 0xF) << 4) & 0xF0;
	char *encoded = base64_encode(bytes, 2);

	free(encoded);
	return encoded;
}



