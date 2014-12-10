#include "algebra.h"
#include "modulus.h"

/**
 *	[EN] This method returns a modular number, known as residue (r), that satisfies:
 *	[PT] Esse metodo retorna um numero em modulo, conhecido como residuo (r), que satisfaz:
 *	(a - r)/n
 *	@param input_number (a)
 *	@param modulus_number (n)
 *	@return output_number (r) a positive number
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

/**
 *	[EN] This method check if the congruence is valid
 *	[PT] Esse metodo verifica se a congruencia e valida
 *	(a - r)/n
 *	@param a_number (a)
 *	@param b_number (r)
 *	@param modulus_number (n)
 *	@return TRUE if is congruent or False if is not congruent
 */
Boolean is_congruent(int a_number, int b_number, unsigned int modulus_number)
{
	Boolean is_congruent = is_divisible((a_number - b_number), modulus_number);
	return is_congruent;
}

/**
 *
 */
unsigned int euler_totient(unsigned int input_number)
{
	unsigned int phi = 1;
	unsigned int correlationed_number;
	for(correlationed_number = 1; correlationed_number < input_number; correlationed_number++)
	{
		if(is_divisible(input_number, correlationed_number) == FALSE)
		{
			phi++;
		}
		else
		{
			
		}
	}
}