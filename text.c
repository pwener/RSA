#include "text.h"

long file_size(char *path)
{
	FILE *target = fopen(path, "rb");
	fseek(target, 0, SEEK_END);
	long file_size = ftell(target);
	fclose(target);
	return file_size;
}


char *get_text(char *path)
{
	char *text;
	long size = file_size(path);
	text = (char*) malloc(size * (sizeof(char)));
	FILE *target = fopen(path, "rb");
	rewind(target);
	fread(text, sizeof(char), size, target);
	fclose(target);
	return text;

}

Boolean export_text_to_file(char *text_input)
{
	Boolean is_exportation_worked_fine = FALSE;
	FILE *standard_text_file = fopen("/text/exported.txt", "w");
	fwrite(text_input, sizeof(text_input), 1, standard_text_file);
	fclose(standard_text_file);
	if(strcmp(get_text("/text/exported.txt"),text_input)==0)
	{
		is_exportation_worked_fine = TRUE;
	}
	return is_exportation_worked_fine;
}

/**
* Returns the number of lines in an FILE
*/
int numberoflines(FILE *input_file)
{
	char s;
	int number_of_lines = 0;
	while((s = fgetc(input_file)) != EOF){
		if(s == '\n')
			number_of_lines++;
	}
	rewind(input_file);
	return number_of_lines;
}

void fix_word(char *word)
{
	int i = 0;	
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
	int i = 0;
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
	else if(((strstr(aux1, aux2) != NULL && length_first > 3) 
			|| (strstr(aux2, aux1) != NULL && length_first > 3)) 
			&& aux1[0] == aux2[0])
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
		int i;
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
