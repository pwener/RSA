#include "msr.h"
#include <time.h>

typedef struct public_key {
	int rsa_modulus;
	int coprime;
} Public_Key;

typedef struct private_key {
	int rsa_modulus;
	int modular_multiplicative_inverse;
} Private_Key;

void rsa(char* text, int first_prime, int second_prime)
{
	int rsa_modulus = first_prime * second_prime;
	int euler_totient = (first_prime - 1) * (second_prime - 1);
	int coprime = find_coprime(euler_totient);
	int modular_multiplicative_inverse = find_modular_multiplicative_inverse(coprime, euler_totient);		
	Public_Key public_key = malloc(sizeof(Public_Key));
	Private_Key private_key = malloc(sizeof(Private_Key));
	public_key->rsa_modulus = rsa_modulus;	
	public_key->coprime = coprime;
	private_key->rsa_modulus = rsa_modulus;
	private_key->modular_multiplicative_inverse = modular_multiplicative_inverse;		
}

int read_number() 
{
	int number = malloc(sizeof(int));
	Boolean valid_input = FALSE;
	do
	{
		printf("Please, insert a prime number: ");
		scanf("%d", &number);
		if (test_primality_msr(number) == TRUE)
			valid_input = TRUE;
	} while(!valid_input);
	return number;
}

int find_coprime(int euler_totient) 
{
	srand(time(NULL));
	int coprime;
	do {
		coprime = 2 + rand() % (euler_totient);
	} while (great_common_divisor(euler_totient, coprime) != 1)); 
	return coprime;
}

int great_common_divisor(int first_number, int second_number) 
{
	if (second_number == 0)
		return first_number;
	else
		return great_common_divisor(second_number, first_number % second_number);
}

int find_modular_multiplicative_inverse(int coprime, int euler_totiente) {
	int modular_inverse = 0;	
	for (int i = 1; i < euler_totiente; i++) {
		if ((i * coprime - 1) % euler_totiente == 0) {
			modular_inverse = i;			
			break;
		}
	}
	return modular_inverse;
}

void encrypt(char* pure_text, Public_Key key) {
	
}

void decrypt(char* encrypted_text, Private_Key key) {
	
}

