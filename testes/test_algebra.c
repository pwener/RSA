#include <stdio.h>
#include <stdlib.h>
#include "algebra.h"

int main(){
	//Teste da funcao is_odd
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
	//Teste da funcao decompose
	Two_Natural_Numbers tnn;
	//Supondo que o primo seja 221, espera-se (2^2) * 55
	tnn = decompose_as_power_of_two(220);
	printf("(2^%d)* %d", tnn.first_number, tnn.second_number);
	return 0;
}
