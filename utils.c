#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include "globals.h"
#include "table.h"



/*this function add the suffix .am to the original file name*/
char *filename_suffix(char *str1, char *str2)
{
	char *str = (char*)malloc(strlen(str1) + strlen(str2) + 1);
	strcpy(str, str1);
	strcat(str, str2);
	return str;
}

/*this function skip all the white spaces in the line*/
void skip_white_spaces(char currLine[]) {
    int len = strlen(currLine);
    int src = 0, dest = 0; /*use to track the beginning and end of the line*/

    while (src < len) { /*check all the chars in line*/
        if (!isspace(currLine[src])) {
            currLine[dest] = currLine[src];
            dest++;
        }
        src++;
    }

    currLine[dest] = '\0'; /*it is the end of the line*/
}


/*this function classified the type of the sentence*/
int type_of_sentence(char *currLine) {
	int label = 0; /*flag*/
	int i=0;

	if (currLine[i] == '\0' || currLine[i] == '\t' || currLine[i] == ' ') {
		return EMPTY_LINE;
	}
	while (currLine[i] != '\0') {
		if  (currLine[i] == ":")
			label = 1;
			i++;
	}
	i=0;

	while (currLine[i] == ' ' || currLine[i] == '\t'){
		i++;
	}	

	if (currLine[i] == '.') {
		return GUIDENCE_LINE;
	}
	if (currLine[i] == '\n') {
		return EMPTY_LINE;
	}
	if (currLine[i] == ';') {
		return NOTE_LINE;
	}
	return INSTRUCTION_LINE;
}

/*this function get the data from the line using tokens*/
void get_data_from_line(char *currLine, char *label, char *keyWord, char *operands, int numberLine) {
	int labelFlag = 0;
	char *token;

	strcpy(tempCurrLine, currLine);
	ctrcat(tempCurrLine, "\0");
	skip_white_spaces(tempCurrLine);

	token = strtok(temp_curr_line, " \t\n");

	while(token != NULL) {
		/*this is label*/
		if (strstr(token, ":")) {
			labelFlag = 1;
			strcpy(label, token);
		}
		/*this is key word*/
		if (strtr(token, ".") || search_opcode_name(token, opcodeTable)) {
			strcpy(keyWord, token);
		}
		/*this is operand*/
		if (labelFlag == 1) {
			strcpy(operands, token);
		}
		
		token = strtok(NULL, " \t\n"); /*get the next token*/
	}

}

/*this function search for the opcode name. using this to compare to token*/
bool search_opcode_name(char *token, struct opcodeInfo *opcodeTable) {
	for (int i = 0; i < sizeof(opcodeTable); i++) {
		if (strcmp(token, opcodeTable[i].name) == 0) {
			return true;
		}	
	}
	return false; /*if the opcode is not find*/
}


/*this function return the hexadecimal opcode code*/
int *get_opcode_code(char *opcodeName, struct opcodeInfo *opcodeTable) {
	for (int i = 0; i < sizeof(opcodeTable1); i++) {
		if (strcmp(opcodeName, opcodeTable[i].name) == 0) {
			return opcodeTable[i].code;
		}
		else {
			printf("error in the given opcode");
		}	
	}
	return -1; /*if the opcode is not find*/
}


/*The following function checks if the symbol already exists in the table.*/
int symbol_exists(char* symbol_name) {
    Symbol* current = symbol_table;
    while (current != NULL) {
        if (strcmp(current->name, symbol_name) == 0) {
            return 1;  /* true - symbol exists */
        }
        current = current->next;
    }
    return 0;  /* false - symbol doesn't exist */
}


/*this function determine the type of instruction based on the provided key_word (opcode name)*/
int get_instruction_type(char *keyWord, int *currOpcode) {
	int i=0;
	/*arrays of pointers to the strings of the key words*/
	const char *(keyWordArray1[]) = {"mov", "cmp", "add", "sub", "lea"}; /*the first group of the opcodes*/
	const char *(keyWordArray2[]) = {"not", "clr", "inc", "dec", "jmp", "bne", "red", "prn", "jsr"}; /*the second group of the opcodes*/
	const char *(keyWordArray3[]) = {"rts", "stop"}; /*the third group of the opcodes*/

	const char opcodeArray1[] = {mov, cmp, add, sub, lea};
	const char opcodeArray2[] = {not, clr, inc, dec, jmp, bne, red, prn, jsr};
	const char opcodeArray3[] = {rts, stop};

	int sizeOfKeyWordArray1 = 5;
	int sizeOfKeyWordArray2 = 9;
	int sizeOfKeyWordArray3 = 2;

	for (i=0; i<sizeOfKeyWordArray1; i++) {
		if (!strcmp(keyword, keyWordArray1[i]) {
			*currOpcode = opcodeArray1[i];
			return INSTRUCTION_GROUP_1;
		}
	}
	for (i=0; i<sizeOfKeyWordArray2; i++) {
		if (!strcmp(keyword, keyWordArray2[i]) {
			*currOpcode = opcodeArray2[i];
			return INSTRUCTION_GROUP_2;
		}
	}
	for (i=0; i<sizeOfKeyWordArray3; i++) {
		if (!strcmp(keyword, keyWordArray2[i]) {
			*currOpcode = opcodeArray3[i];
			return INSTRUCTION_GROUP_3;
		}
	}
	return 0; /*if the key word didnt found*/
}
