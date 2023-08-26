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


int symbol_exists(char* symbol_name, SymbolTable* current_table);

int get_instruction_type(instruction_word *keyWord);

int operand_list_to_ascii(char *operands, int *list, int numberLine);

int get_type_guidence(char *keyWord);

Symbol *insert_symbol(char* symbol_name, int value, char type);

void create_files (struct entry_symbols **head_entry, struct extern_symbols **head_extern, int create_entry_file, int create_extern_file);

void reverse_string(char *str);

void skip_whitespaces(FILE *file_ptr);

int check_line(FILE *file_ptr, int line_counter);

int check_word(char *word, int line_counter, int enable_error);

int check_directive(FILE *file_ptr, char *word, int line_counter, int enable_error);

int check_instruction(FILE *file_ptr, char *word, int line_counter, int enable_error);

int check_symbol(FILE *file_ptr, char *word, int line_counter, int enable_error);

int add_symbol(FILE *file_ptr, char *word, int line_counter, int enable_error);

int empty_line(FILE *file_ptr);

int end_of_file(FILE *file_ptr);

char get_word(FILE *file_ptr);

void print_64(unsigned int buffer_data[MAX_MEMORY_SIZE][1], unsigned int buffer_inst[MAX_MEMORY_SIZE][1], uint16_t binaryWord, int IC, int DC);


#endif 
