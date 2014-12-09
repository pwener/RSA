#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Para compilar no gcc digite: gcc testePrimalidade.c -lm

int s;
int d;

/*
* Operador modulo da aritmética modular - teoria dos numeros
* retorna o modulo n de um numero x
*/
int modulo(double x, int n){
	if(x<0){
                return (int)(x%n)+x;
        }
	else{
		return (int)(x%n);
	}
}

/*
* Verifica se um numero é impar
*/
int eImpar(int i){
	if(i%2 == 0){
		return 0;
	}else{
		return 1;
	}
}

/*
* Tenta achar um d e um s o qual possa rescrever n-1 como 2^s * d
* para d impar, tal que esse passo se repita k vezes, (k é o numero de iterações)
*/
int decomp(int k){
	int x;
	//y é o d
	int y;
	for(x = 1; x < k; x++){
		for(y = 1; y < k/x; y++){
			int result = (int)pow(2, x)*y; 
			if(result == k && eImpar(y) == 1){
				d = y;
				s = x;
				return y;
			}
		}	
	}
}

int RandomInteger( int l, int h){
	int resultado = 0;
	int menor = 0;
	int maior = 0;
    	if(l < h){
        	menor = l;
       		maior = h + 1;
	}
	else{
        	menor = h + 1;
       		maior = l;
   	}
    	resultado = (rand()%(maior-menor))+menor;
    	return resultado;
	//return (l + rand()%h);
}

void teste(){
	int n;
	printf("Digite um n impar e maior que 3: ");
	scanf("%d", &n);
	if(n <= 3 || eImpar(n) == 0){
		printf("Teste só funciona para n impar e maior que 3.\nDigite novamente: ");
		scanf("%d", &n);
	}
	d = decomp(n-1);

	// Agora pego um numero a aleatorio entre 2 e n-2
        srand(time(NULL));
       	int a = RandomInteger(2, n-2);


	int vezes;
        printf("Quantas vezes deseja testar: ");
        scanf("%d", &vezes);
	int nLoop = 0;
	while(nLoop<vezes){
		printf("Aleatorio = %d\n", a);
		int i = 0;
		int x;

		for(x = 0; x < s+1; x++){
			int op1 = pow(2, x);
	       		int op2 = d*op1;
			int result = mod(a, n);
			int z = 1;
			while(z < op2){
				if(result>n){
					result = mod(result, n);
				}else{
					result = mod(result*a, n);
					z++;
				}
			}	
		
			if(result == 1){
				i++;
				break;
			}
		}
		if( i > 0){
			printf("O número é possivel primo\n" );
		}else{
			printf("\nO número é composto\n");
		}
		nLoop++;
		a++;
		if(a>n-2){
			a -= n;
		}
	}
}

int main(){
	int choice;
	while(choice != 2){
		printf("1 para calcular, 2 para sair: ");
		scanf("%d", &choice);
		if(choice == 1){
			teste();
		}else{
			return 0;
		}
	}
}
