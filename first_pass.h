#ifndef FIRSTPASS_H
#define FIRSTPASS_H

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "table.h"
#include "utils.h"
#include "globals.h"
#include "binary.h"


/* Symbol structure and global declaration */
/*typedef struct Symbol {
	char name[MAX_SYMBOL_LENGTH];
	int value;
	char type;*/  /* 'c' for code */
	/*struct Symbol* next;*/  /* Pointer to the next symbol in the list */
/*} Symbol;*/

/*extern Symbol* symbol_table;  Head of the linked list */


int first_pass(FILE *asFile, char *currLine, s_table *symbolTable, long *IC, long *DC, int lineNumber);

int line_data_image(data_image_ptr *currLinePtr, data_image_ptr *tailPtr, char *currLine, long address, int typeOfSentence, char *keyWord, char *operands, int numberLine, s_table *symbolTable, long *IC, long *DC);


#endif
