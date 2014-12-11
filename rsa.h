#ifndef RSA_H_
#define RSA_H_

#include "msr.h"
#include <time.h>

void rsa_algorithm(char* text, int first_prime, int second_prime);
int read_number() 
int find_coprime(int euler_totient) 
int great_common_divisor(int first_number, int second_number) 
int find_modular_multiplicative_inverse(int coprime, int euler_totient)
void encrypt(char* pure_text, Public_Key key)
void decrypt(char* encrypted_text, Private_Key key)

typedef struct public_key {
	int rsa_modulus;
	int coprime;
} Public_Key;

typedef struct private_key {
	int rsa_modulus;
	int modular_multiplicative_inverse;
} Private_Key;

#endif // RSA_H_