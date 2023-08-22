#include <stdio.h>
#include <stdlib.h>
#include "first_pass.h"
#include "preassembler.h"
#include "table.h"
#include "globals.h"
#include "utils.h"
#include "assembler.h"

int main(int argc, char *argv[])
{
	int fileSuccess = 0, i;
	if (argc == 1) /*if there is no file in the input*/
	{
		printf("ERROR: Please enter asseembly file name");
		exit(EXIT_SUCCESS); 
	}

	for(i = 1; i < argc; i++) /*passing over the files in the input*/
	{
		fileSuccess = assembly_to_machine_code(argv[i]);
		if(fileSuccess == 0)
		{
			printf("\n '%s' The file is failed.\n", argv[i]);
		}
	}	

return fileSuccess;
}


int assembly_to_machine_code(char* fileName)
{	long ic = 0, dc = 0;
	int success = 0;
	char tmpLine[MAX_LENGTH_LINE + 2];
	line_info currLine;
	s_table *symbolTable = NULL;
	data_word dataImage[MAX_MEMORY_SIZE] = {0}; /* contains the data image of the file */

	preassembler_file(fileName);
	if (!preassembler_file) {
		printf("couldn't spread the macros correctly into %s.as\n", fileName);
	}
	
	amFileName = filename_suffix(fileName, ".am");
	file_desc = fopen(amFileName, "r");
	if (file_desc == NULL) {
		printf("couldn't open the file %s.\n", ".am");
		free(amFileName);
		return FALSE;
	}

	/*starting first pass*/
	symbolTable = initialize_symbol_table();
	currLine.filename = amFileName;
	currLine.content = tmpLine;
	for (currLine.line_number=1; fgets(tmpLine, MAX_LENGTH_LINE + 2, file_desc) != NULL; currLine.lineNumber++) {
		/*check if the line is too long*/
		if (strchr(tmpLine, '\n') == NULL && !feof(file_desc)) {		
			handle_error(ERROR_LINE_LENGTH, lineNumber);
			success = 0;
		}
		else {
		success = first_pass(currLine, symbolTable, &ic, &dc, dataImage, lineNumber);
		}
	}
	
	/*starting the second pass*/
	rewind(file_desc);
			
		
	
	return success;
}
