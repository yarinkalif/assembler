#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "globals.h"
#include "utils.h"


/*this function represent the line instruction in binary*/
void line_instruction_binary(char *machineCode, char *keyWord, char *operands, int numberLine) {
	int currOpcode = 0;
	instructionGroup1 currLine1;
	instructionGroup2 currLine2;
	instructionGroup3 currLine3;

	int typeOfKeyWord = get_instruction_type(keyWord, &currOpcode);

	switch (typeOfKeyWord) {
		case 1:
			currLine1 = create_instruction_1(keyWord, operands, currOpcode, typeOfKeyWord, numberLine);
			int_to_binary(machineCode, currLine1.size.WORD);
			break;

		case 2:
			currLine2 = creat_instruction_2(keyWord, operands, currOpcode, typeOfKeyWord, numberLine);
			int_to_binary(machineCode, currLine2.size.WORD);
			break;
		case 3:
			currLine2 = create_instruction_3(keyWord, currOpcode, typeOfKeyWord, numberLine);
			int_to_binary(machineCode, currLine3.size.WORD);
}





/*identify the operand type*/
OperandType identify_operand_type(char *operand) {
    if (operand[0] == '@' && operand[1] == 'r' && operand[2] >= '0' && operand[2] <= '7' && operand[3] == '\0') {
        return REGISTER;
    } else if (isdigit(operand[0]) || (operand[0] == '-' && isdigit(operand[1]))) {
        return NUMBER;
    } else if (operand[0] == '"' && operand[strlen(operand) - 1] == '"') {
        return STRING;
    } else {
        return LABEL;
    }
}

/*this function create the instruction of group 1 - the group with two operands*/
instructionGroup1 create_instruction_1(char *keyword, char *operands, int currOpcode, int typeOfKeyWord, int numberLine) {
	instructionGroup1 instr;
	instr->instruction.opcode = currOpcode;

	char *operand1 = strtok((char *)operands, ",");
	char *operand2 = strtok(NULL, ",");

	if (!operand1 || !operand2) {
		printf("error: missing operand\n");
		instr.size = 0;
		return instr;
	}
	/*idenify the operand types*/
	operandType operand_1_type = identify_operand_type(operand1);
	operandType operand_2_type = identify_operand_type(operand2);

	switch (operand_1_type) {
		case REGISTER:
			instr.instruction.operandSrc = operand1[2] - '0'; /*convert int to char*/
			break;
		case LABEL:
			break;
		case STRING:
			instr.instruction.operandSrc = operand1;
			break;
		case NUMBER:
			instr.instruction.operandSrc = operand1;
			break;
	}
	switch (operand_2_type) {
		case REGISTER:
			instr.instruction.operandDst = operand1[2] - '0'; /*convert int to char*/
			break;
		case LABEL:
			break;
		case STRING:
			instr.instruction.operandDst = operand1;
			break;
		case NUMBER:
			instr.instruction.operandDst = operand1;
			break;
	}
	instr.instruction.str = 0;
	return instr;
}	

/*this function create the instruction of group 2 - the group with two operands*/
instructionGroup2 create_instruction_2(char *keyword, char *operands, int currOpcode, int typeOfKeyWord, int numberLine) {
	instructionGroup1 instr;
	instr->instruction.opcode = currOpcode;

	if (operands == NULL) {
		printf("error: missing operand\n");
		return instr;
	}
	operandType operand_type = identify_operand_type(operands);

	switch (operandType) { /*the source operand is always 0*/
		case REGISTER:
			instr.instruction.operandSrc = 0;
			instr.instruction.operandDst = operand1[2] - '0'; /*convert int to char*/
		case LABEL:
			break;
	}	
	instr.instruction.str = 0;	
}

instructionGroup3 create_instruction_3(char *keyword, int currOpcode, int typeOfKeyWord, int numberLine) {
	instructionGroup1 instr;
	instr->instruction.opcode = currOpcode;
	instr.instruction.operandSrc = 0; /*the source operand is always 0*/
	instr.instruction.operandDst = 0; /*the destination operand is always 0*/
	instr.instruction.str = 0;
}



void line_guidence_binary(char *machineCode, char *keyWord, long dataList,int typeOfGuidence, int numberLine) {
	DataCode currData; 
	DataCode currStr;

	switch(typeOfGuidence)
		case DATA:
			if (list > ....) {
				printf("error\n");
			}
			currData.guidence.word = dataList;
			int_to_binary(machineCode, currData.size, WORD);
			break;
		case STRING:
			if (list > ....) {
				printf("error\n");
			}
			currStr.guidence.word = currStr;
			int_to_binary(machineCode, currStr.size, WORD);	
			break;
	} /*end of switch*/	
}




/*this function convert integer to binary represantation*/
void int_to_binary(char *machineCode, int curr, int numOfBit) {
	unsigned mask = 1;

	for (; mask; mask << 1) {
		if (numOfByte != 0) {
			char bit;
			bit = (mask & curr)? '1':'0'; /*Check if the current bit is 1 or 0*/
			strncat(machineCode, &bit, 1); /*Append the bit to the machineCode string*/
			numOfByte--; /*Decrease the number of remaining bytes*/
		}
	}
	strcat(machineCode, "\0"); /*Add the EOF marker to the end of the code*/
	strrev(machineCode); /*change the order of bits to match the actual binary representation*/
    }
}



