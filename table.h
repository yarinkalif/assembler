#ifndef _TABLE_H
#define _TABLE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct macro {
	char *macroName;
	char *macroContent;
	struct macro *next;
} macro;


typedef struct {
	macro *head;
} macro_table;


macro_table *create_macro_table();

void add_macro_to_table(macro_table *table, char *name, char *content);

char *expend_macro(char *line, macro_table *table);

void free_macro_table(macro_table *table);

#endif
