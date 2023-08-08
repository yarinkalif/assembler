#include <stdlib.h>
#include <stdio.h>
#include "table.h"
#include "utils.h"
#include "globals.h"


#define MAX_MACRO_SIZE_NAME 40

int preassembler_file(char* fileName) {
	FILE *amFile; /*the file after the preassembler*/
	char *amFileName = filename_suffix(fileName, ".am");
	char *asFileName = filename_suffix(fileName, ".as");
	FILE *asFile = fopen(asFileName, "r"); /*the original file*/

	char currLine[MAX_LENGTH_LINE + 2];
	char *macroName = NULL;
	char **splitLines;
	int numberOfLineWords = 0;
	int i;
	macro_table *macroTable = create_macro_table();
	int macroFlag = 0; 

	/*Checks whether the original file opens successfully*/
	if(asFile == NULL) {
		printf("The file is failed.\n");
		free(amFileName);
		free(asFileName);
		free_macro_table(macroTable);
		return 0;
	}

	/*Checks whether the new am file creates successfully*/
	amFile = fopen(amFileName, "w");
	if(amFile == NULL) {
		printf("The file is failed.\n");
		free(amFileName);
		free(asFileName);
		fclose(asFile);
		fclose(amFile);
		free_macro_table(macroTable);
		return 0;		
	}

	while(fgets(currLine, MAX_LENGTH_LINE + 2, amFile)) {
		i = 0;
		if (currLine[i] == EOF || currLine[i] == ';' || currLine[i] == '\n' || currLine[i] == '\0') {
			continue;
		}
		
		splitLines = split_string(currLine+i, " ", &numberOfLineWords); /*split the lines by white space*/

		/*print the macros*/
		if (get_macro_val(macroTable, splitLines[0]) != NULL) {
			fputs(get_macro_val(macroTable, splitLines[0]), amFile);
		}
		/*if there is macro, add it to the table*/
		else if (strcmp(splitLines[0], "mcro") == 0) {
			macroFlag = 1;
			macroName = (char*) malloc(sizeof(char)*MAX_MACRO_SIZE_NAME);
			strcpy(macroName, splitLines[1]);
			add_macro_to_table(macroTable, macroName, "");
		}
		else if (macroFlag == 1) {
			char *newMacro = filename_suffix(get_macro_val(macroTable, macroName), currLine);
			add_macro_to_table(macroTable, macroName, newMacro);
			free(newMacro);
		}
		/*not a macro line*/
		else {
			fputs(currLine, amFile);
		}

		free_split_string(splitLines, numberOfLineWords);
	}

	/*free all the memory we have used*/
	free(amFileName);
	fclose(amFile);
	free(asFileName);
	fclose(asFile);
	free_macro_table(macroTable);
	if (macroName != NULL) {
		free(macroName);
	}
	return 1;
}
