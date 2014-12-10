#ifndef MSR_H_
#define MSR_H_
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "algebra.h"
#include "modulus.h"

typedef struct Miller_Selfridge_Rabin
{
	unsigned int possible_prime;
	unsigned int t;
	unsigned int m;
	unsigned int a;
}MSR;

Boolean test_primality_msr(unsigned int possible_prime);
Boolean havent_witness(MSR msr);

#endif

