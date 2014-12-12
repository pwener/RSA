#include "rsa.h"

int main() {
	Pair_of_Keys* pk = generate_keys(61, 53);
	char* string = (char*) malloc(100*sizeof(char));
	fgets(string, 100, stdin);
	string[strlen(string) - 1] = '\0';
	char* texto_criptografado;
	char* texto_decifrado;	
	texto_criptografado = encrypt(string, pk->public_key);
	printf("%s\n", texto_criptografado);
	texto_decifrado = decrypt(texto_criptografado, pk->private_key, pk->public_key);
	printf("%s\n", texto_decifrado);
	return 0;
}
