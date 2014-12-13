#ifndef ALGEBRA_H_
#define ALGEBRA_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef enum Boolean
{
	FALSE,
	TRUE
}Boolean;

typedef struct Two_Natural_Numbers
{
	unsigned long long int first_number;
	unsigned long long int second_number;
}Two_Natural_Numbers;

Boolean is_odd(long long int input_number);
Boolean is_negative(long long int input_number);
Boolean is_divisible(long long int numerator_number, long long int denominator_number);

unsigned long long int random_natural_number(unsigned long long int minimum_number, unsigned long long int maximum_number);

Two_Natural_Numbers decompose_as_power_of_two(unsigned long long int input_number);

long long int get_magnitude(long long int input_number);

#endif // ALGEBRA_H_