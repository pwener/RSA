#include "algebra.h"

/**
 *	[EN] This method check if an integer number is odd
 *	[PT] Esse metodo verifica se um numero inteiro e par
 *	@param input_number a integer number
 *	@return TRUE if is Odd or FALSE if is Even
 */
Boolean is_odd(int input_number)
{
	Boolean isOdd = FALSE;
	if(input_number % 2 == 1)
	{
		isOdd = TRUE;
	}
	return isOdd;
}

/**
 *	[EN] This method return a random natural number from the range:
 *	[PT] Esse metodo retorna um numero natural aleatorio do alcance:
 *	a < or = x < or = b
 *	@param minimum_number (a)
 *	@param maximum_number (b)
 *	@return random_number (x)
 */
unsigned int random_natural_number(unsigned int minimum_number, unsigned int maximum_number){
	unsigned int random_number = 0;
	
}

/**
 *	Tenta achar dois numeros d e s tais que  n-1 = 2^s * d, onde d é impar
 *	Retorna um vetor de inteiros contendo s e d respectivamente
 */
Two_Natural_Numbers decompose_as_power_of_two(unsigned int input_number){
	int s, d;
	Two_Natural_Numbers factors;
	for(s = 1; s < input_number; s++)
	{
		for(d = 1; d < input_number/s; d++)
		{
			int result = (int) pow(2, s)*d;
			if(result == input_number && is_odd(d) == TRUE)
			{
				factors.first_number = s;
				factors.second_number = d;
				return factors;
			}
		}       
	}  
}
