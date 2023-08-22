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


/*The function receives a string and decides what type the field is - whether it is a symbol, a prompt or something else.
 It performs operations based on the type and returns a character that represents the type of the field*/
char process_field(char* field) {
    if (is_symbol(field)) {
        insert_symbol(field, IC, 'c');
        return 's';  /* symbol*/
    } else if (strcmp(field, ".data") == 0 || strcmp(field, ".string") == 0) {
        return 'd';  /* data_instruction*/
    } else if (strcmp(field, ".extern") == 0 || strcmp(field, ".entry") == 0) {
        return 'e';  /* external_entry_instruction */
    } else {
        return 'u';  /* unknown*/
    }
}


/*As we mentioned above, we used the algorithm in the course booklet.
 The following function provides an answer to the ninth step and checks whether it is an .extern directive*/
void handle_guidence(char* field, char* operands) {
    char guidence_type = process_field(field);

    /* If the directive is ".extern" */
    if (guidence_type == 'e') {
        char* token = strtok(operands, " \t,");
        while (token != NULL) {
            /* Add the symbol to the symbol table */
            insert_symbol(token, 0, 'E');
            token = strtok(NULL, " \t,");
        }
    }
    /*TODO: Additional checks for other types of instructions can be added here if needed*/
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



/*this function represent the operands in ascii*/
int operand_list_to_ascii(char *operands, int *list, int numberLine) {
	int i=0;
	int strFlag = 0; /*there is string as operand*/
	int commaFlag = 0;
	int minusFlag = 0;
	int operandCount = 0;

	for (i=0; i<strlen(operands); i++) {
		skip_white_spaces(operands);
		if (operands[i] = '"') /*check if there is string*/
			strFlag = 1;
			i++;
		}
		break;
	} /*end for loop*/
	if (strFlag == 1) { /*if it's .string*/
		for (; i<strlen(operands); i++) {
			if (operands[i] == '"') {
				strFlag = 0;
				break;
			}
			list[operandCount++] = operand[i];
			skip_white_spaces(operands);
		}
		if (strFlag == 1) {
			print("error: syntax\n");
		}
	} /*.data*/
	else if (operands[i] >= '0' && operands[i] <= '9')) { /*check if the current character is a digit*/
		for (;i<strlen(operands);) {
			skip_white_spaces(operands);
			if (operands[i] == ',') {
				if (commaFlag == 0) { /*if there isn't ,*/
					printf("error: syntax\n");
				}
				commaFlag = 0;
				i++;
			}
			else if (commaFlag == 0) {
				while (operands[i]== '-' || operands[i] >= '0' && operands[i] ,= '9')) {
					if (operands[i] == '-') {
						minusFlag = 1; /*negative number*/
					}
					else { /*two digit number*/
						tempNum = (tempNum * 10) + (operands[i] = '0'); /*to get the ascii value*/
						i++;
					}
				}
				commaFlag = 1;
				if (minusFlag == 1) { /*update the negative num*/
					tempNum = (-1) * tempNum;
				}
				list[operandCount] = tempNum; /*add the number to the list*/
				tempNum = 0;
				skip_white_spaces(operands);
			}
		} /*end for loop*/
	}
	else { /*.entry .extern*/
		list[operndCounter] = operands[i];
	}
	return operandCounter;
}

/*this function gets the filed word and decide */
int get_type_guidence(char *field) {
	int i=0;
	int numOfTypes = 4;
	const char *(guidenceType[]) = {".data", ".string", "entry", "extern"};
	
	for (i=0; i<numOfTypes; i++) {
		if (strcmp(keyWord, guidenceType) == 0) {
			return i+1; /*the int that match the word type*/
		}
	}
	return 0;
}



/*The function takes a symbol name, a numeric value, and a type. It adds the symbol to the global symbol table within the program.
 If the symbol already exists in the table, the program may return an error (if you were to run the method one after the other on the same symbol name).*/
void insert_symbol(char* symbol_name, int value, char type) {
    for (int i = 0; i < symbol_table.count; i++) {
        if (strcmp(symbol_table.symbols[i].name, symbol_name) == 0) {
            printf("Error: Symbol %s already exists!\n", symbol_name);
            exit(1);
        }
    }

    strcpy(symbol_table.symbols[symbol_table.count].name, symbol_name);
    symbol_table.symbols[symbol_table.count].value = value;
    symbol_table.symbols[symbol_table.count].type = type;
    symbol_table.count++;
}


/*The function checks whether the string passed to it is a symbol. It returns 1 (true) if the string is a symbol, and 0 (false) otherwise.*/
int is_symbol(char* field) {
    return ((field[0] >= 'A' && field[0] <= 'Z') || (field[0] >= 'a' && field[0] <= 'z')) && is_alphanumeric(field);
}

/*The function checks whether all the characters in the string passed to it are alphanumeric (letters or numbers).
 It returns 1 (true) if all characters are alphanumeric, and 0 (false) otherwise.*/
int is_alphanumeric(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9'))) {
            return 0;
        }
    }
    return 1;
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


/*The following function creates a limit on the address in memory*/
void ensure_address_in_bounds(int address) {
    if (address < 0 || address >= MEMORY_SIZE) {
        handle_error("Address out of bounds");
    }
}


/*The following function takes care of putting data into memory*/
void memory_insert(int address, unsigned int value) {
    ensure_address_in_bounds(address);
    
	/*Check that the value is not too big for memory*/	
    if (value >= (1 << WORD_SIZE)) {
        handle_error("Value too large for memory word");
    }
    memory[address] = value;
}

/*The following function delimits the size of the data that goes into memory*/
void ensure_data_in_bounds(int data) {
    if (data < -(1 << (WORD_SIZE - 1)) || data >= (1 << (WORD_SIZE - 1))) {
        handle_error("Data out of bounds for word size");
    }
}

/*The following function is a function for inserting a whole data (even a third) into memory using the 2's complement method*/
void memory_insert_int(int address, int data) {
    ensure_data_in_bounds(data);
    ensure_address_in_bounds(address);

    if (data < 0) {
        memory[address] = (1 << WORD_SIZE) + data; /*Converting to 2's complement*/
    } else {
        memory[address] = data;
    }
}

/*function to insert a character into memory (when the character is ASCII)*/
void memory_insert_char(int address, char ch) {
    ensure_address_in_bounds(address);
    memory[address] = ch;
}
