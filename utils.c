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
