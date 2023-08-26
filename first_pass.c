#include <stdio.h>
#include <stdlib.h>
#include "first_pass.h"
#include "table.h"
#include "utils.h"
#include "globals.h"


int first_pass(FILE *asFile, char *currLine, SymbolTable *symbolTable, long *IC, long *DC, int lineNumber) {
	IC = 0; /*instruction counter*/
	DC = 0; /*data counter*/
	int currNumberLine = 0; /*count the number of lines*/
	int guidenceLineCount = 0;
	char tmpCurrLine[MAX_LENGTH_LINE], label[MAX_SYMBOL_LENGTH], keyWord[MAX_LENGTH_KEY_WORD], operands[MAX_LENGTH_LINE];

	data_image_ptr instructionHead = NULL, instructionTail = NULL, ptrInstruction;
	data_image_ptr guidenceHead = NULL, guidenceTail = NULL, ptrGuidence;
	Symbol *symbolHead = NULL, *symbolTail = NULL, *ptrSymbol;

	

	int typeOfSentence = type_of_sentence(currLine); /*check the type of line*/
	printf("type of sentence is:%d\n" ,typeOfSentence);
	
	currNumberLine++;
	if (typeOfSentence == INSTRUCTION_LINE || typeOfSentence == GUIDANCE_LINE) {
		strcpy(tmpCurrLine, currLine);
		get_data_from_line(tmpCurrLine, label, keyWord, operands, lineNumber);
		/*checking if the label exist, if not it will add to the symbol table*/
		if (label[0] != '\0') {
			int checkLabel = symbol_exists(label[0], symbolTable);
			if (checkLabel) {
				handle_error(LABEL_EXIST, lineNumber);
			}
		}
		/*create the data image*/
		if (typeOfSentence == INSTRUCTION_LINE ) {
			if (instructionHead == NULL) {
				IC = IC + line_data_image(&instructionHead, NULL, currLine, IC, typeOfSentence, keyWord, operands, currNumberLine, symbolTable);
				instructionHead->next = NULL;
				instructionTail = instructionHead;
			}
			else {
				IC = IC + line_data_image(&ptrInstruction, NULL, currLine, IC, typeOfSentence, keyWord, operands, currNumberLine, symbolTable);
				instructionTail->next = ptrInstruction;			
				instructionTail = instructionTail->next;
			}
		}
		else {
			if (guidenceHead = NULL) {
				guidenceLineCount = line_data_image(&guidenceHead, &guidenceTail, currLine, IC, typeOfSentence, keyWord, operands, 	currNumberLine, symbolTable);
			}
			else {
				guidenceLineCount = line_data_image(&guidenceHead, &guidenceTail, currLine, IC, typeOfSentence, keyWord, operands, currNumberLine, symbolTable);
			}
			DC = DC + guidenceLineCount;
		}

		/*ceate symbol table*/
		if ((label[0] != '\0')|| (!strcmp(keyWord, ".extern"))) {
			long currAddress;
			
			strcat(label, "\0");
			if (typeOfSentence == INSTRUCTION_LINE) { /*the line is instruction*/
				currAddress = IC - NEXT_ADDRESS;
			}
			else { /*the other lines*/
				currAddress = *IC + *DC - guidenceLineCount;
			}
			if (symbolHead == NULL) {
				if (!strcmp(keyWord, ".extern")) {
					symbolHead = insert_symbol(operands, 0, EXTERN_SYMBOL); /*the value of extern is 0*/
				}
				else { /*the other symbols like entry*/
					symbolHead = insert_symbol(label, currAddress, typeOfSentence);
				}
				symbolHead->next = NULL;
				symbolTail = symbolHead;
			}

			else {
				if (!strcmp(keyWord, ".extern")) {
					ptrSymbol = insert_symbol(operands, 0, EXTERN_SYMBOL);
				}
				else {
					ptrSymbol = insert_symbol(label, currAddress, EXTERN_SYMBOL);
				}
				symbolTail->next = ptrSymbol;
				symbolTail = symbolTail->next;
			}
		}
	} /*end of if condition typeOfSentence == INSTRUCTION_LINE || typeOfSentence == GUIDANCE_LINE*/
	
	free(currLine);
	
	/*order the lines that instrucion after guidance*/
	/*if (guidanceHade != NULL && instructinHead != NULL) {
		
	}*/
	
	return 1;
}/*end of void first_pass(FILE *source_file)*/ 



/*this function get the data line*/
int line_data_image(data_image_ptr *currLinePtr, data_image_ptr *tailPtr, char *currLine, long address, int typeOfSentence, char *keyWord, char *operands, int numberLine, SymbolTable *symbolTable) {
	int srcCodeflag = 1;
	long currAddress = address;
	int strLength = strlen(currLine);
	int countLine = 0;
	int i;

	data_image_ptr currPtr = (data_image*) malloc(sizeof(data_image));

	if (!currPtr) {
		handle_error(ERROR_MEMORY_ALLOCATION, numberLine);
	}

	switch (typeOfSentence)
	{
		case INSTRUCTION_LINE:
		{
			/*define the correct value*/
			line_instruction_binary(currPtr->machine_code, keyWord, operands, numberLine);
			strcpy(currPtr->src_code, currLine);
			currPtr->address = address;
			currPtr->next = NULL;
			/*(*ic)++;*/

			/*The pointer moves to the next position after it*/
			(*currLinePtr) = currPtr;
			return NEXT_ADDRESS;
			break;
		}
		case GUIDANCE_LINE:
		{	
			if (get_type_guidence(keyWord) == 1) { /*if it's ".data"*/
				int *listOfOperands = (int*)malloc(MAX_LENGTH_LINE * sizeof(int));
				if (!listOfOperands) {
					printf("Error: Memory allocation failed.\n");
				}
				int numOfOperands = operand_list_to_ascii(operands, listOfOperands, numberLine);

				for (i = 0; i < numOfOperands; i++) {
					currPtr = (data_image*)malloc(sizeof(data_image));
					if (!currPtr) {
						printf("Error: Memory allocation failed.\n");
					}
				
					/*convert operand to machine code and update data image*/
					line_guidence_binary(currPtr->machine_code, keyWord, listOfOperands[i], currLine, DATA, numberLine);
			
					/*update source code and data image properties*/
					if (srcCodeflag == 1) {
						strcpy(currPtr->src_code, currLine);
						srcCodeflag = 0;
					}
					currPtr->address = countLine;
					currPtr->next = NULL;

					/*Update linked list of data images*/
					if (*currLinePtr == NULL) {
						*currLinePtr = currPtr;
						(*currLinePtr)->next = NULL;
						*tailPtr = currPtr;
					} 
					else {
						(*tailPtr)->next = currPtr;
						currPtr->next = NULL;
						*tailPtr = currPtr;
					}
				/*(*dc)++;*/
				countLine++;
				} /*end for loop*/
				return countLine;
			}
			else if(get_type_guidence(keyWord) == 2) { /*if it's ".string"*/
				for (i = 0; i<strLength; i++) {
					data_image_ptr tempLine = (data_image_ptr)malloc(sizeof(data_image));	
					if (!tempLine) {
						handle_error(ERROR_MEMORY_ALLOCATION, numberLine);
					}
		
					char curr_char = (i < strLength) ? currLine[i] : '\0'; /*add the null terminator and update DC*/

					/*encode the character and add to the machine code*/
					line_guidence_binary(tempLine->machine_code, ".string", currLine[i], currLinePtr, STRING, 0);

					/*update pointers and add source code and address*/
					strcpy(tempLine->src_code, currLine);
					tempLine->address = currAddress;
	
					if ((*currLinePtr) == NULL) {
						(*currLinePtr) = tempLine;
						(*currLinePtr)->next = NULL;
						(*tailPtr) = tempLine;
					} 
					else {
						(*tailPtr)->next = tempLine;
						tempLine->next = NULL;
						(*tailPtr) = tempLine;
					}
					/*(*dc)++;*/
				} /*end of for loop*/
			}
			/*else if (get_type_guidence(keyWord) == 4) {*/ /*if it's ".extern"*/
				/*handle_instruction(field, strtok(NULL, ""));*/
			/*}*/
			
		}
	}
		
	return 0;
}
	
	
	



