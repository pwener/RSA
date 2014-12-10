#include <stdio.h>
#include <stdlib.h>
#include "msr.h"

int main(){
	int x;
	for(x = 4; x < 20; x++){
		if(test_msr(x)){
			printf("\n-->%d", x);
		}
	}
}
