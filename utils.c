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

/*this function splites the strings by separator like char*/
char **split_string(char *str, char *separator, int *count) {
	int length = strlen(str);
	int i = 0, j, k=0, l=0;
	char **substring;
	int indexString = 0; /*count the number of substrings found during the process*/
	char *strCopy = (char*) malloc((length + 1) * sizeof(char));
	*count = 0;
	
	if (strCopy == NULL) {
		return NULL;
	}
	
	strcpy(strCopy, str);
	
	while (i<length) { /*count the number of substring*/
		while (i<length && strchr(separator, strCopy[i]) != NULL) {
			i++;
		}

		j=i;
		while (j<length && strchr(separator, strCopy[j]) == NULL) {
			j++;
		}

		if (i<length && i<j) { /*found substring*/
			strCopy[j] = '\0'; /*marks the end of the substring*/
			indexString++;
		}
	i = j+1; /*to the next character*/
	} /*end of while loop*/

	/*allocate memory for the array of substrings*/
	substring = (char**) malloc(indexString * sizeof(char*));
	if (substring == NULL) {
		free(strCopy);
		return NULL;
	}
	
	/*split the substrings and storing them in the array*/
	i=0;
	l=0;
	while (i<length && k < indexString) {
		while (i<length && strchr(separator, strCopy[i]) != NULL) { 
			i++;
		} /*end of while loop*/

		j=i;
		while (j<length && strchr(separator, strCopy[j]) == NULL) { 
			j++;
		} /*end of while loop*/

		if (i<length && i<j) {
			substring[k] = (char*) malloc((j-i+1)*sizeof(char));
			if (substring[k] == NULL) { /*the memory allocation is failed*/
				for (l=0; l<k; l++) {
					free(substring[l]);
				}/*end of for*/
				free(substring);
				*count=0;
				free(strCopy);
				return NULL;
				}/*end of if*/

			strncpy(substring[k], &strCopy[i],j-i);
			substring[k][j-i] = '\0';
			k++;
		} /*end of if*/

		i=j+1;		
	}/*end of while loop*/

	*count = indexString;
	free(strCopy);
	
	return substring; /*return the array of the strings*/
}

void free_split_string(char **splitString, int count) {
	int i;
	for (i=0; i<count; i++) {
		free(splitString[i]);
	}
	free(splitString);
}


void skip_white(char *str, int *i) {
	while (str[*i] && isspace(str[*i])){
		(*i)++;
	}
}













/*int type_of_sentence(char* currLine)
{
	int label = 0; 
	int i=0;
	
	if(currLine[i] == '\0') { 
		return empty_line;
	}

	while(currLine[i] != '\0') { 
		if(currLine[i] == ':') { 
			label = 1;
		}
		else if(currLine[i] == '.') {
			return guidance_line;
		}
		else if(currLine[i] == ';') {
			return comment_line;
		}
		else if(currLine[i] == ' ' || currLine[i] == '\t') {
			return empty_line;
		else{
			return instruction_line;
		}

	}*/


