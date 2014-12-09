#include <stdio.h>
#include <stdlib.h>
#include "algebra.h"

int main(){
	printf("---> Teste da funcao is_odd \n");
	int i;
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

	printf("---> Teste da funcao decompose_as_power_of_two \n");
	Two_Natural_Numbers tnn;
	printf("Supondo que o primo seja 221, espera-se (2^2) * 55\n");
	tnn = decompose_as_power_of_two(220);
	printf("-------> (2^%d) * %d \n", tnn.first_number, tnn.second_number);

	printf("---> Teste da funcao random_natural_number \n");
	printf("%d \n", random_natural_number(2,3));
	printf("%d \n", random_natural_number(2,3));
	printf("%d \n", random_natural_number(2,3));

	return 0;
}
