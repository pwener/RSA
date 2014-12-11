#ifndef RSA_H_
#define RSA_H_
#include <stdlib.h>
#include <stdio.h>
#include "algebra.h"
#include "modulus.h"
#include "msr.h"

#define MAX_STR_LENGTH 5000

char *get_text(char *path);
long file_size(char *path);

#endif
