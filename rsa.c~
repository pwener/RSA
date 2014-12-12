#include "rsa.h"
#include <string.h>

Pair_of_Keys* generate_keys(int first_prime, int second_prime)
{
	int rsa_modulus = first_prime * second_prime;
	int euler_totient = (first_prime - 1) * (second_prime - 1);
	int coprime = 17;//find_coprime(euler_totient);
	int modular_multiplicative_inverse = find_modular_multiplicative_inverse(coprime, euler_totient);		
	Public_Key* public_key = (Public_Key*) malloc(sizeof(Public_Key));
	Private_Key* private_key = (Private_Key*) malloc(sizeof(Private_Key));
	Pair_of_Keys* keys = (Pair_of_Keys*) malloc(sizeof(Pair_of_Keys));
	keys->private_key = private_key;
	keys->public_key = public_key;
	public_key->rsa_modulus = rsa_modulus;	
	public_key->coprime = coprime;
	private_key->rsa_modulus = rsa_modulus;
	private_key->modular_multiplicative_inverse = modular_multiplicative_inverse;
	return keys;
}

int find_coprime(int euler_totient) 
{
	srand(time(NULL));
	int coprime = 0;
	do {
		coprime = 2 + rand() % (euler_totient);
	} while (great_common_divisor(euler_totient, coprime) != 1); 
	return coprime;
}

int great_common_divisor(int first_number, int second_number) 
{
	if (second_number == 0)
		return first_number;
	else
		return great_common_divisor(second_number, first_number % second_number);
}

int find_modular_multiplicative_inverse(int coprime, int euler_totiente)
{
	int i, modular_inverse = 0;	
	for (i = 1; i < euler_totiente; i++) {
		if ((i * coprime - 1) % euler_totiente == 0) {
			modular_inverse = i;			
			break;
		}
	}
	printf("Modular inverse: %d\n", modular_inverse);
	return modular_inverse;
}

char* encrypt(char* pure_text, Public_Key* key)
{
	int i, j, k;
	for (i = 0; pure_text[i]; i++);
	int* encrypted_values = (int*) malloc(i * sizeof(int));	
	int modulus_size = integer_size(key->rsa_modulus);
	char* encrypted_string = (char*) malloc(modulus_size * strlen(pure_text) * sizeof(char));  
	char* aux = (char*) malloc(modulus_size * sizeof(char));
	for (i = 0; pure_text[i]; i++) {
		encrypted_values[i] = exponential_modulus(pure_text[i], key->coprime, key->rsa_modulus);				
		//printf("encrypted_values[%d] = %d\n", i, encrypted_values[i]);	
	}
	
	for (i = 0, k = 0; pure_text[i]; i++) {
		printf("\nok\n");
		for (j = modulus_size; j > integer_size(encrypted_values[i]); j--)
			encrypted_string[k++] = '0';
		sprintf(aux, "%d", encrypted_values[i]);

		for (j = 0; aux[j]; j++)
			encrypted_string[k++] = aux[j];
	
	}
	encrypted_string[k++] = '\0';
	//printf("%s\n", encrypted_string);
	free(aux);
	free(encrypted_values);		
	return encrypted_string;
}

void decrypt(char* encrypted_text, Private_Key* private_key, Public_Key* public_key)
{
	int i;
	printf("\n\n\npri_key->rsa_modular = %d\tpub_key->modular_inverse = %d\n\n", public_key->rsa_modulus, private_key->modular_multiplicative_inverse);
	for (i = 0; encrypted_text[i]; i++) {
		if (is_letter(encrypted_text[i]) == FALSE) continue;
		printf("encrypted_text[%d] = %c\n", i, encrypted_text[i]);
		encrypted_text[i] = exponential_modulus(encrypted_text[i], private_key->modular_multiplicative_inverse, public_key->rsa_modulus);
	}
	printf("Decrypted text: %s\n\n", encrypted_text);
}

int integer_size(int number)
{
	int i = 1, counter = 0;
	while (number / i != 0) {
		counter++;
		i *= 10;
	}
	return counter; 
}


