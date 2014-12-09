#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algebra.h"

/*
* Verifica se um numero é impar
*/
Boolean is_odd(int input_number)
{
	if(input_number % 2 == 0){
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

/*
*
*/
unsigned int random_positive_number(unsigned int minimum_number, unsigned int maximum_number){
	
}

/*
* Tenta achar dois numeros d e s tais que  n-1 = 2^s * d, onde d é impar
* Retorna um vetor de inteiros contendo s e d respectivamente
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
