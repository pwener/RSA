#ifndef RSA_H_
#define RSA_H_

#include "modulus.h"
#include "text.h"
#include "msr.h"
#include "algebra.h"
#include <time.h>

typedef struct public_key {
	long long int rsa_modulus;
	long long int coprime;
} Public_Key;

typedef struct private_key {
	long long int rsa_modulus;
	long long int modular_multiplicative_inverse;
} Private_Key;

typedef struct pair_of_keys {
	Private_Key* private_key;
	Public_Key* public_key;
} Pair_of_Keys;

Pair_of_Keys* generate_keys(long long int first_prime, long long int second_prime);
long long int read_number();
long long int find_coprime(long long int euler_totient);
long long int great_common_divisor(long long int first_number, long long int second_number);
long long int find_modular_multiplicative_inverse(long long int coprime, long long int euler_totient);
char* encrypt(char* pure_text, Public_Key* key);
void brute_force(char* encrypted_text, Public_Key* public_key);
char* decrypt(char* encrypted_text, Private_Key* private_key, Public_Key* public_key, Boolean show_info);
#endif // RSA_H_
