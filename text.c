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
	text = malloc(size * (sizeof(char)));
	FILE *target = fopen(path, "rb");
	rewind(target);
	fread(text, sizeof(char), size, target);
	fclose(target);
	return text;

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

char *str_upercase(char *string)
{
	char *result = string;
	while (*string) *string = toupper(*(string++));
	return result;
}

Boolean compare_strings(char *first, char *second)
{
	int length_first = strlen(first);
	int length_second = strlen(second);
	int compatibity = 0;
	char *aux1, *aux2;
	strcpy(aux1, first);
	strcpy(aux2, second);
	str_upercase(aux1);
	Boolean isEquals;
	if(length_first == length_second)
	{
		int i;
		for(i = 0; i< length_first; i++)
		{
			if (aux1[i] == aux2)
			{
				compatibility++;
			}
		}
		if(compatibility == length){
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
		dictionary = malloc(number_of_words * sizeof(char*));
		int i;
		for(i = 0; i < number_of_words; i++)
		{
			dictionary[i] = malloc(MAX_WORD_LENGHT*sizeof(char));
			fgets(dictionary[i], MAX_WORD_LENGHT, dictionary_file);
			fix_word(dictionary[i]);
		}
	}
	fclose(dictionary_file);
	return dictionary;
}
