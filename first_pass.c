#include <stdio.h>
#include <stdlib.h>
#include "first_pass.h"

int first_pass(char* fileName)
{
	int IC = IC;
	int DC = DC;
	int currNumberLine = 0;

	/*open the .am file*/
	FILE *assemblyFile = NULL;
	assemblyFile = fopen(fileName, "r");
	if(assemblyFile == NULL) {
		printf("The file is failed.\n");
		return 0;
	}
	
	while (!feof(assemblyFile))
	{
		char *currLine = (char*)calloc()
		if (!currLine) {
			printf("error: alloctaion error of line\n");		
	}

	define_line(currLine);
	
	fclose(source_file);
	}/*end of  while (read_next_line(source_file, line))*/
/	return 1;
}/*end of void first_pass(FILE *source_file)*/ 




/*this function define the line - empty, instruction, guidence or note*/
int define_line(char *currLine) {
	char currLine[MAX_LENGTH_LINE];
	int currNumLine = 0;
	char label, keyWord, operands;
	int checkLabel = 0;

	data_image_ptr instruction_head = NULL;
	data_image_ptr instruction_tail = NULL;

	/*In the second step, we were asked to read the following line from the source file.*/
	/*It is important to note that this operation repeats itself throughout the entire passage of the file, so we used a loop*/

	while (fgets(currLine, MAX_LENGTH_LINE + 2, asFile) != NULL) {
		char *field = strtok(line, " \t\n");
		if (field == NULL) {
			continue; // Empty or whitespace-only line, skip processing.
		}
		char guidence_type = process_field(field);
		typeOfSentence = type_of_sentence(currLine); 
		currNumLine++;
		
		/*check if the first field is label*/
		if (label[0] != '\0') {
			checkLabel = symbol_exists(label[0]);
			if (checkLabel == 0) {
				printf("Error: Symbol %s already exists in the symbol table.\n", label[0]);
			}
			else {
				insert_symbol(label[0], IC, 'c');
			}


		if (typeOfSentence == INSTRUCTION_LINE || typeOfSentence == GUIDANCE_LINE) {
			char tempCurrLine[MAX_LENGTH_LINE];
			strcpy(tmpCurrLine, currLine);

			get_data_from_line(tempCurrLine, label, keyWord, currNumLine); /*check the type of the word*/
		
			if (typeOfSentence == INSTRUCTION_LINE) {
				return get_instruction_type(keyWord, tempCurrLine);
			}
			else if (typeOfSentence == GUIDANCE_LINE) {
				return get_type_guidence(keyWord);
			}
		}
		tempLineField = strtok(NULL, " \t\n"); /*move to the next token*/
	}
	return 0;
	}/*end of while loop*/
}


/*this function get the data line*/
int line_data_image(data_image_ptr *currLine, data_image_ptr *currLinePtr, data_image_ptr *tailPtr, int typeOfSentence, long address, char *keyWord, char *operands, int numberLine) {
	int srcCodeflag = 1;
	long currAddress = address;
	int countLine = 0;

	data_image_ptr currPtr = (data_image*) malloc(sizeof(data_image));

	if (!currPtr) {
		printf("error: allocation memory\n");
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

			/**/
			(*currLinePtr) = currPtr;
			return NEXT_ADDRESS;
			break;
		}
		case GUIDENCE_LINE:
		{
			int *listOfOperands = (int*)malloc(MAX_LENGTH_LINE * sizeof(int));
			if (!listOfOperands) {
				printf("error allocation\n");
	
			int numOfOperands = operand_list_to_ascii(operands, listOfOperands, numberLine);

			typeOfLine = get_type_guidence(keyWord);
			if (typeOfLine == 0) {
				printf("error: key word incorrect\n");
			}
			/*go over the operands*/
			for (i=0; i<numOfOperands; i++) {
				tempLine = (data_image*)malloc(sizeof(data_image);
				if (!tempLine) {
					printf("error allocation memory\n");
				}
				/*every operand added to the machine code*/
				line_guidence_binary(tempLine->machine_code, keyWord, listOfOperands[i], currLine, typeOfLine, numberLine);

				if (srcCodeflag == 1) { /*adding the source code*/
					strcpy(tempLine->src_code, currLine);
					srcCodeflag = 0;
				}

				switch (typeOfLine) {
					case DATA:
						tempLine->address = currAddress + countLine;
						currAddress = currAddress + 1;
						break;
					case STRING:
						tempLine->address = currAddress + countLine;
						break;
				} /*end of switch*/
				/*continue to the next line by pointer*/
				if ((*currLinePtr) == NULL) {
					(*currLinePtr) = tempLine
					(*currLinePtr)->next = NULL;
					(*tailPtr) = tempLine;
				}
				else {
					(*tailPtr)->next = tempLine;
					tempLine->next = NULL;
					(*tailPtr) = tempLine;
				}
				countLine++;
			} /*end of for loop*/

			if (typeOfLine = DATA) {
				countLine = countLine + NEXT_ADDRESS + 1;
			} 
			return countLine;
		} /*end of switch*/
	return 0;
}

	
