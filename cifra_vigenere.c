#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_LENGTH 5000
#define boolean int
#define true 1
#define false 0

void get_string(char* palavra);

int tamanho(char* string);

int abs(int n);

int mod(int n);

void encriptar(char* palavra, char* chave, int tamanhoChave);

void desencriptar(char* palavra, char* chave, int tamanhoChave);

char** obter_repertorio_lexical(void);

void corrigir_string(char* palavra);

char* converter_para_minuscula(char* string);

void forca_bruta(char* texto);

boolean comparar_strings(char* string_a, char* string_b);

boolean verificar_letra(char letra);

boolean verificar_letra_minuscula(char letra);

boolean verificar_letra_maiuscula(char letra);

int main(int argc, char* argv[]) {
	int modo_de_jogo;
	char* texto = malloc(MAX_LENGTH * sizeof(char));
	char* chave = malloc(10 * sizeof(char));
	printf("\t\t%s", "~ C I F R A  D E  V I G E N È R E ~\n");
	printf("************* Escolha o modo de execução do programa *************\n\n"); 
	printf("1 - Modo explicativo\t2 - Modo Hardcore: Força Bruta!\n"); 	
	scanf("%d", &modo_de_jogo);
	getchar();	
	get_string(texto);
	get_string(chave);
	encriptar(texto, chave, tamanho(chave));
	printf("%s\n", texto);
	desencriptar(texto, chave, tamanho(chave));
	printf("%s\n", texto);	
	free(texto);
	return 0;
}

void get_string(char* palavra) {
	fgets(palavra, MAX_LENGTH, stdin);
	palavra[strlen(palavra) - 1] = '\0';
}

int tamanho(char* string) {
	int i = 0;
	while (string[i]) i++;
	return i;
}

int abs(int n) {
	return n > 0 ? n : -n;
}

int mod(int n) {
	if (n >= 0)
		return n%26;
	else
		return n%26 + 26;
}

void encriptar(char* texto, char* chave, int tamanhoChave) {
	char* temp = malloc(tamanho(texto) * sizeof(char));
	strcpy(temp, chave);
	int indice1 = tamanhoChave;
	for (int i = tamanhoChave; i < tamanho(texto) && indice1 < tamanho(texto); i++) {
		if (verificar_letra(texto[i - tamanhoChave]))
			temp[indice1++] = texto[i - tamanhoChave];	
	}
	temp[tamanho(texto)] = '\0';

	printf("- Chave gerada na encriptação: %s\n", temp);

	for (int i = 0; texto[i]; i++) {
		if (!verificar_letra(texto[i])) continue;
	
		if (verificar_letra_minuscula(texto[i]))		
			texto[i] = mod((texto[i] - 97) + (temp[i] - 97)) + 97;
		
		if (verificar_letra_maiuscula(texto[i]))
			texto[i] = mod((texto[i] - 65) + (temp[i] - 65)) + 65;
	}
	
	free(temp); 
}

void desencriptar(char* texto, char* chave, int tamanhoChave) {
	char* aux = malloc(tamanho(texto) * sizeof(char));	
	strcpy(aux, chave);
	
	for (int i = 0, j = tamanhoChave; texto[i]; i++) {
		if (!verificar_letra(texto[i])) continue;		

		printf("%c\n", mod((texto[i] - 97) - (aux[j - tamanhoChave] - 97)) + 97);		
		getchar();
		if (verificar_letra_minuscula(texto[i]))
			aux[j++] = mod((texto[i] - 97) - (aux[j - tamanhoChave] - 97)) + 97;

		if (verificar_letra_maiuscula(texto[i])) 
			aux[j++] = mod((texto[i] - 65) - (aux[j - tamanhoChave] - 65)) + 65;
	}

	printf("%s\n", aux);
}

/*
	for (int i = 0, j = 0; i < tamanhoChave; i++) {
		if(!verificar_letra(texto[i])) continue;
		
		if (verificar_letra_minuscula(texto[i]))
			texto[i] = mod((texto[i] - 97) - (chave[j++] - 97)) + 97;

		if (verificar_letra_maiuscula(texto[i]))
			texto[i] = mod((texto[i] - 65) - (chave[j++] - 65)) + 65;
	
	}

	for (int i = tamanhoChave, numero_de_espacos = 0; texto[i]; i++) {
		if(!verificar_letra(texto[i])) {
			if (texto[i] == ' ') numero_de_espacos++;		
 			continue;
		}
		if (verificar_letra_minuscula(texto[i]))
			texto[i] = mod((texto[i] - 97) - (texto[i - tamanhoChave + numero_de_espacos] - 97) + 26) + 97;

		if (verificar_letra_maiuscula(texto[i]))
			texto[i] = mod((texto[i] - 65) - (texto[i - tamanhoChave + numero_de_espacos] - 65) + 26) + 65;
	}
*/
char* converter_para_minuscula(char* string) {
	int i = 0;
	char* aux = malloc(strlen(string) * sizeof(char));
	while (string[i]) {
		if (verificar_letra_maiuscula(string[i]))
			aux[i] = string[i] + 32;
		else
			aux[i] = string[i];
		i++;	
	}
	return aux;
}
/*
void forca_bruta(char* texto_criptografado) {
	char** repertorio_lexical = obter_repertorio_lexical();
	int frequencia_de_acertos = 0;
	int n_certo = 0, qtd_palavras = 0;
	char delimitadores[7] = " .,!?\"'";
	char aux[strlen(texto_criptografado)];
	strcpy(aux, texto_criptografado);
	char* token = strtok(aux, delimitadores);
	char* tokens[2000];
	while (token != NULL) {
		tokens[qtd_palavras++] = token;
		token = strtok(NULL, delimitadores);
	}	

	for (int i = 1; i <= 26; i++) {
			for (int j = 0; j < qtd_palavras; j++) {
				desencriptar(tokens[j], i);
				printf("%s ", tokens[j]);
				for (int k = 0; k < 29840; k++) {
					if (comparar_strings(converter_para_minuscula(tokens[j]), converter_para_minuscula(repertorio_lexical[k]))) {
						//printf("\n%s\n%s\n", tokens[j], repertorio_lexical[k]);						
						frequencia_de_acertos++;
						break;
					}
				}
				encriptar(tokens[j], i);
				if ((float) frequencia_de_acertos >= 0.8 * qtd_palavras) {
					printf("*.*.*.*.*.* ...80%c de acerto atingido... *.*.*.*.*.*\n", '%');
					printf("\n\nOK! CHAVE ENCONTRADA: %d\n\n", i);					
					n_certo = i;
					break;
				}
			}
			printf("\n");
			if (n_certo)
				break;
			frequencia_de_acertos = 0;
	}
	desencriptar(texto_criptografado, n_certo);
}
*/
boolean comparar_strings(char* string_a, char* string_b) {
	int tamanho_a = strlen(string_a), tamanho_b = strlen(string_b);
	int compatibilidade = 0;	
	if (tamanho_a == tamanho_b) {
		for (int i = 0; i < tamanho_a; i++)
			if (string_a[i] == string_b[i])
				compatibilidade++;

		if (compatibilidade == tamanho_a)
			return true;
	}
	if (((strstr(string_a, string_b) != NULL && tamanho_b > 3) || (strstr(string_b, string_a) != NULL && tamanho_a > 3)) && string_a[0] == string_b[0]) 
		return true;
	else
		return false;
}

char** obter_repertorio_lexical(void) {
	FILE* arquivo = fopen("repertorio_lexical_pt.txt", "r");
	char** repertorio_lexical;	
	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo!\n");
		exit(1);
	}

	repertorio_lexical = malloc(29840 * sizeof(char *));
	
	for (int i = 0; i < 29840; i++) {	
		repertorio_lexical[i] = malloc(40 * sizeof(char));
		fgets(repertorio_lexical[i], 40, arquivo);
		corrigir_string(repertorio_lexical[i]);
	}	
	fclose(arquivo);
	return repertorio_lexical;
}

void corrigir_string(char* palavra) {
	int i = 0;	
	while(1) {
		if (palavra[i] == '\n' || palavra[i] == '\0') {
			palavra[i] = '\0';
			break;
		}	
		i++;
	}
}

boolean verificar_letra(char letra) {
	return verificar_letra_maiuscula(letra) || verificar_letra_minuscula(letra);
}

boolean verificar_letra_minuscula(char letra) {
	return letra >= 97 && letra <= 122;
}

boolean verificar_letra_maiuscula(char letra) {
	return letra >= 65 && letra <= 90;
}
