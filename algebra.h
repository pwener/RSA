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
	unsigned int first_number;
	unsigned int second_number;
}Two_Natural_Numbers;

Boolean is_odd(int input_number);
Boolean is_negative(int input_number);
Boolean is_divisible(int numerator_number, int denominator_number);

unsigned int random_natural_number(unsigned int minimum_number, unsigned int maximum_number);

Two_Natural_Numbers decompose_as_power_of_two(unsigned int input_number);

int get_magnitude(int input_number);

#endif // ALGEBRA_H_