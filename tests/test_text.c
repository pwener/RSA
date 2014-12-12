#include <stdlib.h>
#include <stdio.h>
#include "text.h"

int main(){
	long size = file_size("textoExemplo.txt");
	char * texto = malloc(size * sizeof(char));
	texto = get_text("textoExemplo.txt");
	printf("%s\n", texto);
	return 0;
}
