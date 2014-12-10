#include "algebra.h"
#include "modulus.h"

/**
 *	[EN] This method returns a modular number, known as residue (r), that satisfies:
 *	[PT] Esse metodo retorna um numero em modulo, conhecido como residuo (r), que satisfaz:
 *	n|(a - r)
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
 *	n|(a - r)
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
 *	[EN] This method returns a modular number (a), that satisfies:
 *	[PT] Esse metodo retorna um numero em modulo (a), que satisfaz:
 *	n|(a - r)
 *	@param residue_number (r)
 *	@param modulus_number (n)
 *	@return output_number (a) a positive number
 */
unsigned int congruence_exponant(unsigned int input_number,
	unsigned int exponant_number, int modulus_number)
{
	unsigned int output_number = modulus(pow(input_number,1),modulus_number);
	unsigned int exponant_reference = 2;
	while(exponant_reference < exponant_number)
	{
		output_number = modulus(pow(output_number,exponant_reference),modulus_number);
		if(is_divisible(exponant_number, exponant_reference)==TRUE)
		{

		}
	}
}

/**
 *	[EN] This method discover the quantity of numbers n < x who not satisfies x|n
 *	[PT] Esse metodo descobre a quantitade de numeros n < x que nao satisfaz x|n
 *	@param input_number (x)
 *	@return phi (n)
 */
unsigned int euler_totient(unsigned int input_number)
{
	unsigned int associated_number = 1;
	unsigned int phi = 0;
	while(associated_number < input_number)
	{
		if(is_divisible(input_number, input_number) == FALSE)
		{
			phi++;
		}
		associated_number++;
	}
	return phi;
}



Boolean check_primality_as_xzero(unsigned int input_number,
	unsigned int exponant_number, unsigned int modulus_number)
{
	return FALSE;
}