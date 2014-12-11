#ifndef TEXT_H_
#define TEXT_H_
#include <stdlib.h>
#include <stdio.h>

#define MAX_WORD_LENGHT 45

char *get_text(char *path);
long file_size(char *path);
int numberoflines(FILE *input_file);
char **get_dictionary();
void fix_word(char *word);

#endif
