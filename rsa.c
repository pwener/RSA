#include "rsa.h"
#include <string.h>

Pair_of_Keys* generate_keys(long long int first_prime, long long int second_prime)
{
	long long int rsa_modulus = first_prime * second_prime;
	long long int euler_totient = (first_prime - 1) * (second_prime - 1);
	long long int coprime = find_coprime(euler_totient);
	long long int modular_multiplicative_inverse = find_modular_multiplicative_inverse(coprime, euler_totient);		
	Public_Key* public_key = (Public_Key*) malloc(sizeof(Public_Key));
	Private_Key* private_key = (Private_Key*) malloc(sizeof(Private_Key));
	public_key->rsa_modulus = rsa_modulus;	
	public_key->coprime = coprime;
	private_key->rsa_modulus = rsa_modulus;
	private_key->modular_multiplicative_inverse = modular_multiplicative_inverse;
	Pair_of_Keys* keys = (Pair_of_Keys*) malloc(sizeof(Pair_of_Keys));
	keys->private_key = private_key;
	keys->public_key = public_key;
	return keys;
}

long long int find_coprime(long long int euler_totient) 
{
	srand(time(NULL));
	long long int coprime = 2;
	do {
		coprime++;
	} while (great_common_divisor(euler_totient, coprime) != 1); 
	return coprime;
}

long long int great_common_divisor(long long int first_number, long long int second_number) 
{
	if (second_number == 0)
		return first_number;
	else
		return great_common_divisor(second_number, first_number % second_number);
}

long long int find_modular_multiplicative_inverse(long long int coprime, long long int euler_totiente)
{
	long long int i, modular_inverse = 0;	
	for (i = 1; i < euler_totiente; i++) {
		if ((i * coprime - 1) % euler_totiente == 0) {
			modular_inverse = i;			
			break;
		}
	}
	return modular_inverse;
}

char* encrypt(char* pure_text, Public_Key* key)
{
	long long int i, j, k;
	for (i = 0; pure_text[i]; i++);
	long long int* encrypted_values = (long long int*) malloc(i * sizeof(long long int));	
	long long int modulus_size = get_magnitude(key->rsa_modulus);
	char* encrypted_string = (char*) malloc(modulus_size * strlen(pure_text) * sizeof(char));  
	char* aux = (char*) malloc(modulus_size * sizeof(char));
	for (i = 0; pure_text[i]; i++) {
		encrypted_values[i] = exponential_modulus(pure_text[i], key->coprime, key->rsa_modulus);				
		//printf("encrypted_values[%lld] = %lld\n", i, encrypted_values[i]);	
	}
	
	for (i = 0, k = 0; pure_text[i]; i++) {
		for (j = modulus_size; j > get_magnitude(encrypted_values[i]); j--)
			encrypted_string[k++] = '0';
		sprintf(aux, "%lld", encrypted_values[i]);

		for (j = 0; aux[j]; j++)
			encrypted_string[k++] = aux[j];
	}
	encrypted_string[k] = '\0';

	if(strlen(encrypted_string)>70)
	{
		printf("\n%.70s\n(...+%d", encrypted_string, (encrypted_string-70));		
		printf(" numbers)\n", encrypted_string, (encrypted_string-70));		
	}

	free(aux);
	free(encrypted_values);		
	return encrypted_string;
}

char* decrypt(char* encrypted_text, Private_Key* private_key, Public_Key* public_key, Boolean show_info)
{
	int i = 0, j = 0, k = 0, l = 0;
	int magnitude = get_magnitude(public_key->rsa_modulus);
	int length = (strlen(encrypted_text)) / magnitude;
	char* decrypted_text = (char*) malloc((strlen(encrypted_text) / magnitude + 1) * sizeof(char));
	long long int* decrypted_values = (long long int*) malloc((strlen(encrypted_text) / magnitude + 1) * sizeof(long long int));
	char* aux = (char*) malloc((magnitude + 1) * sizeof(char));
	aux[magnitude] = '\0';

	for (i = 0; encrypted_text[i]; i += magnitude) {
		k = 0;
		for (j = i; j < (i + magnitude); j++)
			aux[k++] = encrypted_text[j];
		decrypted_values[l++] = atoi(aux);
	}
	for (i = 0; i < l; i++) {
		decrypted_text[i] = exponential_modulus(decrypted_values[i], private_key->modular_multiplicative_inverse, public_key->rsa_modulus);
		
		if(show_info==TRUE)
		{
			printf("[%d%%] \tDecrypting...\n", ((int)(i*100)/l));
		}
	}
	if(show_info==TRUE)
	{
		printf("[100%%]\tDecrypted\n");
	}

	decrypted_text[i] = '\0';
	free(aux);
	free(decrypted_values);
	return decrypted_text;
}

void brute_force(char* encrypted_text, Public_Key* public_key)
{
	char** dictionary = get_dictionary();
	Boolean found = FALSE;	
	long long int key = 0;
	int frequency_of_success = 0;
	int number_of_words = 0;
	float quantity_of_words = strlen(encrypted_text)/get_magnitude(public_key->rsa_modulus)+1;
	char delimiters[8] = " .,!?\"'";
	// Cada letra corresponde a magnitude de publick_key->rsa_modulus
	char* decrypted_text = (char*) malloc(quantity_of_words*sizeof(char));
	char* aux = (char*) malloc(quantity_of_words*sizeof(char));
	char* token;
	char* tokens[2000];
	int dicionary_lines = numberoflines(fopen("dicionario.pt.txt", "r"));
	Private_Key *private_key = (Private_Key*) malloc(sizeof(Private_Key));
	private_key->rsa_modulus = public_key->rsa_modulus;
	while(!found)
	{
		printf("\nAttempting the Private Key >> %lld\n", key);
		//Descriptografa o texto
		private_key->modular_multiplicative_inverse = key;
		decrypted_text = decrypt(encrypted_text, private_key, public_key,FALSE);
		number_of_words = 0;
		strcpy(aux, decrypted_text);
		token = strtok(decrypted_text, delimiters);
		while (token != NULL)
		{
			tokens[number_of_words++] = token;
			token = strtok(NULL, delimiters);
		}
		int i, j;
		for (i = 0; i < number_of_words; i++)
		{
				for (j = 0; j < dicionary_lines; j++) 
				{		
						if(strlen(tokens[i]) > MAX_WORD_LENGHT){
							break;
						}
						if (compare_strings(tokens[i], dictionary[j]))
						{
							frequency_of_success++;
							break;
						}
				}
				if (frequency_of_success >= 0.8 * number_of_words) 
				{
							printf("\n\n\n\n*.*.*.*.*.* ...80%c of Warranty Reached... *.*.*.*.*.*\n", '%');
							printf("\n\n PRIVATE KEY FOUNDED: %lld\n\n", key);
							printf("Decrypted Message >> \n%s\n", aux);				
							found = TRUE;
							break;
				}
		}
		frequency_of_success = 0;
		key++;
	}
}
