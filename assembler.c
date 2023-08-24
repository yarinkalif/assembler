#include <stdio.h>
#include <stdlib.h>

#include "assembler.h"
#include "first_pass.h"
#include "table.h"
#include "errors.h"

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

/*this function calls to the preassembler, first past and second past functions*/
int assembly_to_machine_code(char* fileName)
{	long ic = 0, dc = 0;
	int success = 0, line_number = 0;
	char *currLine = (char*)calloc(MAX_LENGTH_LINE + 2, sizeof(char));
	char *amFileName = (char*)malloc(256 * sizeof(char));

	FILE *file_desc;
	s_table *symbolTable = NULL;
	

	success = preassembler_file(fileName);
	if (success != 1) {
		printf("couldn't spread the macros correctly into %s.as\n", fileName);
	}
	
	amFileName = filename_suffix(fileName, ".am");
	file_desc = fopen(amFileName, "r");
	if (file_desc == NULL) {
		printf("couldn't open the file %s.\n", ".am");
		free(amFileName);
		return 0;
	}

	/*starting first pass*/
	symbolTable = create_symbol_table(); /*we storage the symbols here*/

	while (fgets(currLine, MAX_LENGTH_LINE + 2, file_desc) != NULL) { /*go over every line in the file*/
		if (strchr(currLine, '\n') == NULL && !feof(file_desc)) {
			handle_error(ERROR_LINE_LENGTH, line_number); /*the length of line is too long*/
			success = 0;
		}
		if (!currLine) {
			handle_error(ERROR_MEMORY_ALLOCATION, line_number);
		}
		else {
			printf("the line is:%s\n", currLine);
			success = first_pass(file_desc, currLine, symbolTable, &ic, &dc, line_number);
		}
		line_number++;
	}
	
	/*starting the second pass*/
	/*rewind(file_desc);*/
			
	free(amFileName);	
	
	return success;
}
