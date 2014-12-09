#include "modulus.h"

/**
 *	[EN] This method returns a modular number, known as residue (r), from the equation:
 *	[PT] Esse metodo retorna um numero em modulo, conhecido como residuo (r), da equacao:
 *	a/n = x + r;
 *	@param input_number (a)
 *	@param modulus_number (n)
 *	@return output_number (r)
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