#include <stdio.h>
#include <stdlib.h>
#include "table.h"


/*this function creats the linked list*/
macro_table *create_macro_table() {
	macro_table *table = (macro_table*)malloc(sizeof(macro_table));
	if (table == NULL){
		return NULL;
	}
	table->head = NULL;
	return table;
}

/*this function adds new macro to the table by using linked list*/
void add_macro_to_table(macro_table *table, char *name, char *content) {
	macro_table_val *newVal = (macro_table_val*) malloc(sizeof(macro_table_val)); /*create new space in the table for new macro*/

	newVal->macroName = (char*)malloc((strlen(name) + 1)*sizeof(char)); /*allocate memory for name*/
	strcpy(newVal->macroName,name); /*copy the macro name*/

	newVal->macroContent = (char*)malloc((strlen(content) + 1)*sizeof(char)); /*allocate memory for content*/
	strcpy(newVal->macroContent,content); /*copy the macro content*/
	
	newVal->next = table->head; /*linked the new macro to the beginning of the list*/
	table->head = newVal;
}

/*this function returns the macro value from the linked list*/
char *get_macro_val(macro_table *table, char *macroName) {
	macro_table_val *curr = table->head;

	while (curr != NULL) {
		if (strcmp(curr->macroName, macroName) == 0) {
			return curr->macroContent;
		}
		curr = curr->next; /*to the next value*/
	}
	return NULL; /*if the macro not found*/
}

/*this function free the memory used to the macro table*/
void free_macro_table(macro_table *table) {
	macro_table_val *curr = table->head;
	while (curr != NULL) {
		macro_table_val *temp = curr;
		curr = curr->next;
		free(temp->macroName);
		free(temp->macroContent);
		free(temp);
	}
}
