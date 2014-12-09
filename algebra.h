#ifndef ALGEBRA_H_
#define ALGEBRA_H_

typedef enum Boolean
{
	FALSE,
	TRUE
}Boolean;

Boolean is_odd(int input_number);

unsigned int random_positive_number(unsigned int minimum_number, unsigned int maximum_number);

unsigned int[2] decompose_as_power_of_two(unsigned int input_number);

#endif // ALGEBRA_H_