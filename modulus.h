#ifndef MODULUS_H_
#define MODULUS_H_

#include "algebra.h"

unsigned long long int modulus(long long int input_number, unsigned long long int modulus_number);

unsigned long long int exponential_modulus(long long int base, long long int exponant, long long int modulus_number);

Boolean is_congruent(long long int a_number, long long int b_number, unsigned long long int modulus_number);

unsigned long long int euler_totient(unsigned long long int input_number);

#endif // MODULUS_H_
