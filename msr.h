#ifndef MSR_H_
#define MSR_H_
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "algebra.h"
#include "modulus.h"

typedef struct Miller_Selfridge_Rabin
{
	unsigned long long int possible_prime;
	unsigned long long int t;
	unsigned long long int m;
	unsigned long long int a;
}MSR;

Boolean test_primality_msr(unsigned long long int possible_prime);
Boolean havent_witness(MSR msr);

#endif

