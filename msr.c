#include "msr.h"
#include <stdio.h>

/*
	return TRUE if possible_prime is prime
*/
Boolean test_msr(unsigned int possible_prime)
{
	Boolean is_prime = FALSE;
	if(is_odd(possible_prime) == TRUE)
	{
		Two_Natural_Numbers factors = decompose_as_power_of_two(possible_prime-1);
		MSR msr;
		msr.possible_prime = possible_prime;
		msr.t = factors.first_number;
		msr.m = factors.second_number;
		msr.a = random_natural_number(2, possible_prime-2);

		printf("t = %d \t m = %d \t a = %d \n", msr.t, msr.m, msr.a);

		is_prime = havent_witness(msr);
	}
	return is_prime;
}

Boolean havent_witness(MSR msr)
{
	Boolean havent_witness = FALSE;
	int result = 0;
	unsigned int exponant_reference = 0;
	unsigned int exponant = 0;
	unsigned int exponant_multiplier = 1;
	for(exponant_reference = 0; exponant_reference < msr.t ; exponant_reference++)
	{
		exponant = (pow(2, exponant_reference)) * msr.m;
		result = modulus(msr.a, msr.possible_prime);
		exponant_multiplier = 1;
		while(exponant_multiplier < exponant)
		{
			if(result > msr.possible_prime)
			{
				result = modulus(result, msr.possible_prime);
			}
			else
			{
				result = modulus(result*msr.a, msr.possible_prime);
				exponant_multiplier++;
			}
		}

		//printf("%d^(2^(%d) * %d) mod %d = %d \n", msr.a, exponant_reference, msr.m,
		//	msr.possible_prime, result);

		// CERTAMENTE COMPOSTO
		if(result == 1 || result == msr.possible_prime-1)
		{
			havent_witness = TRUE;
		}
	}
	// POSSIVELMENTE PRIMO
	return havent_witness;
}