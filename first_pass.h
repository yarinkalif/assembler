#ifndef FIRSTPASS_H
#define FIRSTPASS_H

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "table.h"
#include "utils.h"
#include "globals.h"
#include "binary.h"


int first_pass(FILE *asFile, char *currLine, SymbolTable *symbolTable, long *IC, long *DC, int lineNumber);

int line_data_image(data_image_ptr *currLinePtr, data_image_ptr *tailPtr, char *currLine, long address, int typeOfSentence, char *keyWord, char *operands, int numberLine, SymbolTable *symbolTable, long *IC, long *DC);


#endif
