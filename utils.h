#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "table.h"
#include "globals.h"
#include "errors.h"

enum typeOfSentence {
	EMPTY_LINE = 0,
	NOTE_LINE,
	INSTRUCTION_LINE,
	GUIDANCE_LINE
};



char *filename_suffix(char *str1, char *str2);

void skip_white_spaces(char currLine[]);

int type_of_sentence(char *currLine);

char process_field(char* field, int IC);

void handle_guidence(char* field, char* operands);

void get_data_from_line(char *currLine, char *label, char *keyWord, char *operands, int numberLine);

/*bool search_opcode_name(char *token, struct opcodeInfo *opcodeTable1, struct opcodeInfo *opcodeTable2, struct opcodeInfo *opcodeTable3);*/

/*int get_opcode_code(char *opcodeName, struct opcodeInfo *opcodeTable);*/

int symbol_exists(char* symbol_name, SymbolTable* current_table);

/*int get_instruction_type(instruction_word *keyWord);*/

int operand_list_to_ascii(char *operands, int *list, int numberLine);

int get_type_guidence(char *keyWord);

void insert_symbol(char* symbol_name, int value, char type);

int is_symbol(char* field);

int is_alphanumeric(char* str);

/*void ensure_address_in_bounds(int address);

void memory_insert(int address, unsigned int value);

void ensure_data_in_bounds(int data);

void memory_insert_int(int address, int data);

void memory_insert_char(int address, char ch);*/

#endif 
