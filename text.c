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
