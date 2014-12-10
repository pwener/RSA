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

/*
Este programa possui dois modos de execução. O modo explicativo explica ao usuário como funciona a cifra de Vigenère e o modo Hardcore mostra na prática como é feito o processo de decifração de um texto cifrado sem ter em mãos a chave correta (força bruta).
*/
int main(int argc, char* argv[]) {
	int modo_de_jogo;
	char* texto = malloc(MAX_LENGTH * sizeof(char));
	char* chave = malloc(10 * sizeof(char));
	printf("\t\t%s", "~ C I F R A  D E  V I G E N È R E ~\n");
	printf("************* Escolha o modo de execução do programa *************\n\n"); 
	printf("1 - Modo explicativo\t2 - Modo Hardcore: Força Bruta!\n"); 	
	scanf("%d", &modo_de_jogo);
	getchar();
	if (modo_de_jogo == 1) {
		printf("\nA cifra de Vigenère\n\n");
		printf("A cifra de Vigenère é uma técnica de criptografia que é muito parecida com a cifra de César. O texto puro sofre deslocamentos variáveis, caracter por caracter, enquanto que na cifra de César o deslocamento é constante. O funcionamento é bem simples:\n");
		printf("1. Uma chave é definida, por exemplo. Ex: 'fga'\n");
		printf("2. Esta chave é concatenada com o texto objeto até o tamanho do texto que será cifrado. Ex: 'fga' + 'A menina brinca na rua' = 'fgaAmeninabrincana' (Obs: Neste programa, desconsideramos quaisquer caracteres que não sejam letras durante a encriptação e decifração!)\n");
		printf("3. É realizado um deslocamento, caracter por caracter entre o texto puro e a chave gerada. Ex 'A menina brinca na rua' + 'fgaAmeninabrincana' = 'F senurn jeioti ac rha'.\n");
		printf("4. Para decifrar o texto cifrado, basta realiza o caminho inverso, tendo em mãos a chave utilizada na encriptação!\n");
		printf("\nExperimente!\n");   
		printf("Digite o texto que será cifrado: ");
		get_string(texto);
		printf("Digite a chave de Vigenère (deve conter exatamente TRÊS letras MINÚSCULAS): ");
		get_string(chave);
		encriptar(texto, chave, tamanho(chave));
		printf("Texto encriptado: ");
		printf("%s\n", texto);
		desencriptar(texto, chave, tamanho(chave));
		printf("\n");
		printf("Texto decifrado: ");
		printf("%s\n", texto);
	} else if (modo_de_jogo == 2) {
		printf("\n\nFORÇA BRUTA\n\n");
		printf("Digite o texto que será encriptado\n");
		get_string(texto);
		srand(time(NULL));
		chave[0] = 97 + rand()%25;
		chave[1] = 97 + rand()%25;
		chave[2] = 97 + rand()%25;
		chave[3] = '\0';
		printf("- Chave de Vigenère gerada aleatoriamente: %s\n", chave);
		encriptar(texto, chave, tamanho(chave));
		printf("- Texto cifrado: %s\n\n", texto);
		printf("Aperte Enter quando estiver pronto!\n\n");
		getchar();
		forca_bruta(texto);
	} else {
		printf("Opção inválida. O programa será encerrado.\n");
	}
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
Esta função retorna a quantidade de caracteres válidos de uma string.
*/
int tamanho(char* string) {
	int i = 0;
	while (string[i]) i++;
	return i;
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
		return n%26;
	else
		return n%26 + 26;
}

/*
Esta função realiza a encriptação do texto ou palavra enviada, utilizando a cifra de César.
*/
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

	for (int i = 0, j = 0; texto[i] && temp[j]; i++) {
		if (!verificar_letra(texto[i])) continue;
	
		if (verificar_letra_minuscula(texto[i])) {		
			if (verificar_letra_minuscula(temp[j]))			
				texto[i] = mod((texto[i] - 97) + (temp[j++] - 97)) + 97;
			else
				texto[i] = mod((texto[i] - 97) + (temp[j++] - 65)) + 97;
		}

		if (verificar_letra_maiuscula(texto[i])) {
			if (verificar_letra_minuscula(temp[j]))
				texto[i] = mod((texto[i] - 65) + (temp[j++] - 97)) + 65;
			else
				texto[i] = mod((texto[i] - 65) + (temp[j++] - 65)) + 65;
		}
	}
	
	free(temp); 
}

/*
Esta função realiza a desencriptação do texto ou palavra enviada.
*/
void desencriptar(char* texto, char* chave, int tamanhoChave) {
	char* aux = malloc(tamanho(texto) * sizeof(char));	
	strcpy(aux, chave);

	for (int i = 0, j = tamanhoChave; texto[i]; i++) {
		if (!verificar_letra(texto[i])) continue;

		if (verificar_letra_minuscula(texto[i])) {
			if (verificar_letra_minuscula(aux[j - tamanhoChave]))			
				aux[j] = mod((texto[i] - 97) - (aux[j - tamanhoChave] - 97)) + 97;
			else
				aux[j] = mod((texto[i] - 97) - (aux[j - tamanhoChave] - 65)) + 97;
		}
		if (verificar_letra_maiuscula(texto[i])) {
			if (verificar_letra_minuscula(aux[j - tamanhoChave]))			
				aux[j] = mod((texto[i] - 65) - (aux[j - tamanhoChave] - 97)) + 65;
			else
				aux[j] = mod((texto[i] - 65) - (aux[j - tamanhoChave] - 65)) + 65;
		}
		j++;	
	}

	for (int i = 0, j = 0; texto[i]; i++) {
		if(!verificar_letra(texto[i])) continue;
		
		if (verificar_letra_minuscula(texto[i])) {
			if (verificar_letra_minuscula(aux[j]))
				texto[i] = mod((texto[i] - 97) - (aux[j] - 97)) + 97;
			else
				texto[i] = mod((texto[i] - 97) - (aux[j] - 65)) + 97;
		}

		if (verificar_letra_maiuscula(texto[i])) {
			if (verificar_letra_minuscula(aux[j]))
				texto[i] = mod((texto[i] - 65) - (aux[j] - 97)) + 65;
			else
				texto[i] = mod((texto[i] - 65) - (aux[j] - 65)) + 65;		
		}
		j++;	
	}

	free(aux);
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
Esta função realiza a decifração de um texto criptografado pela cifra de Vigenère com uma chave de TRÊS letras MINÚSCULAS. Para isso são geradas todas as chaves entre 'aaa'...'zzz' e as mesmas são enviadas como argumentos da função desencriptar. Quando as palavras do texto desencriptado apresentarem uma certa compatibilidade com as palavras do arquivo que contém o repertório lexical da língua portuguesa, a execução do for é executada e a chave atual é selecionada como a chave correta.
*/
void forca_bruta(char* texto_criptografado) {
	char** repertorio_lexical = obter_repertorio_lexical();
	boolean chave_encontrada = false;	
	char* chave;
	int frequencia_de_acertos = 0;
	int qtd_palavras = 0;
	char delimitadores[7] = " .,!?\"'";
	char aux[strlen(texto_criptografado)];
	char* token;
	char* tokens[2000];
	chave = malloc(4 * sizeof(char));
	chave[3] = '\0';
	for (int indice_1 = 97; indice_1 <= 122; indice_1++) {
		chave[0] = indice_1;
		for (int indice_2 = 97; indice_2 <= 122; indice_2++) {
			chave[1] = indice_2;			
			for (int indice_3 = 97; indice_3 <= 122; indice_3++) {
				chave[2] = indice_3;
				printf("CHAVE: %s\n", chave);
				printf("Texto cifrado: %s\n", texto_criptografado);
				desencriptar(texto_criptografado, chave, 3);
				printf("Texto decifrado: %s\n", texto_criptografado); 
				strcpy(aux, texto_criptografado);
				qtd_palavras = 0;
				token = strtok(aux, delimitadores);
				while (token != NULL) {
					tokens[qtd_palavras++] = token;
					token = strtok(NULL, delimitadores);
				}	
				for (int i = 0; i < qtd_palavras; i++) {
						printf("%s ", tokens[i]);
						for (int j = 0; j < 29840; j++) {
							if (comparar_strings(tokens[i], repertorio_lexical[j])) {
								frequencia_de_acertos++;
								break;
							}
						}
	
						if ((float) frequencia_de_acertos >= 0.8 * qtd_palavras) {
							printf("*.*.*.*.*.* ...80%c de acerto atingido... *.*.*.*.*.*\n", '%');
							printf("\n\nOK! CHAVE ENCONTRADA: %s\n\n", chave);					
							chave_encontrada = true;
							break;
						}
				}
				printf("\n");
				if (chave_encontrada)
					break;
				frequencia_de_acertos = 0;
				encriptar(texto_criptografado, chave, 3);
			}
			if (chave_encontrada)
				break;
		}
		if (chave_encontrada)
			break;		
	}
	
	free(chave);
}

/*
Esta função processa duas strings e verifica se existe uma certa compatibilidade entre elas. O fluxo de execução desta função é dado da seguinte forma:
- Se ambas strings forem iguais, a variável compatibilidade possuirá o mesmo valor que o tamanho das strings, e a função retorna true.
- Se as strings não forem iguais, é verificado se uma é um sufixo da outra. Utilizando a função strstr da biblioteca string.h, é verificado se uma string está contida na outra, exemplo: 'orb' está contido em 'orbita'. É verificado também se o tamanho da string contida na outra é maior do que 3, para evitar os casos em que uma letra está contida em uma palavra, exemplo: 'b' está contido em 'brasil'. E por fim, para garantir que um é o sufixo do outro, as iniciais de ambas devem ser equivalentes.
- Se as strings não passarem em nenhum dos testes acima, elas são consideradas incompatíveis e é retornado falso. 
Esta função NÃO é case sensitive.
*/
boolean comparar_strings(char* string_a, char* string_b) {
	int tamanho_a = strlen(string_a), tamanho_b = strlen(string_b);
	int compatibilidade = 0;
	char* aux1 = converter_para_minuscula(string_a);
	char* aux2 = converter_para_minuscula(string_b);
	if (tamanho_a == tamanho_b) {
		for (int i = 0; i < tamanho_a; i++)
			if (aux1[i] == aux2[i])
				compatibilidade++;

		if (compatibilidade == tamanho_a) {
			free(aux1);
			free(aux2);			
			return true;
		}
	}
	if (((strstr(aux1, aux2) != NULL && tamanho_b > 3) || (strstr(aux2, aux1) != NULL && tamanho_a > 3)) && aux1[0] == aux2[0]) { 
		free(aux1);
		free(aux2);				
		return true;
	} else {
		free(aux1);
		free(aux2);
		return false;
	}
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
