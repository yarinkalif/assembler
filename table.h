#ifndef _TABLE_H
#define _TABLE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct macro_table_val {
	char *macroName;
	char *macroContent;
	struct macro_table_val *next;
} macro_table_val;


typedef struct {
	macro_table_val *head;
} macro_table;


macro_table *create_macro_table();

void add_macro_to_table(macro_table *table, char *name, char *content);

char *get_macro_val(macro_table *table, char *macroName);

void free_macro_table(macro_table *table);

#endif
