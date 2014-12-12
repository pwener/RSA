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
unsigned long long int modulus(long long int input_number, unsigned long long int modulus_number)
{
	unsigned long long int output_number = 0;
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

unsigned long long int exponential_modulus(long long int base, long long int exponant, long long int modulus_number){
	unsigned long long int result = 0;
	result = modulus(base, modulus_number);
	long long int count = 1;
	while(count < exponant)
	{
		if(result > modulus_number)
		{
			result = modulus(result, modulus_number);
		}
		else
		{
			result = modulus(result*base, modulus_number);
			count++;
		}
	}
	return result;
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
Boolean is_congruent(long long int a_number, long long int b_number, unsigned long long int modulus_number)
{
	Boolean is_congruent = is_divisible((a_number - b_number), modulus_number);
	return is_congruent;
}

/**
 *	[EN] This method discover the quantity of numbers n < x who not satisfies x|n
 *	[PT] Esse metodo descobre a quantitade de numeros n < x que nao satisfaz x|n
 *	@param input_number (x)
 *	@return phi (n)
 */
unsigned long long int euler_totient(unsigned long long int input_number)
{
	unsigned long long int associated_number = 1;
	unsigned long long int phi = 0;
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
