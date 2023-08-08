#include <stdio.h>
#include <stdlib.h>
#include "first_pass.h"
#include "preassembler.h"
#include "tables.h"
#include "global.h"
#include "utils.h"

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
{
	int success = 0;
	success = preassembler_file(fileName);
	checkName = check_name_of_file(fileName);
	/*success = first_pass(fileName);
	if(checkName == false) {
		printf("There is no such file.\n");
		return 0;
	}*/
	return success;
}
