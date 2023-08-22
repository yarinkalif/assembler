#ifndef BINARY_H
#define BINARY_H

void line_instruction_binary(char *machineCode, char *keyWord, char *operands, int numberLine)

OperandType identify_operand_type(char *operand);

instructionGroup1 create_instruction_1(char *keyword, char *operands, int currOpcode, int typeOfKeyWord, int numberLine);

instructionGroup2 create_instruction_2(char *keyword, char *operands, int currOpcode, int typeOfKeyWord, int numberLine);

instructionGroup3 create_instruction_3(char *keyword, int currOpcode, int typeOfKeyWord, int numberLine);

void line_guidence_binary(char *machineCode, char *keyWord, long dataList,int typeOfGuidence, int numberLine);

void int_to_binary(char *machineCode, int curr, int numOfBit);

char *base64_encode(unsigned char *input, size_t inputLength);

char *encode_binary_word_to_base64(uint16_t binaryWord);
