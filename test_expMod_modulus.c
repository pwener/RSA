#include "rsa.h"

int main(){
	char texto[] = "A menina brinca na rua";
	rsa_algorithm(texto, 61, 53);
	return 0;	
}
