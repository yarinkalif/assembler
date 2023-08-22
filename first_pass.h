#ifndef FIRSTPASS_H
#define FIRSTPASS_H

int first_pass(char* fileName);

int define_line(char *currLine);

int line_data_image(data_image_ptr *currLine, data_image_ptr *currLinePtr, data_image_ptr *tailPtr, int typeOfSentence, long address, char *keyWord, char *operands, int numberLine, long *ic, long *dc);

#endif
