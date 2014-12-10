#include <stdio.h>
#include <stdlib.h>
#include "msr.h"

int main(){
	int x;
	/* for(x = 4; x < 300; x++){
		if(test_msr(x)){
			printf("%d , ", x);
		}
	} */
	printf("\n\n");
	if(test_msr(8969))
	{
			printf("8969\n");
	}
	printf("\n\n");
	if(test_msr(13711))
	{
			printf("13711\n");
	}
}
