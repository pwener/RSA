#include "rsa.h"

void rsa_algorithm(char* text, int first_prime, int second_prime)
{
	int rsa_modulus = first_prime * second_prime;
	int euler_totient = (first_prime - 1) * (second_prime - 1);
	int coprime = find_coprime(euler_totient);
	int modular_multiplicative_inverse = find_modular_multiplicative_inverse(coprime, euler_totient);		
	Public_Key* public_key = (Public_Key*) malloc(sizeof(Public_Key));
	Private_Key* private_key = (Private_Key*) malloc(sizeof(Private_Key));
	public_key->rsa_modulus = rsa_modulus;	
	public_key->coprime = coprime;
	private_key->rsa_modulus = rsa_modulus;
	private_key->modular_multiplicative_inverse = modular_multiplicative_inverse;
	encrypt(text,public_key);
	decrypt(text,private_key,public_key);
}

int read_number() 
{
	int number = 0;
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
	int modular_inverse = 0;	
	for (int i = 1; i < euler_totiente; i++) {
		if ((i * coprime - 1) % euler_totiente == 0) {
			modular_inverse = i;			
			break;
		}
	}
	return modular_inverse;
}

void encrypt(char* pure_text, Public_Key* key)
{
	for (int i = 0; pure_text[i]; i++) {
		if (is_letter(pure_text[i]) == FALSE) continue;

		pure_text[i] = exponential_modulus(pure_text[i], key->coprime, key->rsa_modulus);				
	}
	printf("Encrypted text: %s\n\n", pure_text);
}

void decrypt(char* encrypted_text, Private_Key* private_key, Public_Key* public_key)
{
	for (int i = 0; encrypted_text[i]; i++) {
		if (is_letter(encrypted_text[i]) == FALSE) continue;
		
		encrypted_text[i] = exponential_modulus(encrypted_text[i], private_key->modular_multiplicative_inverse, public_key->rsa_modulus);
	}
	printf("Decrypted text: %s\n\n", encrypted_text);
}

void brute_force(char* encrypted_text, Public_Key* public_key)
{
	char** dictionary = get_dictionary();
	Boolean found = FALSE;	
	unsigned int key;
	int frequency_of_success = 0;
	int number_of_words = 0;
	char delimiters[7] = " .,!?\"'";
	// Cada letra corresponde a magnitude de publick_key->rsa_modulus
	char aux[strlen(encrypted_text)* get_magnitude()];
	char* token;
	char* tokens[2000];
	while(!found)
	{
		printf("Tentando a chave>> %d\n", key);
		//Descriptografa o texto
		decrypt(encrypted_text, key, public_key);
		strcpy(aux, encrypted_text);
		number_of_words = 0;
		token = strtok(aux, delimiters);
		while (token != NULL)
		{
			tokens[number_of_words++] = token;
				token = strtok(NULL, delimiters);
		}
		int i, j;
		long dicionary_lines = numberoflines(dictionary_file);
		for (i = 0; i < number_of_words; i++)
		{
				for (j = 0; j < dicionary_lines; j++) 
				{
						if (compare_strings(tokens[i], dictionary[j]))
						{
							frequency_of_success++;
							break;
						}
				}
				if ((float) frequency_of_success >= 0.8 * number_of_words) 
				{
							printf("*.*.*.*.*.* ...80%c de acerto atingido... *.*.*.*.*.*\n", '%');
							printf("\n\n CHAVE ENCONTRADA: %s\n\n", key);					
							found = true;
							break;
				}
		}
	}
}