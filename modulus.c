#include "modulus.h"

/*
 *	This method returns a modular number, known as residue (r), from the equation:
 *	a - r = n
 *	Example: a = 2, n = 5
 */
unsigned int modulus(int input_number, unsigned int modulus_number)
{
	unsigned int output_number = 0;
	if(is_negative(input_number)==TRUE)
	{
		output_number = (input_number % modulus_number) + input_number;
	}
	else
	{
		output_number = (input_number % modulus_number);
	}
	return output_number;
}