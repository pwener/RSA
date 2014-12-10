#include "msr.h"

/*
	return TRUE if possible_prime is prime
*/
Boolean teste_msr(unsigned int possible_prime)
{
	if(is_odd(possible_prime) == FALSE)
	{
		return FALSE;
	}
	else
	{
		Two_Natural_Numbers factors;
		factors = decompose_as_power_of_two(possible_prime);
		int a = random_natural_number(2, n-2);
		int loop, times;
		times = get_number_of_times(possible_prime);
		while(loop<times){
			int x, result;
			for(x = 0; x<factors.first_number; x++)
			{
				int m = pow(2, x)*d;
				result = mod(a, n);
				int z = 1;
				while(z < (pow(2, x)*factors.second_number))
				{
					if(result>times)
					{
						result = mod(result, n);
					}
					else
					{
						result = mod(result*a, n);
						z++;
					}
				}
				if(result != 1){
					return FALSE;
				}
			}
			a = random_natural_number(2, n-2);
		}
		return TRUE;
	}
}

int get_number_of_times(int target){
	int times;
	if(number < 100)
	{
		times = number * 0.1
	}       
	else    
	{
		times = 100;
	}
	return times;
}

