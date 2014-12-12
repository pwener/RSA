#include "rsa.h"

int main(){
	char *text_reference = get_text_by_file((char*)"messages/encrypted.txt");
	
	Public_Key* public_key = (Public_Key*) malloc(sizeof(Public_Key));
	
	long long int rsa_modulus = 0;
	long long int coprime = 0;
	long long int modular_multiplicative_inverse = 0;

	FILE *public_key_file = fopen("keys/public_key.txt", "r");
	fscanf(public_key_file, "%lld %lld", &rsa_modulus, &coprime);
	fclose(public_key_file);

	public_key->rsa_modulus = rsa_modulus;
	public_key->coprime = coprime;
	
	printf("%lld\n", rsa_modulus);
	printf("%lld\n", coprime);

	int size = file_size("messages/encrypted.txt");
	char *encrypted_text = (char*) malloc(sizeof(char)* size);
	brute_force(text_reference, public_key);
	return 0;
}
