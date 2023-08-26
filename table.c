#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"



/*this function creats the linked list*/
macro_table *create_macro_table() {
	macro_table *table = (macro_table*)malloc(sizeof(macro_table));
	if (table == NULL){ /*check if the memory allocation successed*/
		return NULL;
	}
	table->head = NULL;
	return table;
}

/*this function adds new macro to the table by using linked list*/
void add_macro_to_table(macro_table *table, char *name, char *content) {
	macro *newMacro = (macro*) malloc(sizeof(macro)); /*create new space in the table for new macro*/

	newMacro->macroName = (char*)malloc((strlen(name) + 1)*sizeof(char)); /*allocate memory for name*/
	strcpy(newMacro->macroName,name); /*copy the macro name*/
	newMacro->macroContent = (char*)malloc((strlen(content) + 1)*sizeof(char)); /*allocate memory for content*/
	strcpy(newMacro->macroContent,content); /*copy the macro content*/
	newMacro->next = table->head; /*linked the new macro to the beginning of the list*/
	table->head = newMacro;
}

/*this function replace macro name with his content*/
char *expend_macro(char *line, macro_table *table) {
	macro *curr = table->head; /*pointed to the head of the linked list*/
	char *expendLine = (char *)malloc(MAX_LENGTH_LINE + 2);

	if (expendLine == NULL) {
		return NULL;
	}
	strcpy(expendLine, line);

	while (curr != NULL){
		char *macroPos = strstr(expendLine, curr->macroName); /*search for the macro name in the linked list*/
		if (macroPos != NULL) { /*found the macro name*/
			strcpy(macroPos, curr->macroContent); /*replace the line with the macro content*/
			return expendLine;
		}
		curr = curr->next;
	}
	return expendLine;
}
	

/*this function free the memory used to the macro table*/
void free_macro_table(macro_table *table) {
	macro *curr = table->head;
	while (curr != NULL) {
		macro *temp = curr;
		curr = curr->next;
		free(temp->macroName);
		free(temp->macroContent);
		free(temp);
	}
}

SymbolTable *create_symbol_table() {
	int i=0;
	SymbolTable *symbolTable = malloc(sizeof(SymbolTable));
	symbolTable->entries = malloc(sizeof(s_table_entry) * TABLE_SIZE);
	for (i=0; i<TABLE_SIZE; i++) {
		symbolTable->entries[i] = NULL;
	}
	free(symbolTable);
	free(symbolTable->entries);
	return symbolTable;
}
