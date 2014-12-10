#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_LENGTH 5000
#define boolean int
#define true 1
#define false 0

void get_string(char* palavra);

int abs(int n);

int mod(int n);

void encriptar(char* texto, int n);

void desencriptar(char* texto, int n);

char** obter_repertorio_lexical(void);

void corrigir_string(char* palavra);

char* converter_para_minuscula(char* string);

void forca_bruta(char* texto);

boolean comparar_strings(char* string_a, char* string_b);

boolean verificar_letra(char letra);

boolean verificar_letra_minuscula(char letra);

boolean verificar_letra_maiuscula(char letra);


/*
Este programa possui dois modos de execução. O modo explicativo explica ao usuário como funciona a cifra de César e o modo Hardcore mostra na prática como é feita a decifração de um texto cifrado sem ter em mãos a chave correta (força bruta).
*/
int main(void) {
	int n_de_cesar, modo_de_jogo;
	char* texto = malloc(MAX_LENGTH * sizeof(char));
	printf("\t\t   %s", "~ C I F R A  D E  C É S A R ~\n");	
	printf("************* Escolha o modo de execução do programa *************\n\n"); 
	printf("1 - Modo explicativo\t2 - Modo Hardcore: Força Bruta!\n"); 	
	scanf("%d", &modo_de_jogo);
	
	if (modo_de_jogo == 1) {
		printf("\nA cifra de César\n");
		printf("A cifra de César é uma técnica de criptografia que consiste em realizar um deslocamento nos caracteres que constituem as palavras de um texto que será criptografado. Neste programa, cada caracter da string em questão receberá um incremento de \"n\" unidades de acordo com a entrada do usuário.\n");
		printf("Ex: Supondo um deslocamento \"n = 3\", a palavra bola se tornaria \"erod\" após a criptografia! Experimente!\n");
		getchar();
		printf("Digite a frase que deseja criptografar: ");
		get_string(texto);
		printf("Digite o \"n\" de César: ");
		scanf("%d", &n_de_cesar);
		encriptar(texto, n_de_cesar);
		printf("Texto encriptado: %s\n", texto);
		desencriptar(texto, n_de_cesar);
		printf("Texto decifrado: %s\n\n", texto);
	} else if (modo_de_jogo == 2) {
		printf("Geração aleatória do \"n\" de César\n");
		srand(time(NULL));
		printf("Deslocamento gerado: %d\n\n", n_de_cesar = rand()%26 + 1);
		getchar();
		printf("Digite a frase que deseja criptografar: ");
		get_string(texto);
		encriptar(texto, n_de_cesar);
		
		printf("Texto encriptado: %s\n", texto);		
		forca_bruta(texto);
		printf("\n");
		printf("Texto decifrado: %s\n\n", texto);
	} else {
		printf("Opção inválida! Programa encerrado!\n");
	}
	printf("A criptografia deste programa se baseia na codificação ASCII dos caracteres!\n\n");
	free(texto);
	return 0;
}

/*
Esta função realiza a leitura de um texto ou palavra enviada pelo usuário.
*/
void get_string(char* palavra) {
	fgets(palavra, MAX_LENGTH, stdin);
	palavra[strlen(palavra) - 1] = '\0';
}

/*
Esta função retorna o módulo de um número. 
*/
int abs(int n) {
	return n > 0 ? n : -n;
}

/*
Esta função retorna n mod(26).
*/
int mod(int n) {
	if (n >= 0)
		return n % 26;
	else
		return n % 26 + 26;
}

/*
Esta função realiza a encriptação do texto ou palavra enviada, utilizando a cifra de César.
*/
void encriptar(char* texto, int n_de_cesar) {
	for (int i = 0; texto[i]; i++) {
		if (!verificar_letra(texto[i])) continue; 
		
		if (verificar_letra_minuscula(texto[i]))
			texto[i] = mod(texto[i] - 97 + n_de_cesar) + 97; 
    	
		if (verificar_letra_maiuscula(texto[i]))
			texto[i] = mod(texto[i] - 65 + n_de_cesar) + 65;
	}
}

/*
Esta função realiza a desencriptação do texto ou palavra enviada.
*/
void desencriptar(char* texto, int n_de_cesar) {
	for (int i = 0; texto[i]; i++) {
		if (!verificar_letra(texto[i])) continue;

		if (verificar_letra_minuscula(texto[i]))		
			texto[i] = mod(texto[i] - 97 - n_de_cesar) + 97; 

		if (verificar_letra_maiuscula(texto[i]))
			texto[i] = mod(texto[i] - 65 - n_de_cesar) + 65;
	}
}
/*
Esta função retorna uma cópia minúscula da string enviada como argumento, sem alterar o argumento.
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
Esta função realiza a tentativa de decifrar um texto criptografado pela cifra de César sem possuir a chave, ou seja, por força bruta. Em primeiro lugar, a função obter_repertorio_lexical() é chamada pra se obter as palavras da língua portuguesa. Este algoritmo utiliza a função strtok() da biblioteca string.h para dividir (tokenizar) o texto criptografado em apenas palavras (criptografadas) e armazená-las na variável local tokens, que suporta 2000 palavras. Após este processo, cada token (palavra cifrada) é decifrado utilizando uma chave no intervalo de 1 a 26, a palavra decifrada é comparada com todas as letras da variável que armazena as palavras da língua portuguesa (repertorio_lexical). A função converter_para_minuscula() retorna uma réplica minúscula da string enviada como argumento, sem alterá-la. Se a função comparar_strings() retornar true, a variável frequencia_de_acertos é incrementada. O token analisado atualmente é encriptado novamente com a mesma chave (por não se saber ainda se a chave atual é a correta). Se a variável frequencia_de_acertos for maior ou igual a 80% da quantidade de palavras, a chave é considerada verdadeira e a execução do for é suspensa. O texto é então desencriptado utilizando a chave encontrada.
*/
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
	free(repertorio_lexical);
}

/*
Esta função processa duas strings e verifica se existe uma certa compatibilidade entre elas. O fluxo de execução desta função é dado da seguinte forma:
- Se ambas strings forem iguais, a variável compatibilidade possuirá o mesmo valor que o tamanho das strings, e a função retorna true.
- Se as strings não forem iguais, é verificado se uma é um sufixo da outra. Utilizando a função strstr da biblioteca string.h, é verificado se uma string está contida na outra, exemplo: 'orb' está contido em 'orbita'. É verificado também se o tamanho da string contida na outra é maior do que 3, para evitar os casos em que uma letra está contida em uma palavra, exemplo: 'b' está contido em 'brasil'. E por fim, para garantir que um é o sufixo do outro, as iniciais de ambas devem ser equivalentes.
- Se as strings não passarem em nenhum dos testes acima, elas são consideradas incompatíveis e é retornado falso. 
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

/*
Esta função realiza a leitura do arquivo que contém o repertório lexical da língua portuguesa, e armazena cada palavra localizada no arquivo em uma posição do vetor 'repertorio_lexical'. A função retorna o vetor contendo todas as palavras.
obs: Se algum erro ocorrer na abertura do arquivo, o programa é encerrado.
*/
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

/*
Esta função recebe como argumento uma string e percorre seus caracteres até encontrar um caracter nulo '\0' ou um caracter de quebra de linha '\n', para então atribuir a esta posição o caracter nulo '\0'. Ela é utilizada no processo de leitura do arquivo (na função obter_repertorio_lexical()), pois a função fgets() inclui na string o caracter '\n'.
*/
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

/*
Esta função recebe como argumento um caracter e verifica se o mesmo é uma letra. Caso seja, retorna 1, se não, retorna 0.
*/
boolean verificar_letra(char letra) {
	return verificar_letra_maiuscula(letra) || verificar_letra_minuscula(letra);
}

/*
Esta função recebe como argumento um caracter e verifica se o mesmo é uma letra minúscula. Caso seja, retorna 1, se não, retorna 0.
*/
boolean verificar_letra_minuscula(char letra) {
	return letra >= 97 && letra <= 122;
}

/*
Esta função recebe como argumento um caracter e verifica se o mesmo é uma letra maiúscula. Caso seja, retorna 1, se não, retorna 0.
*/
boolean verificar_letra_maiuscula(char letra) {
	return letra >= 65 && letra <= 90;
}
