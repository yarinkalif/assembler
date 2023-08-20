#include <stdio.h>
#include <stdlib.h>
#include "first_pass.h"

int first_pass(char* fileName)
{
	int ic = IC;
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
			printf("error: alloctaion error of line);
			
	}

	
}

/*this function define the line - empty, instruction, guidence or note*/
int define_line() {
	char currLine[MAX_LENGTH_LINE];
	int currNumLine = 0;
	char label, keyWord, operands;
	int checkLabel = 0;

	data_image_ptr instruction_head = NULL;
	data_image_ptr instruction_tail = NULL;

	/*In the second step, we were asked to read the following line from the source file.*/
	/*It is important to note that this operation repeats itself throughout the entire passage of the file, so we used a loop*/

	while (fgets(currLine, MAX_LENGTH_LINE + 2, asFile) != NULL) {
		typeOfSentence = type_of_sentence(currLine); 
		currNumLine++;
		
		if (typeOfSentence == INSTRUCTION_LINE || typeOfSentence == GUIDANCE_LINE) {
			char tempCurrLine[MAX_LENGTH_LINE];
			strcpy(tmpCurrLine, currLine);

			get_data_from_line(tempCurrLine, label, keyWord, currNumLine);

			if (label[0] != '\0') {
				checkLabel = symbol_exists(label[0]);
				if (checkLabel == 0) {
					 printf("Error: Symbol %s already exists in the symbol table.\n", label[0]);
				}
			}
			if (typeOfSentence == INSTRUCTION_LINE) {
				
			}

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
						currAddress = currAddress + 12;
						break;
					case STRING:
						

}














/*
		char tempLineField[MAX_LENGTH_LINE + 2];
		strcpy(tempLineField, currLine);
		char *field = strtok(tempLineField, " \t\n"); 
		if (field == NULL) { 
			continue; 
		}

		if (typeOfSentence == GUIDENCE_LINE)
			{
				char guidence_type = process_field(field);

				if (guidence_type == 's') {
					if (symbol_exists(field)) {
						printf("Error: Symbol %s already exists in the symbol table.\n", field);
					}
					else {
						insert_symbol(field, DC, SYMBOL_TYPE_DATA);
						/* Continue processing the line to check for directives or commands following the symbol.*/
						/*field = strtok(NULL, " \t\n");
						instruction_type = process_field(field);
					}
				}

				if (guidence_type == 'e') {
					handle_instruction(field, strtok(NULL, ""));
				}
				else if (guidence_type == 'd') {  /* Handle data (.data or .string) here if needed.*/
				/* Code for processing data directives can be added here.*/
				/*}
				else if (guidence_type == 'u') { /* Handle commands or unknown fields here.*/
				/* Code for processing commands or handling errors for unknown fields can be added here.*/
			/*	}
			}
		if (typeOfSentence == INSTRUCTION_LINE) {
			

		}
		
		tempLineField = strtok(NULL, " \t\n"); /*move to the next token*/

	


	/*fclose(source_file);
	}/*end of  while (read_next_line(source_file, line))*/
/*	return 1;
}/*end of void first_pass(FILE *source_file)*/ 



