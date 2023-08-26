#ifndef _TABLE_H
#define _TABLE_H
#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "errors.h"

#define TABLE_SIZE 80

typedef struct macro {
	char *macroName;
	char *macroContent;
	struct macro *next;
} macro;


typedef struct {
	macro *head;
} macro_table;

/*typedef struct s_table{
	char **entries;
} s_table;*/

/* Define an entry in a symbols table */
typedef struct s_table_entry{
	char *symbol;
	int symbol_addr;
	symbol_type symbol_type;
	struct s_table_entry *next;
} s_table_entry;


typedef struct {
	char name[MAX_SYMBOL_LENGTH];
	int value;
	char type;
	struct Symbol* next;
} Symbol;

typedef struct SymbolTable{
	Symbol symbols[MAX_SYMBOL_LENGTH];
	char **entries;
	int count;
} SymbolTable;

SymbolTable symbol_table; 

macro_table *create_macro_table();

void add_macro_to_table(macro_table *table, char *name, char *content);

char *expend_macro(char *line, macro_table *table);

void free_macro_table(macro_table *table);

SymbolTable *create_symbol_table();

#endif
