#include "msr.h"

/*
*	return TRUE if possible_prime is prime
*/
Boolean test_primality_msr(unsigned long long int possible_prime)
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
		is_prime = havent_witness(msr);
	}
	return is_prime;
}

Boolean havent_witness(MSR msr)
{
	Boolean havent_witness = FALSE;
	long long int result = 0;
	unsigned long long int exponant_reference = 0;
	unsigned long long int exponant = 0;
	unsigned long long int exponant_multiplier = 1;
	for(exponant_reference = 0; exponant_reference < msr.t ; exponant_reference++)
	{
		exponant = (pow(2, exponant_reference)) * msr.m;
		result = exponential_modulus(msr.a, exponant, msr.possible_prime);
		// Provavel primo
		if(result == 1 || result == msr.possible_prime-1)
		{
			havent_witness = TRUE;
		}
	}
	// CERTAMENTE COMPOSTO
	return havent_witness;
}
