#include "msr.h"
#include <stdio.h>

/*
	return TRUE if possible_prime is prime
*/
Boolean test_msr(unsigned int possible_prime)
{
	if(is_odd(possible_prime) == FALSE)
	{
		return FALSE;
	}
	else
	{
		Two_Natural_Numbers factors;
		factors = decompose_as_power_of_two(possible_prime-1);
		int a = random_natural_number(2, possible_prime-2);
		int loop = 0;
		int times = get_number_of_times(possible_prime);
		while(loop<times){
			int x, result;
			for(x = 0; x<factors.first_number; x++)
			{
				int m = pow(2, x)*factors.second_number;
				printf("\n s = %d \t| d = %d \t| m = %d \t| a = %d", x, factors.first_number, m, a);
				result = modulus(a, possible_prime);
				int z = 1;
				while(z < m)
				{
					if(result>possible_prime)
					{
						result = modulus(result, possible_prime);
					}
					else
					{
						result = modulus(result*a, possible_prime);
						z++;
					}
				}
				if(result != 1){
					return FALSE;
				}
			}
			loop++;
			a = random_natural_number(2, possible_prime-2);
		}
		return TRUE;
	}
}

int get_number_of_times(int target){
	int times;
	if(target < 100)
	{
		times = target * 0.1;
	}       
	else    
	{
		times = 100;
	}
	return times;
}

