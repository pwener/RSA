#include "algebra.h"

/**
 *	[EN] This method check if an long long integer number is odd
 *	[PT] Esse metodo verifica se um numero long long inteiro e par
 *	@param input_number an long long integer number
 *	@return TRUE if is Odd or FALSE if is Even
 */
Boolean is_odd(long long int input_number)
{
	Boolean is_odd = FALSE;
	if(input_number % 2 == 1)
	{
		is_odd = TRUE;
	}
	return is_odd;
}

/**
 *	[EN] This method check if an long long integer number is negativo
 *	[PT] Esse metodo verifica se um numero long long inteiro e negativo
 *	@param input_number an long long integer number
 *	@return TRUE if is negative or FALSE if is natural
 */
Boolean is_negative(long long int input_number)
{
	Boolean is_negative = FALSE;
	if(input_number < 0)
	{
		is_negative = TRUE;
	}
	return is_negative;
}

/**
 *	[EN] This method check if the two numbers is not coprime
 *	[PT] Esse metodo verifica se os dois numeros nao sao coprimos
 *	@param 
 *	@return TRUE if is not coprime or FALSE if is coprime
 */
Boolean is_divisible(long long int numerator_number, long long int denominator_number)
{
	Boolean is_divisible = FALSE;
	if( (numerator_number % denominator_number) == 0)
	{
		is_divisible = TRUE;
	}
	return is_divisible;
}

/**
 *	[EN] This method return a random natural number from the range:
 *	[PT] Esse metodo retorna um numero natural aleatorio do alcance:
 *	a < or = x < or = b
 *	@param minimum_number (a)
 *	@param maximum_number (b)
 *	@return random_number (x)
 */
unsigned long long int random_natural_number(unsigned long long int minimum_number, unsigned long long int maximum_number)
{
	srand(time(NULL));
	unsigned long long int random_number = (rand() % (maximum_number - minimum_number + 1)) + minimum_number;
	return random_number;
}

/**
 *	[EN] This method return two numbers (d and s), from the equation:
 *	[PT] Esse método retorna dois dois numeros (d e s), de acordo com a equacao:
 *	n = 2^(s) * d
 *	@param input_number (n) must be (p-1), p = prime number
 *	@return Two_Natural_Numbers
 *		first_number (s)
 *		second_number (d) an odd value
 */
Two_Natural_Numbers decompose_as_power_of_two(unsigned long long int input_number)
{
	unsigned long long int s = 1;
	unsigned long long int d = 1;
	Two_Natural_Numbers factors;
	for(s = 1; s < input_number; s++)
	{
		for(d = 1; d < (input_number/s); d++)
		{
			long long int result = (long long int) pow(2, s)*d;
			if(result == input_number && is_odd(d) == TRUE)
			{
				factors.first_number = s;
				factors.second_number = d;
				return factors;
			}
		}       
	}  
}

/**
 *	[EN] This method return magnitude's number
 *	[PT] Esse método retorna a magnitude do número
 *	@param input_number number to be calculated magnitude
 *	@return magnitude
 */
long long int get_magnitude(long long int input_number)
{	
	long long int number = input_number;
	long long int magnitude = 0;
	while(number > 0){
		magnitude++;
		number = number / 10;
    };
    return magnitude;
}
