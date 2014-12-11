#include "text.h"

int main(){
	char *test = malloc(sizeof(char)*11);
	test = "SOLAR";
	printf("word: %s\n", test);
	test = tolow(test);
	printf("After to low()\n");
	printf("word: %s\n", test);
	printf("isTrue : %d\n", compare_strings(test, "solarizado"));
	return 0;
}
