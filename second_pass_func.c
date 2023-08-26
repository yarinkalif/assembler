#include "globals.h"
#include "utils.h"
#include "globals.h"
#include "binary.h"
#include "table.h"

/* Skips whitespaces
   gets source file pointer and skips spaces and tabs in the current line in the file */                                                     
void skip_whitespaces (FILE *file_ptr) {

	char current_character = fgetc(file_ptr); /* current character in the line */

	while (current_character != EOF && current_character != '\n' && (current_character == ' ' || current_character == '\t')) {
		fseek(file_ptr ,-1 ,SEEK_CUR);
		current_character = fgetc(file_ptr);
	}
}

/* Skips whitespaces
   gets source file pointer and skips spaces and tabs in the current line in the file */     
int check_line (FILE *file_ptr, int line_counter) {

	char current_character = fgetc(file_ptr); /* current character in the line */
	int character_counter = 0;
	int word_length_counter = 0;
	int big_word = 0;

	while (current_character != EOF && current_character != '\0' && current_character != '\n') {

		if (current_character != ' ' && current_character != '\t') {
			word_length_counter++;
			character_counter++;
			current_character = fgetc(file_ptr); /* current character in the line */
		}

		if (word_length_counter > MAX_LENGTH_LINE) {
			big_word = 1;
		}

		else {
			word_length_counter = 0;			
			character_counter++;
			current_character = fgetc(file_ptr); /* current character in the line */
	}	}
	
	if (big_word == 1) {
		handle_error(ERROR_WORD_LENGTH, line_counter);
	}

	else if (character_counter > MAX_LENGTH_LINE) {
		handle_error(ERROR_LINE_LENGTH, line_counter);
	}

	return character_counter;
}

/* Skips whitespaces
   gets source file pointer and skips spaces and tabs in the current line in the file */ 
int check_word (char *word, int line_counter, int enable_error) {
	
	int i=0;
	char *directive[MAX_LENGTH_LINE];
	char opcodeTable[MAX_OPCODES];
	char symbols[MAX_SYMBOL_LENGTH];

	for (i = 0; i <= 15; i++) {
	
		if (i <= 3) {

			if (strcmp(word, directive[i]) == 0) {
				return 1;
			}
		}

		if (strcmp(word, opcodeTable[i]) == 0) {
			return 2;
		}

		if (strcmp(word, symbols[i]) == 0) {
			return 3;
		}
	}

	if (enable_error == 1) {
		handle_error(ERROR_INVALID_WORD, line_counter);
	}
	
	return 0;
}


/* Returns if the line is empty
   gets source file pointer and skips spaces and tabs in the current line in the file
   if reached to '\n' returns 1 and if not returns 0 */
int empty_line (FILE *file_ptr) {

	char current_character = fgetc(file_ptr); /* current character in the line */
	skip_whitespaces(file_ptr);

	if (current_character == '\n') {
		return 1;
	}

	return 0;
}

/* Returns if reached to end of file
   gets source file pointer and skips spaces and tabs in the current line in the file
   if reached to end of file returns 1 and if not returns 0 */
int end_of_file (FILE *file_ptr) {

	char current_character = fgetc(file_ptr); /* current character in the line */

	skip_whitespaces(file_ptr);

	if (current_character == EOF) {
		return 1;
	}

	return 0;
}

/* Returns if reached to end of file
   gets source file pointer and skips spaces and tabs in the current line in the file
   if reached to end of file returns 1 and if not returns 0 */
char get_word (FILE *file_ptr) {
	
	char current_character = fgetc(file_ptr); /* current character in the line */
	char *word = (char*)malloc(MAX_LENGTH_LINE * sizeof(char));
	int i = 0;

	while (current_character != EOF && current_character != '\0' && current_character != '\t' && current_character != ' ' && current_character != '\n') {

		word[i] = current_character;
        	i++;
		fseek(file_ptr ,-1 ,SEEK_CUR);
		current_character = fgetc(file_ptr);
	}

	word[i] = '\0';
	free(word);
	return word;
}


void print_64 (FILE *filename, unsigned int listOfData[MAX_LENGTH_LINE], unsigned int listOfInstruction[MAX_LENGTH_LINE], uint16_t binaryWord, int IC, int DC) {

	int i = 0;
	FILE *file_ptr;

	if (IC == 0 && DC == 0) {
		printf ("Error in creating output 64 file: failed to open a file for 64 base\n");
		return;
	}

	file_ptr = fopen(filename, "w");

	if (file_ptr == NULL)
	{
		printf ("Can't open a file for 64 base output\n");
		return;
	}


	while (i <= IC) {
		if (listOfInstruction[i] != 3) {
			printf("%s ", encode_binary_word_to_base64(binaryWord));
		}
	}

	i = 0;

	while (i <= DC) {
		if (listOfInstruction[i] == 3) {
			printf("%s ", encode_binary_word_to_base64(binaryWord));
		}
	}

	rewind (file_ptr);
	fprintf (file_ptr, "%d ", IC);
	fprintf (file_ptr, "%d", DC);
	fclose (file_ptr);
}
