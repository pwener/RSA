#ifndef MODULUS_H_
#define MODULUS_H_

#include "algebra.h"

unsigned int modulus(int input_number, unsigned int modulus_number);

unsigned int exponential_modulus(int base, int exponant, int modulus_number);

Boolean is_congruent(int a_number, int b_number, unsigned int modulus_number);

unsigned int euler_totient(unsigned int input_number);

#endif // MODULUS_H_
