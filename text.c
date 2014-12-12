#include "text.h"

int file_size(char *path)
{
	FILE *target = fopen(path, "r");
	fseek(target, 0, SEEK_END);
	int file_size = ftell(target);
	fclose(target);
	return file_size;
}


char *get_text_by_file(char *path)
{
	char *text;
	int size = file_size(path);
	text = (char*) malloc(size * (sizeof(char)));
	FILE *target = fopen(path, "r");
	fread(text, sizeof(char), size, target);
	fclose(target);
	return text;

}

char *receive_string_from_user(unsigned long long int text_size)
{
	char* text_input = (char*) malloc(text_size*(sizeof(char)));
	fgets(text_input, text_size, stdin);
	text_input[strlen(text_input)-1] = '\0';
	return text_input;
}

Boolean export_text_to_file(char *text_input, char *path_input)
{
	Boolean is_exportation_worked_fine = FALSE;
	FILE *standard_text_file = fopen(path_input, "w");
	fprintf(standard_text_file, "%s", text_input);
	fclose(standard_text_file);
	is_exportation_worked_fine = TRUE;
	return is_exportation_worked_fine;
}

/**
* Returns the number of lines in an FILE
*/
int numberoflines(FILE *input_file)
{
	char s;
	long long int number_of_lines = 0;
	while((s = fgetc(input_file)) != EOF){
		if(s == '\n')
			number_of_lines++;
	}
	rewind(input_file);
	return number_of_lines;
}

void fix_word(char *word)
{
	long long int i = 0;	
	while(1){
		if (word[i] == '\n' || word[i] == '\0') {
			word[i] = '\0';
			break;
		}	
		i++;
	}
}

/*
Esta função retorna uma cópia minúscula da string enviada como argumento, sem alterar o argumento.
*/
char* tolow(char* string) 
{
	long long int i = 0;
	char* aux = (char*) malloc(strlen(string) * sizeof(char));
	while (string[i])
	{
		if (verify_if_uppercase(string[i]))
		{
			aux[i] = string[i] + 32;
		}
		else
		{
			aux[i] = string[i];
		}
		i++;
	}
	return aux;
}


/*
Esta função recebe como argumento um caracter e verifica se o mesmo é uma letra maiúscula. Caso seja, retorna 1, se não, retorna 0.
*/
Boolean verify_if_uppercase(char letter)
{
	Boolean is_in_uppercase = FALSE;
	if(letter >= 65 && letter <= 90)
	{
		is_in_uppercase = TRUE;
	}
	return is_in_uppercase;
}

Boolean is_letter(char letter) {
	Boolean is_in_uppercase = FALSE;
	
	if((letter >= 65 && letter <= 90) || (letter >= 97 && letter <= 122))
	{
		is_in_uppercase = TRUE;
	}
	return is_in_uppercase;
}

Boolean compare_strings(char *first, char *second)
{
	int length_first = strlen(first);
	int length_second = strlen(second);
	int compatibility = 0;
	char *aux1, *aux2;
	aux1 = tolow(first);
	aux2 = tolow(second);
	Boolean isEquals;
	if(length_first == length_second)
	{
		int i;
		for(i = 0; i< length_first; i++)
		{
			if (aux1[i] == aux2[i])
			{
				compatibility++;
			}
		}
		if(compatibility == length_first){
			isEquals = TRUE;	
		}
	}
	else if((strstr(aux1, aux2) != NULL && length_second > 3) 
			|| (strstr(aux2, aux1) != NULL && length_first > 3)
			&& (aux1[0] == aux2[0]))
	{
		isEquals = TRUE;	
	}
	else
	{
		isEquals = FALSE;
	}
	free(aux1);
	free(aux2);
	return isEquals;
}

char **get_dictionary()
{
	FILE *dictionary_file = fopen("dicionario.pt.txt", "r");
	char **dictionary;
	if(dictionary_file == NULL)
	{
		printf("O dicionario esta com problema\n");
		exit(1);
	}
	else
	{
		long number_of_words = numberoflines(dictionary_file);
		dictionary = (char**) malloc(number_of_words * sizeof(char*));
		long long int i;
		for(i = 0; i < number_of_words; i++)
		{
			dictionary[i] = (char*) malloc(MAX_WORD_LENGHT*sizeof(char));
			fgets(dictionary[i], MAX_WORD_LENGHT, dictionary_file);
			fix_word(dictionary[i]);
		}
	}
	fclose(dictionary_file);
	return dictionary;
}
