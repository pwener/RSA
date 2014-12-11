#include "rsa.h"

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
