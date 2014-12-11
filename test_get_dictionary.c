#include "text.h"

int main(){
	char **dictionary = get_dictionary();
	FILE *arquivo = fopen("dicionario.pt.txt", "r");
	long n = numberoflines(arquivo);
	fclose(arquivo);
	printf("\nNumber of lines>> %ld\n", n);
	int i;
	for(i = 0; i < n ; i++){
		printf("%s;", dictionary[i]);
	}
	free(dictionary);	
}
