#include <stdlib.h>
#include <stdio.h>
#include "table.h"
#include "utils.h"
#include <string.h>
#include "globals.h"


#define MAX_MACRO_SIZE_NAME 40

int preassembler_file(char* fileName) {
	FILE *amFile; /*the file after the preassembler*/
	char *amFileName = filename_suffix(fileName, ".am");
	char *asFileName = filename_suffix(fileName, ".as");
	FILE *asFile = fopen(asFileName, "r"); /*the original file*/

	char currLine[MAX_LENGTH_LINE + 2]; /*array of characters*/
	char *macroName = NULL;
	char *macroContent = NULL;	
	macro_table *macroTable = create_macro_table();
	int macroFlag = 0; 
	macro *currentMacro;
	macro *temp;
	char *expendLine;


	/*Checks whether the original file opens successfully*/
	if(asFile == NULL) {
		printf("The file is failed.\n");
		free(amFileName);
		free(asFileName);
		free_macro_table(macroTable);
		return 0;
	}

	/*Checks whether the new am file creates successfully*/
	amFile = fopen(amFileName, "w+");
	if(amFile == NULL) {
		printf("The file is failed.\n");
		free(amFileName);
		free(asFileName);
		fclose(asFile);
		fclose(amFile);
		free_macro_table(macroTable);
		return 0;		
	}

	while(fgets(currLine, MAX_LENGTH_LINE + 2, asFile) != NULL) { /*reading the file line by line*/
			/*printf("current line: %s\n", currLine);*/
			/*strcpy(currLine, currLine + 4);*/
			printf("current line: %s\n", currLine);
			/*if (getchar(currLine) == '\n' || getchar(currLine) == EOF || getcar(currLine) == ';' || getchar(currLine) == '\0') {
				continue;
			}*/
			if (strstr(currLine, "mcro") != NULL) {
				macroFlag = 1;
				macroName = (char *)malloc(MAX_MACRO_SIZE_NAME);
				strcpy(currLine, currLine + 4);
				printf("before: %s", currLine);
				skip_white_spaces(currLine);
				printf("after: %s", currLine);
				/*printf("outside util ptr: %d\n", currLine);*/
				strcpy(macroName, currLine);

				/*fgets(macroName, MAX_MACRO_SIZE_NAME, asFile);*/
				printf("macro name is: %s\n", macroName);
				macroContent = (char *)malloc(MAX_LENGTH_LINE + 2);

				while (fgets(currLine, MAX_LENGTH_LINE + 2, asFile) != NULL) {
					printf("current line: %s\n", currLine);
					if (strstr(currLine, "endmcro") != NULL) {
						macroFlag = 0;
						add_macro_to_table(macroTable, macroName, macroContent);
						break;
					}
					if (macroFlag) { /*we are still in macro definition*/
						strcat(macroContent, currLine);
					}
				}
				/*for debug*/
				/*currentMacro = macroTable->head;
				while (currentMacro != NULL) {
					printf("Macro Name: %s\nMacro Content: %s\n", currentMacro->macroName, currentMacro->macroContent);
					currentMacro = currentMacro->next;
				}*/
			}
			else { /*if find nacro name, print his content instead*/
				expendLine = expend_macro(currLine, macroTable);
				if (expendLine != NULL) {
					fputs(expendLine, amFile);
					free(expendLine);
				}
				else { /*regular line*/
					fputs(currLine, amFile);
				}
			}
		}


	/*free all the memory we have used*/
	currentMacro = macroTable->head;
	while (currentMacro != NULL) {
		temp = currentMacro;
		currentMacro = currentMacro->next;
		free(temp->macroName);
		free(temp->macroContent);
		free(temp);
	}
	free(macroTable);
	free(macroName);
	free(macroContent);
	fclose(asFile);
	fclose(amFile);
	return 1;
}
