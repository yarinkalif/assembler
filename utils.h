#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"
#include "globals.h"

char *filename_suffix(char *str1, char *str2);

char **split_string(char *str, char *separator, int *count);

void free_split_string(char **splitString, int count);
