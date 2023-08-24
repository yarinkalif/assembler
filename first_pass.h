#ifndef FIRSTPASS_H
#define FIRSTPASS_H

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "table.h"
#include "utils.h"


/* Symbol structure and global declaration */
/*typedef struct Symbol {
	char name[MAX_SYMBOL_LENGTH];
	int value;
	char type;*/  /* 'c' for code */
	/*struct Symbol* next;*/  /* Pointer to the next symbol in the list */
/*} Symbol;*/

/*extern Symbol* symbol_table;  Head of the linked list */


int first_pass(FILE *asFile, char *currLine, SymbolTable *symbolTable, long *IC, long *DC, int lineNumber);

int line_data_image(data_image_ptr *currLinePtr, data_image_ptr *tailPtr, char *currLine, int typeOfSentence, long address, char *keyWord, char *operands, int numberLine, SymbolTable *symbolTable);

/*int line_data_image(char *currLine, SymbolTable *symbolTable, int typeOfSentence, int numberLine, long *ic, long *dc);*/

#endif
