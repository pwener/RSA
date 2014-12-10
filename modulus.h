#ifndef MODULUS_H_
#define MODULUS_H_

#include "algebra.h"

unsigned int modulus(int input_number, unsigned int modulus_number);

Boolean is_congruent(int a_number, int b_number, unsigned int modulus_number);

unsigned int euler_totient(unsigned int input_number);

unsigned int congruence(unsigned int residue_number, int modulus_number);

Boolean check_primality_as_xzero(unsigned int input_number,
	unsigned int exponant_number, unsigned int modulus_number);

#endif // MODULUS_H_