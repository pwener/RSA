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
	else if(options.type == MSR)
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
	if(options.rsa == RSAENCRYPT)
	{
		run_encrypt_functions();
	}
	else if(options.rsa == RSADECRYPT)
	{
		run_decrypt_functions();
	}
	else if(options.rsa == RSAHACK)
	{
		run_hack_functions();
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

	unsigned int possibly_prime_number =  receive_number();
	Boolean is_number_prime = check_possibly_prime_number(possibly_prime_number);
	if(is_number_prime==TRUE)
	{
		inform_its_prime();
	}
	else if(is_number_prime==FALSE)
	{
		inform_its_composite();
	}

	options.msr = MSRNONE;
	
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
			options.type = MSR;
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
		Boolean is_exportation_worked_fine = export_text_to_file(text_input);
		if(is_exportation_worked_fine == TRUE)
		{
			inform_text_is_fine();
			press_enter();
			options.text = TXTSUCCESS;
		}
		else if(is_exportation_worked_fine == FALSE)
		{
			inform_unknown_error();
			press_enter();
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
	Boolean is_exportation_worked_fine = export_text_to_file(text_input);
	if(is_exportation_worked_fine == TRUE)
	{
		inform_text_is_fine();
		press_enter();
		options.text = TXTSUCCESS;
	}
	else if(is_exportation_worked_fine == FALSE)
	{
		inform_unknown_error();
		press_enter();
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
			options.rsa = RSAENCRYPT;
		break;

		case 2:
			options.rsa = RSADECRYPT;
		break;

		case 3:
			options.rsa = RSAHACK;
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
	printf("\tRSA without knowing the public and private keys.");
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
	print_previous();
	print_quit();
	print_hline();
}

void explain_text_upload_by_file()
{
	print_hline();
	printf("Please inform the path of the file (based on current folder)\n");
	printf("Example: /foo.txt\n");
}

void explain_text_upload_by_user()
{
	print_hline();
	printf("Please write your text\n");
}

void inform_wrong_path()
{
	printf("[ERROR]\tThe file could not be found!");
	print_hline();
}

void inform_text_is_fine()
{
	printf("[Yiikies!]\tThe text was succesfully imported!");
	print_hline();
}

void inform_rsa_option(){
	print_hline();
	print_choose();
	printf("\t[1] Encrypt the Text\n");
	printf("\t[2] Decrypt the Text\n");
	printf("\t[3] Try to Hack a Encrypted Text\n");
	print_previous();
	print_quit();
	print_hline();
}

void inform_unknown_error()
{
	printf("[ERROR]\tWell, im sorry about that, but some\n");
	printf("unknown force striked against this software. :(\n");
}