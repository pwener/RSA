#ifndef TEXT_H_
#define TEXT_H_
#include <stdlib.h>
#include <stdio.h>
#include "algebra.h"
#include "modulus.h"
#include "msr.h"

char *get_text(char *path);
long file_size(char *path);
char **get_dicionary();

#endif
