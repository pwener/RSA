#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <stdio.h>
#include <stdlib.h>
#include "text.h"
#include "rsa.h"

typedef enum Main_Option
{
	CONTINUE,
	QUIT
}Main_Opt;

typedef enum Type_Option
{
	NONE,
	RSA,
	TYPMSR
}Type_Opt;

typedef enum Miller_Selfridge_Rabin_Option
{
	MSRNONE,
	MSRTEST,
	MSRPREVIOUS
}MSR_Opt;

typedef enum Text_Option
{
	TXTNONE,
	TXTFILE,
	TXTUSER,
	TXTSUCCESS,
	TXTPREVIOUS
}Text_Opt;

typedef enum RSA_Option
{
	RSANONE,
	RSAENCRYPT,
	RSADECRYPT,
	RSAHACK,
	RSAPREVIOUS
}RSA_Opt;

typedef struct Options
{
	Main_Opt main;
	Type_Opt type;
	MSR_Opt msr;
	Text_Opt text;
	RSA_Opt rsa;
}Options;

Options run_functions(Options previous_options);
Options run_rsa_functions(Options previous_options);
Options run_msr_functions(Options previous_options);
Options run_test_primality(Options previous_options);
Options run_encrypt_functions(Options previous_options);
Options run_decrypt_functions(Options previous_options);
Options run_hack_functions(Options previous_options);

Options get_standard_options_values();
Options receive_type_option(Options previous_options);
Options receive_text_upload_option(Options previous_options);
Options receive_text_by_file(Options previous_options);
Options receive_text_by_user(Options previous_options);
Options receive_rsa_option(Options previous_options);
Options receive_msr_option(Options previous_options);

unsigned int receive_number_from_user();

void print_authors();
void print_institute();

void clear_view();
void press_enter();
void print_hline();
void print_choose();
void print_previous();
void print_quit();
void print_response_symbol();

void inform_about();
void inform_header();

void inform_type_option();

void inform_text_upload_option();
void explain_text_upload_by_file();
void explain_text_upload_by_user();
void inform_wrong_path();
void inform_text_is_fine();

void inform_rsa_option();

void explain_miller_selfridge_rabin();
void inform_number_desirable();
void inform_its_prime(unsigned int prime_number);
void inform_its_composite(unsigned int composite_number);

void inform_unknown_error();

#endif // CONSOLE_H_