#include "console.h"

// Run Methods

Options run_functions(Options previous_options)
{
	clear_view();
	Options options = previous_options;
	if(options.type == RSA)
	{
		options = run_rsa_functions(options);
	}
	else if(options.type == TYPMSR)
	{
		options = run_msr_functions(options);
	}
	else if(options.type == NONE)
	{
		inform_header();
		inform_about();
		press_enter();
		inform_type_option();
		options = receive_type_option(options);
	}
	return options;
}

Options run_rsa_functions(Options previous_options)
{
	Options options = previous_options;
	if(options.rsa == RSAGENKEYS)
	{
		options = run_key_functions(options);
	}
	else if(options.rsa == RSASEEKEYS)
	{
		options = run_see_keys_functions(options);
	}
	else if(options.rsa == RSAENCRYPT)
	{
		options = run_encrypt_functions(options);
	}
	else if(options.rsa == RSADECRYPT)
	{
		options = run_decrypt_functions(options);
	}
	else if(options.rsa == RSAHACK)
	{
		options = run_hack_functions(options);
	}
	else if(options.rsa == RSASEETXT)
	{
		see_current_text();
		options.rsa = RSANONE;
	}
	else if(options.rsa == RSANONE)
	{
		if(options.text == TXTSUCCESS)
		{
			inform_rsa_option();
			options = receive_rsa_option(options);
		}
		else if(options.text == TXTFILE)
		{
			explain_text_upload_by_file();
			options = receive_text_by_file(options);
		}
		else if(options.text == TXTUSER)
		{
			explain_text_upload_by_user();
			options = receive_text_by_user(options);
		}
		else if(options.text == TXTONE)
		{
			options = receive_example_text(options);
		}
		else if(options.text == TXTTWO)
		{
			options = receive_example_text(options);
		}
		else if(options.text == TXTTRE)
		{
			options = receive_example_text(options);
		}
		else if(options.text == TXTFOU)
		{
			options = receive_example_text(options);
		}
		else if(options.text == TXTFIV)
		{
			options = receive_example_text(options);
		}
		else if(options.text == TXTSIX)
		{
			options = receive_example_text(options);
		}
		else if(options.text == TXTNONE)
		{
			inform_text_upload_option();
			options = receive_text_upload_option(options);
		}
		else if(options.text == TXTPREVIOUS)
		{
			options.text = TXTNONE;
			options.type = NONE;
		}
	}
	else if(options.rsa == RSAPREVIOUS)
	{
		options.text = TXTNONE;
		options.rsa = RSANONE;
	}
	return options;
}

Options run_msr_functions(Options previous_options)
{
	Options options = previous_options;
	
	if(options.msr == MSRTEST)
	{
		options = run_test_primality(options);
	}
	else if(options.msr == MSRNONE)
	{
		explain_miller_selfridge_rabin();
		options = receive_msr_option(options);
	}
	else if(options.msr == MSRPREVIOUS)
	{
		options.msr = MSRNONE;
		options.type = NONE;
	}

	return options;
}

Options run_test_primality(Options previous_options)
{
	Options options = previous_options;
	inform_number_to_check_primality();
	unsigned int possibly_prime_number = receive_number_from_user();
	Boolean is_number_prime = test_primality_msr(possibly_prime_number);

	if(is_number_prime==TRUE)
	{
		inform_its_prime(possibly_prime_number);
	}
	else if(is_number_prime==FALSE)
	{
		inform_its_composite(possibly_prime_number);
	}

	options.msr = MSRNONE;

	press_enter();
	
	return options;
}

Options run_key_functions(Options previous_options)
{
	Options options = previous_options;

	if(options.gen_key == GKGEN)
	{
		explain_primes_to_generate_key();
		options = run_generate_key(options);
	}
	else if(options.gen_key == GKNONE)
	{
		explain_key_generation();
		options = receive_key_option(options);
	}
	else if(options.gen_key == GKPREVIOUS)
	{
		options.gen_key = GKNONE;
		options.rsa = RSANONE;
	}

	return options;
}

Options run_generate_key(Options previous_options)
{
	Options options = previous_options;

	Two_Natural_Numbers prime_numbers = receive_prime_numbers();
	press_enter();

	if(prime_numbers.first_number == 1 || prime_numbers.second_number == 1)
	{
		options = get_standard_options_values();
	}
	else
	{
		Pair_of_Keys* pair_of_keys = generate_keys(prime_numbers.first_number,
			prime_numbers.second_number);

		export_keys_to_file(pair_of_keys);

		press_enter();

		options = run_see_key(options);

		options.gen_key = GKPREVIOUS;
	}

	return options;
}


Options run_see_keys_functions(Options previous_options)
{
	Options options = previous_options;

	if(options.see_key == SKSEE)
	{
		options = run_see_key(options);
	}
	else if(options.see_key == SKNONE)
	{
		explain_see_keys();
		options = receive_see_keys_option(options);
	}
	else if(options.see_key == SKPREVIOUS)
	{
		options.see_key = SKNONE;
		options.rsa = RSANONE;
	}

	return options;
}

Options run_see_key(Options previous_options)
{
	Options options = previous_options;

	inform_keys_to_user();

	press_enter();

	options.see_key = SKPREVIOUS;

	return options;
}


Options run_encrypt_functions(Options previous_options)
{
	Options options = previous_options;
	char *text_reference = get_text_by_file((char*)"text/exported.txt");

	Pair_of_Keys *pair_of_keys = get_pair_of_keys();

	print_hline();
	printf("\n\t\t\tEncrypted Text with RSA\n");
	printf("\t\t\tPublic Key Used: %d %d\n", pair_of_keys->public_key->rsa_modulus, pair_of_keys->public_key->coprime);
	print_hline();
	char *text_encrypted = encrypt(text_reference,pair_of_keys->public_key);
	print_hline();

	Boolean is_exportation_worked_fine = export_text_to_file(text_encrypted,
		(char*)"messages/encrypted.txt");
	if(is_exportation_worked_fine == TRUE)
	{
		inform_text_is_fine();
		press_enter();
	}
	else if(is_exportation_worked_fine == FALSE)
	{
		inform_unknown_error();
		press_enter();
	}

	free(text_reference);
	free(text_encrypted);

	options.rsa = RSANONE;

	return options;
}

Options run_decrypt_functions(Options previous_options)
{
	Options options = previous_options;
	char *text_reference = get_text_by_file((char*)"messages/encrypted.txt");

	Pair_of_Keys *pair_of_keys = get_pair_of_keys();

	char *text_decrypted = decrypt(text_reference,pair_of_keys->private_key,pair_of_keys->public_key,TRUE);

	Boolean is_exportation_worked_fine = export_text_to_file(text_decrypted,
		(char*)"messages/decrypted.txt");
	if(is_exportation_worked_fine == TRUE)
	{
		inform_text_is_fine();
		press_enter();
	}
	else if(is_exportation_worked_fine == FALSE)
	{
		inform_unknown_error();
		press_enter();
	}

	free(text_reference);
	free(text_decrypted);
	options.rsa = RSANONE;
	return options;
}

Options run_hack_functions(Options previous_options)
{
	Options options = previous_options;
	char *text_reference = get_text_by_file((char*)"messages/encrypted.txt");
	Pair_of_Keys *pair_of_keys = get_pair_of_keys();
	Public_Key *public_key = pair_of_keys->public_key;

	printf("The Public Key Received Is: [%d %d]", public_key->rsa_modulus, public_key->coprime);
	press_enter();
	brute_force(text_reference, public_key);
	press_enter();

	options.rsa = RSANONE;
	return options;	
}


// Option Methods

Options get_standard_options_values()
{
	Options options;
	options.main = CONTINUE;
	options.type = NONE;
	options.text = TXTNONE;
	options.msr = MSRNONE;
	options.rsa = RSANONE;
	options.gen_key = GKNONE;
	options.see_key = SKNONE;
	return options;
}

Options receive_type_option(Options previous_options)
{
	Options options = previous_options;
	int input = 10;
	print_response_symbol();
	scanf("%d", &input);
	getchar();
	switch(input)
	{
		case 1:
			options.type = RSA;
		break;

		case 2:
			options.type = TYPMSR;
		break;

		case 0:
			options.main = QUIT;
		break;

		default:
			options.type = NONE;
		break;
	}
	return options;
}

Options receive_text_upload_option(Options previous_options)
{
	Options options = previous_options;
	int input = 10;
	print_response_symbol();
	scanf("%d", &input);
	getchar();
	switch(input)
	{
		case 1:
			options.text = TXTFILE;
		break;

		case 2:
			options.text = TXTUSER;
		break;

		case 3:
			options.text = TXTONE;
		break;

		case 4:
			options.text = TXTTWO;
		break;

		case 5:
			options.text = TXTTRE;
		break;

		case 6:
			options.text = TXTFOU;
		break;

		case 7:
			options.text = TXTFIV;
		break;

		case 8:
			options.text = TXTSIX;
		break;

		case 9:
			options.text = TXTPREVIOUS;
		break;

		case 0:
			options.main = QUIT;
		break;

		default:
			options.text = TXTNONE;
		break;
	}
	return options;
}

Options receive_text_by_file(Options previous_options)
{
	Options options = previous_options;
	print_response_symbol();
	char* path_input = receive_string_from_user(80);
	char* text_input = get_text_by_file(path_input);
	if(text_input==NULL)
	{
		inform_wrong_path();
		press_enter();
	}
	else
	{
		Boolean is_exportation_worked_fine = export_text_to_file(text_input,(char*)"text/exported.txt");
		if(is_exportation_worked_fine == TRUE)
		{
			inform_text_is_fine();
			press_enter();
			options.text = TXTSUCCESS;
			options.rsa = RSASEETXT;
		}
		else if(is_exportation_worked_fine == FALSE)
		{
			inform_unknown_error();
			press_enter();
			options.text = TXTNONE;
		}
	}
	free(path_input);
	free(text_input);
	return options;
}

Options receive_text_by_user(Options previous_options)
{
	Options options = previous_options;
	print_response_symbol();
	char* text_input = receive_string_from_user(500);
	Boolean is_exportation_worked_fine = export_text_to_file(text_input,(char*)"text/exported.txt");
	if(is_exportation_worked_fine == TRUE)
	{
		inform_text_is_fine();
		press_enter();
		options.text = TXTSUCCESS;
		options.rsa = RSASEETXT;
	}
	else if(is_exportation_worked_fine == FALSE)
	{
		inform_unknown_error();
		press_enter();
	}

	return options;
}

Options receive_example_text(Options previous_options)
{
	Options options = previous_options;
	char* example_text;
	switch(options.text)
	{
		case TXTONE:
			example_text = get_text_by_file((char*)"examples/the_little_prince_pt.txt");
		break;

		case TXTTWO:
			example_text = get_text_by_file((char*)"examples/harry_potter_pt.txt");
		break;

		case TXTTRE:
			example_text = get_text_by_file((char*)"examples/sidereus_nuncius_pt.txt");
		break;

		case TXTFOU:
			example_text = get_text_by_file((char*)"examples/dostoievski_pt.txt");
		break;

		case TXTFIV:
			example_text = get_text_by_file((char*)"examples/love_spotted_pt.txt");
		break;

		case TXTSIX:
			example_text = get_text_by_file((char*)"examples/the_beatles_pt.txt");
		break;
	}
	Boolean is_exportation_worked_fine = export_text_to_file(example_text,(char*)"text/exported.txt");
	if(is_exportation_worked_fine == TRUE)
	{
		inform_text_is_fine();
		press_enter();
		options.text = TXTSUCCESS;
		options.rsa = RSASEETXT;
	}
	else if(is_exportation_worked_fine == FALSE)
	{
		inform_unknown_error();
		press_enter();
		options.text = TXTNONE;
	}
	return options;
}

Options receive_rsa_option(Options previous_options)
{
	Options options = previous_options;
	int input = 10;
	print_response_symbol();
	scanf("%d", &input);
	getchar();
	switch(input)
	{
		case 1:
			options.rsa = RSAGENKEYS;
		break;

		case 2:
			options.rsa = RSASEEKEYS;
		break;

		case 3:
			options.rsa = RSAENCRYPT;
		break;

		case 4:
			options.rsa = RSADECRYPT;
		break;

		case 5:
			options.rsa = RSAHACK;
		break;

		case 6:
			options.rsa = RSASEETXT;
		break;

		case 9:
			options.rsa = RSAPREVIOUS;
		break;

		case 0:
			options.main = QUIT;
		break;

		default:
			options.rsa = RSANONE;
		break;
	}
	return options;	
}

Options receive_key_option(Options previous_options)
{
	Options options = previous_options;

	int input = 10;
	print_response_symbol();
	scanf("%d", &input);
	getchar();
	switch(input)
	{
		case 1:
			options.gen_key = GKGEN;
		break;

		case 2:
			options.rsa = RSASEEKEYS;
			options.gen_key = GKNONE;
			options.see_key = SKSEE;
		break;

		case 9:
			options.gen_key = GKPREVIOUS;
		break;

		case 0:
			options.main = QUIT;
		break;

		default:
			options.gen_key = GKNONE;
		break;
	}

	return options;
}

Options receive_see_keys_option(Options previous_options)
{
	Options options = previous_options;

	int input = 10;
	print_response_symbol();
	scanf("%d", &input);
	getchar();
	switch(input)
	{
		case 1:
			options.see_key = SKSEE;
		break;

		case 2:
			options.rsa = RSAGENKEYS;
			options.see_key = SKNONE;
			options.gen_key = GKGEN;
		break;

		case 9:
			options.see_key = SKPREVIOUS;
		break;

		case 0:
			options.main = QUIT;
		break;

		default:
			options.see_key = SKNONE;
		break;
	}

	return options;
}

Options receive_msr_option(Options previous_options)
{
	Options options = previous_options;
	int input = 10;
	print_response_symbol();
	scanf("%d", &input);
	getchar();
	switch(input)
	{
		case 1:
			options.msr = MSRTEST;
		break;

		case 9:
			options.msr = MSRPREVIOUS;
		break;

		case 0:
			options.main = QUIT;
		break;

		default:
			options.msr = MSRNONE;
		break;
	}
	return options;	
}

unsigned long long int receive_number_from_user()
{
	unsigned long long int input = 1;
	print_response_symbol();
	scanf("%lld", &input);
	getchar();
	return input;
}

Two_Natural_Numbers receive_prime_numbers()
{
	Two_Natural_Numbers prime_numbers;

	prime_numbers.first_number = receive_number_from_user();
	prime_numbers.second_number = receive_number_from_user();

	Boolean is_first_number_prime = test_primality_msr(prime_numbers.first_number);
	Boolean is_second_number_prime = test_primality_msr(prime_numbers.second_number);
	Boolean is_both_numbers_primes = FALSE;

	if(is_first_number_prime == TRUE && is_second_number_prime == TRUE)
	{
		is_both_numbers_primes = TRUE;
	}
	else
	{
		if(is_first_number_prime == FALSE)
		{
			inform_its_composite(prime_numbers.first_number);
		}

		if(is_second_number_prime == FALSE)
		{
			inform_its_composite(prime_numbers.second_number);
		}
		prime_numbers.first_number = 1;
		prime_numbers.second_number = 1;
	}

	return prime_numbers;
}

Pair_of_Keys* get_pair_of_keys()
{
	Public_Key* public_key = (Public_Key*) malloc(sizeof(Public_Key));
	Private_Key* private_key = (Private_Key*) malloc(sizeof(Private_Key));

	long long int rsa_modulus = 0;
	long long int coprime = 0;
	long long int modular_multiplicative_inverse = 0;

	FILE *public_key_file = fopen("keys/public_key.txt", "r");
	fscanf(public_key_file, "%lld %lld", &rsa_modulus, &coprime);
	fclose(public_key_file);

	FILE *private_key_file = fopen("keys/private_key.txt", "r");
	fscanf(private_key_file, "%lld %lld", &rsa_modulus, &modular_multiplicative_inverse);
	fclose(private_key_file);

	public_key->rsa_modulus = rsa_modulus;
	public_key->coprime = coprime;
	private_key->rsa_modulus = rsa_modulus;
	private_key->modular_multiplicative_inverse = modular_multiplicative_inverse;

	Pair_of_Keys* pair_of_keys = (Pair_of_Keys*) malloc(sizeof(Pair_of_Keys));
	pair_of_keys->public_key = public_key;
	pair_of_keys->private_key = private_key;

	return pair_of_keys;
}


void export_keys_to_file(Pair_of_Keys* pair_of_keys)
{
	FILE *standard_public_key_file = fopen("keys/public_key.txt", "w");
	fprintf(standard_public_key_file, "%lld %lld",
		pair_of_keys->public_key->rsa_modulus, pair_of_keys->public_key->coprime);
	fclose(standard_public_key_file);

	FILE *standard_private_key_file = fopen("keys/private_key.txt", "w");
	fprintf(standard_private_key_file, "%lld %lld",
		pair_of_keys->private_key->rsa_modulus,
		pair_of_keys->private_key->modular_multiplicative_inverse);
	fclose(standard_private_key_file);
}

// Header Procedures

void print_authors()
{
	printf("\nAuthors:\n");
	printf("\tJonathan Henrique Maia de Moraes\t12/0122553\n");
	printf("\tPedro de Lyra Pereira\t\t\t11/0135725\n");
	printf("\tPhelipe Wener Pereira Mota\t\t12/0132893\n");
}

void print_institute()
{
	printf("\t\tUniversity of Brasilia - Brazil\n");
	printf("\t\t\tUnB Gama College\n");
	printf("\t\tDegree in Software Engineering\n");
	printf("\tCourse of Mathematical Structures for Computer\n");
}

// General Procedures

void clear_view()
{
	printf("\n\n\n \n\n\n \n\n\n \n");
	printf("\n\n\n \n\n\n \n\n\n \n");
	printf("\n\n\n \n\n\n \n\n\n \n");
	printf("\n\n\n \n\n\n \n\n\n \n");
	printf("\n\n\n \n\n\n \n\n\n \n");
	printf("\n\n\n \n\n\n \n\n\n \n");
}

void press_enter()
{
	printf("\t\t\tPress ENTER To Continue...\n");
	getchar();
	clear_view();
}

void print_hline()
{
	printf("\n================================");
	printf("======================================\n");
}

void print_choose()
{
	printf("Choose One Option Below:\n");
}

void print_previous()
{
	printf("\t[9] Previous\n");
}

void print_quit()
{
	printf("\t[0] Quit\n");
}

void print_response_symbol()
{
	printf(">\t");
}

// Main Informations Procedures

void inform_about()
{
	print_hline();
	printf("\t\t\tWelcome to the RSA Cryptosystem!\n");
	printf("\tThis Software realize the RSA Encryption and Decryption\n");
	printf("\tand implements a rustic algorithm who tries to solve the\n");
	printf("\tRSA without knowing the public and private keys.\n");
	print_hline();
}

void inform_header()
{
	print_hline();
	print_institute();
	print_authors();
	print_hline();
}

void inform_type_option()
{
	print_hline();
	print_choose();
	printf("\t[1] Use RSA Algorithm\n");
	printf("\t[2] Check Primality Of A Number\n");
	print_quit();
	print_hline();
}

// RSA [1] Text Importation Procedures

void inform_text_upload_option()
{
	print_hline();
	print_choose();
	printf("\t[1] Upload a Text File\n");
	printf("\t[2] Inform Your Own Text\n");
	printf("\t[3] Utilizar Exemplo: O Pequeno Principe (Antoine de Saint-Exupery)\n");
	printf("\t[4] Utilizar Exemplo: Harry Potter (JK Rowling)\n");
	printf("\t[5] Utilizar Exemplo: Sidereus Nuncius (Galileu)\n");
	printf("\t[6] Utilizar Exemplo: Crime e Castigo (Dostoievski)\n");
	printf("\t[7] Utilizar Exemplo: Spotted (Desconhecido)\n");
	printf("\t[8] Utilizar Exemplo: A Day In The Life (The Beatles)\n");
	print_previous();
	print_quit();
	print_hline();
}

void explain_text_upload_by_file()
{
	print_hline();
	printf("Please inform the path of the file (based on current folder)\n");
	printf("Example: messages/foo.txt\n");
}

void explain_text_upload_by_user()
{
	print_hline();
	printf("Please write your text\n");
}

void inform_wrong_path()
{
	printf("\t\t\n[ERROR]\tThe file could not be found!");
	print_hline();
}

void inform_text_is_fine()
{
	printf("\n\t\t[Yiikies!]\tThe text was succesfully imported!");
	print_hline();
}

void inform_rsa_option()
{
	print_hline();
	print_choose();
	printf("\t[1] Generate New Keys\n");
	printf("\t[2] See Your Keys\n");
	printf("\t[3] Encrypt the Text\n");
	printf("\t[4] Decrypt the Text\n");
	printf("\t[5] Try to Hack an Encrypted Text\n");
	printf("\t[6] See The Current Exported Text\n");
	print_previous();
	print_quit();
	print_hline();
}

void see_current_text()
{
	char* current_text = get_text_by_file((char*)"text/exported.txt");
	print_hline();
	printf("\n\t\tActual Exported Text\n");
	print_hline();
	printf("%s", current_text);
	print_hline();
	press_enter();
}

void explain_rivest_shamir_adleman()
{
	print_hline();
	printf("\tThe RSA is a public-key cryptosystem widely used\n");
	printf("\tfor secure data trasnsmission. It works with two keys:\n");
	printf("\tThe Public Key, a.k.a Encryption Key, can be known by\n");
	printf("\teveryone and is used for encrypting messages. The Private\n");
	printf("\tKey, a.k.a. Decryption Key, is secret and can decrypt the\n");
	printf("\tthe message encrypted by the Public Key. Both keys are generated\n");
	printf("\twith two prime numbers! Or at least high enough to be confused as\n");
	printf("\tone. This software can easily deal with numbers in 999 order, but\n");
	printf("\tis not safe above this.\n\n");
	print_hline();
}

void explain_key_generation()
{
	print_hline();
	printf("\tTo encrypt and decrypt using RSA Cryptosystem is required\n");
	printf("\ttwo Keys (Public - shared by all, Private - keeped in secret)\n");
	printf("\tgenerated with Modular Arithmetics using two prime numbers.\n");
	printf("\tYou'll be asked to put two natural numbers, keep in mind they\n");
	printf("\tneed to be primes, and will be tested with MSR Primality Test.\n\n");
	print_choose();
	printf("\t[1] Generate New Keys\n");
	printf("\t[2] See Your Keys\n");
	print_previous();
	print_quit();
	print_hline();
}

void explain_primes_to_generate_key()
{
	print_hline();
	printf("\tPlease, inform two prime numbers to generate the Public Key and\n");
	printf("\tPrivate Key. Inform the first prime number and press enter, then\n");
	printf("\tinform the second prime number and press enter.\n");
	printf("\tAs Like: <number_one><enter><number_two><enter>\n");
	printf("\tExample:\n\t\t8969\n\t\t13711\n\n");
	printf("\tNice Pairs: <13,17> <61,53> <29,19>\n\n");
}

void explain_see_keys()
{
	print_hline();
	printf("\tTo see your keys you need to generate they first. If you did not\n");
	printf("\tgenerate your keys before, just select as described below the option\n");
	printf("\tto generate public key and private key.\n\n");
	print_choose();
	printf("\t[1] See Your Keys\n");
	printf("\t[2] Generate New Keys\n");
	print_previous();
	print_quit();
	print_hline();
}

void inform_keys_to_user()
{
	Pair_of_Keys *pair_of_keys = get_pair_of_keys();
	print_hline();
	printf("\n\t\t\t\tYOUR KEYS\n");
	print_hline();
	printf("\t\tPublic Key:\t%lld %lld\n", pair_of_keys->public_key->rsa_modulus,
		pair_of_keys->public_key->coprime);
	printf("\t\tPrivate Key:\t%lld %lld\n", pair_of_keys->private_key->rsa_modulus,
		pair_of_keys->private_key->modular_multiplicative_inverse);
	print_hline();
}

void inform_encrypt_option()
{
	print_hline();
	print_choose();
	printf("\t[1] Encrypt the Current Exported Text\n");
	printf("\t[2] Modify the Current Exported Text\n");
	printf("\t[3] Read the Current Exported Text\n");
	print_previous();
	print_quit();
	print_hline();
}

void inform_decrypt_option()
{
	print_hline();
	print_choose();
	printf("\t[1] Decrypt the Current Exported Text\n");
	printf("\t[2] Modify the Current Exported Text\n");
	printf("\t[3] Read the Current Exported Text\n");
	print_previous();
	print_quit();
	print_hline();
}

void inform_hack_option()
{
	print_hline();
	print_choose();
	printf("\t[1] Try to Hack the Current Exported Text\n");
	printf("\t[2] Modify the Current Exported Text\n");
	printf("\t[3] Read the Current Exported Text\n");
	printf("\t[4] Encrypt and Try to Hack the Current Exported Text\n");
	print_previous();
	print_quit();
	print_hline();
}

void inform_result_encrypt()
{
	print_hline();
	printf("\t\t\tMESSAGE ENCRYPTED!\n");
	print_hline();
	printf("\n\n");
	printf("\t The Prime  is: %s", get_text_by_file((char*)"keys/public_key.txt"));
	printf("\t The Private Key is: %s", get_text_by_file((char*)"keys/private_key.txt"));
	printf("%s", get_text_by_file((char*)"output/encrypted_text.txt"));
	printf("\n\n");
}

void explain_miller_selfridge_rabin()
{
	print_hline();
	printf("\tThis Primality Test use the Algorithm MSR\n");
	printf("\t(Miller-Selfridge-Rabin) to check if a number\n");
	printf("\tis prime or composite, with an accuracy of 100%%\n");
	printf("\tif it is a prime number, and 25%% if is a composite\n");
	printf("\tnumber.\n");
	print_choose();
	printf("\t[1] Check if a Number is Prime or Composite\n");
	print_previous();
	print_quit();
	print_hline();
}

void inform_number_to_check_primality()
{
	print_hline();
	printf("Please inform a number to check if it is prime or\n");
	printf("composite.\n");
	printf("Example: 8123 (it's prime), 9327 (it's composite)\n");
}

void inform_its_prime(unsigned long long int prime_number)
{
	printf("\n->\tThe Number [%lld] is Prime!\n", prime_number);
	print_hline();
}

void inform_its_composite(unsigned long long int composite_number)
{
	printf("\n->\tThe Number [%lld] is Composite!\n", composite_number);
	print_hline();
}

void inform_unknown_error()
{
	printf("[ERROR]\tWell, im sorry about that, but some\n");
	printf("unknown force striked against this software. :(\n");
}