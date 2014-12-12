#ifndef RSA_H_
#define RSA_H_

#include "rsa.h"
#include "modulus.h"
#include "text.h"
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

typedef struct pair_of_keys {
	Private_Key* private_key;
	Public_Key* public_key;
} Pair_of_Keys;

Pair_of_Keys* generate_keys(int first_prime, int second_prime);
int read_number();
int find_coprime(int euler_totient);
int great_common_divisor(int first_number, int second_number);
int find_modular_multiplicative_inverse(int coprime, int euler_totient);
char* encrypt(char* pure_text, Public_Key* key);
void decrypt(char* encrypted_text, Private_Key* private_key, Public_Key* public_key);
int integer_size(int number);

#endif // RSA_H_
