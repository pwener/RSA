#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <stdio.h>
#include <stdlib.h>
#include "text.h"

typedef enum Main_Option
{
	CONTINUE,
	QUIT
}Main_Opt;

typedef enum Type_Option
{
	NONE,
	RSA,
	MSR
}Type_Opt;

typedef enum Miller_Selfridge_Rabin_Option
{
	MSRCONTINUE,
	MSRPREVIOUS
}MSR_Opt;

typedef enum Text_Option
{
	TXTNONE,
	TXTFILE,
	TXTUSER,
	TXTPREVIOUS
}Text_Opt;

typedef enum RSA_Option
{
	RSANONE,
	RSAPRIME,
	RSAENCRYPT,
	RSADECRYPT,
	RSAPREVIOUS
}RSA_Opt;

typedef struct Options
{
	Main_Option main;
	Type_Option type;
	Miller_Selfridge_Rabin_Option msr;
	Text_Option text;
	RSA_Option rsa;
}Options;

Options run_functions(Options previous_options);
Options run_rsa_functions(Options previous_options);
Options run_msr_functions(Options previous_options);

Options get_standard_options_values();
Options receive_type_option(Options previous_options);
Options receive_text_upload_option(Options previous_options);
Options receive_text_by_file(Options previous_options);
Options receive_text_by_user(Options previous_options);
Options receive_rsa_option(Options previous_options);

void print_authors();
void print_institute();

void clear_view();
void press_any_key();
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

void inform_unknown_error();

#endif // CONSOLE_H_