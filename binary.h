#ifndef BINARY_H
#define BINARY_H

#include <stdint.h>
#include "globals.h"
#include "utils.h"
#include "errors.h"

void line_instruction_binary(char *machineCode, char *keyWord, int listOfInstruction, int numberLine);

OperandType identify_operand_type(char *operand);

instruction_word create_instruction_1(char *operands, int currOpcode, int typeOfKeyWord, int numberLine);

instruction_word create_instruction_2(char *operands, int currOpcode, int typeOfKeyWord, int numberLine);

instruction_word create_instruction_3(char *operands, int currOpcode, int typeOfKeyWord, int numberLine) ;

void line_guidence_binary(char *machineCode, char *keyWord, long dataList, int typeOfGuidence, int numberLine);

void int_to_binary(char *machineCode, int curr, int numOfBit);

char *base64_encode(unsigned char *input, size_t inputLength);

char *encode_binary_word_to_base64(uint16_t binaryWord);

#endif
