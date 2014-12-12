#include <stdio.h>
#include <stdlib.h>
#include "algebra.h"
#include "modulus.h"

void test_is_odd()
{
	printf("---> Teste da funcao is_odd \n");
	long long int i;
	for(i = 1; i < 10; i++)
	{
		if(is_odd(i) == TRUE)
		{
			printf("%d is odd", i);
		}
		else
		{
			printf("%d is even", i);
		}
		printf("\n");
	}
}

void test_decompose_as_power_of_two()
{
	printf("---> Teste da funcao decompose_as_power_of_two \n");
	Two_Natural_Numbers tnn;
	printf("Supondo que o primo seja 221, espera-se (2^2) * 55\n");
	tnn = decompose_as_power_of_two(220);
	printf("-------> (2^%d) * %d \n", tnn.first_number, tnn.second_number);
	printf("Supondo que o primo seja 19, espera-se (2^1) * 9\n");
	tnn = decompose_as_power_of_two(18);
	printf("-------> (2^%d) * %d \n", tnn.first_number, tnn.second_number);
}

void test_random_natural_number()
{
	printf("---> Teste da funcao random_natural_number \n");
	printf("%d \n", random_natural_number(20,30));
	printf("%d \n", random_natural_number(25,60));
	printf("%d \n", random_natural_number(45,45));
}

void test_modulus()
{
	printf("--> Teste da Funcao Modulus \n");
	printf("%d\n", modulus(2,5));
	printf("%d\n", modulus(30,5));
	printf("%d\n", modulus(8,5));
}

void test_is_congruent()
{
	printf("--> Teste da Funcao Modulus \n");
	printf("%d\n", is_congruent(2,2,5));
	printf("%d\n", is_congruent(30,0,5));
	printf("%d\n", is_congruent(8,3,5));
}

int main(){
	test_is_odd();
	test_decompose_as_power_of_two();
	test_random_natural_number();
	test_modulus();
	test_is_congruent();
	return 0;
}
