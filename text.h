#ifndef TEXT_H_
#define TEXT_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "algebra.h"

#define MAX_WORD_LENGHT 45

char *get_text_by_file(char *path);
char *receive_string_from_user(unsigned int text_size);
Boolean export_text_to_file(char *text_input);
long file_size(char *path);
void fix_word(char *word);
char *tolow(char *string);
Boolean verify_if_uppercase(char letter);
Boolean is_letter(char letter);
Boolean compare_strings(char *first, char *second);
int numberoflines(FILE *input_file);
char **get_dictionary();

#endif