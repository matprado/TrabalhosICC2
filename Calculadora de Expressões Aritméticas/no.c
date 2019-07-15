#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "no.h"


/*ESTRUTURA no:
@CAMPOS:
-Tipo do dado no nó;
-Union com os tipos: operando, operador e delimitador;
-Ponteiros para os nós da direita e esquerda na árvore aritmética;*/
struct no{
	int tipo;
	/*
	0 = nada;
	1 = operando;
	2 = operador;
	3 = delimitador;*/
	union{
		double operando;
		char operador;	 	
		char delimitador;
	}info;
	NO *esquerda;
	NO *direita;
};


/*FUNÇÃO criar_no(): Cria um nó;
@ARGUMENTOS:
-Não possui argumento;
@RETORNO:
-Se existir memória disponível, retorna um ponteiro para o nó criado;*/
NO *criar_no(void){
	NO *novo = (NO *) malloc(sizeof(NO));
	if(novo != NULL){
		novo->tipo = 0;
		novo->esquerda = NULL;
		novo->direita = NULL;
	}
	return novo;
}

/*FUNÇÃO apagar_no(): Libera memória alocada por um nó;
@ARGUMENTOS:
-Ponteiro para um nó a ser apagado;
@RETORNO:
-Sendo um procedimento, a função não retorna;*/
void apagar_no(NO *no){
	if(no != NULL){
		no->esquerda = NULL;
		no->direita = NULL;
		free(no);
		no = NULL;
	}	
}

/*FUNÇÃO ler_no(): Lê e retorna um nó;
@ARGUMENTOS:
-Ponteiro para o nó que armazenará os dados lidos;
-Um caractere que indica o que foi lido;
@RETORNO:
-Sendo um procedimento, a função não retorna;*/
void ler_no(NO *no, char c){
	if((int)c >= 48 && (int)c <= 57){ /*É um número/operando. */
		fseek(stdin, -1L, SEEK_CUR);
		no->tipo = 1;
		scanf("%lf", &(no->info.operando));
	}else if(c=='(' || c==')' || c=='{' || c=='}' || c=='[' || c==']'){ /*É um delimitador*/
		no->tipo = 3;
	    no->info.delimitador = c;
	}else{ /*É um operador*/
	    no->tipo = 2;
	    no->info.operador = c;
	    if(c == '*'){ /*CASO ESPECIAL: CONFERIR '**': */
	    	scanf("%c", &c);
	    	if(c == '*') no->info.operador = 'p'; /*Chamo a operação '**' de p*/
	    	else fseek(stdin, -1L, SEEK_CUR);
	    }
	    else if(c == 'e' || c == 'l') scanf("%c%c", &c, &c); /*Pula "xp" ou "og"*/
	   	else if(c == 's') scanf("%c%c%c", &c, &c, &c); /*Pula "qrt"*/
	}
}

/*FUNÇÃO tipo_no(): Retorna o tipo do dado armazenado no nó;
@ARGUMENTOS:
-Ponteiro para o nó;
@RETORNO:
-O tipo do dado no nó;*/
int tipo_no(NO *no){
	return(no != NULL ? no->tipo : 0);
}

/*FUNÇÃO imprimir_no(): Imprime o conteúdo de um nó;
@ARGUMENTOS:
-Ponteiro para o nó;
@RETORNO:
-Sendo um procedimento, a função não retorna;*/
void imprimir_no(NO *no){
	switch(tipo_no(no)){
		case 1: printf("%.1lf ", no->info.operando);
			break;
		case 2: printf("%c ", no->info.operador);
			break;
		case 3: printf("%c ", no->info.delimitador);
			break;			
	}	
}

/*FUNÇÃO imprimir_recursivo(): Imprime nós de uma árvore e seus respectivos filhos recursivamente;
@ARGUMENTOS:
-Ponteiro para o nó;*/
void imprimir_recursivo(NO* no){	
	if(no == NULL) return;
	imprimir_no(no);
	imprimir_recursivo(no->esquerda);
	imprimir_recursivo(no->direita);
}

/*FUNÇÃO delimitador(): Retorna o dado armazenado no nó. Nesse caso, delimitador;
@ARGUMENTOS:
-Ponteiro para o nó;
@RETORNO:
-O dado do nó;*/
char delimitador(NO *no){
	if(no != NULL && tipo_no(no) == 3){
		return(no->info.delimitador);
	}
	return ' ';
}

/*FUNÇÃO delimitador_oposto(): Confere se dois delimitadores são relativamente opostos;
@ARGUMENTOS:
-Dois caracteres(delimitadores);
@RETORNO:
-Retorna 1 caso os delimitadores sejam opostos e 0 caso contrário;*/
int delimitador_oposto(char del1, char del2){
	if((del1=='{' && del2=='}') || (del1=='(' && del2==')') || (del1=='[' && del2==']'))
		return 1;
	return 0;
}

/*FUNÇÃO operador(): Retorna o dado armazenado no nó. Nesse caso, operador;
@ARGUMENTOS:
-Ponteiro para o nó;
@RETORNO:
-O dado do nó;*/
char operador(NO *no){
	return(no != NULL ? no->info.operador : ' ');
}

/*FUNÇÃO operando(): Retorna o dado armazenado no nó. Nesse caso, operando;
@ARGUMENTOS:
-Ponteiro para o nó;
@RETORNO:
-O dado do nó;*/
double operando(NO *no){
	return(no != NULL ? no->info.operando : -1);	
}

/*FUNÇÃO aponta_esquerda(): Faz o ponteiro para a esquerda de um nó apontar para outro;
@ARGUMENTOS:
-Ponteiros para os nós pai e filho;*/
void aponta_esquerda(NO *pai, NO *filho){
	if(pai != NULL && filho != NULL){
		pai->esquerda = filho;
	}
}

/*FUNÇÃO aponta_direita(): Faz o ponteiro para a direita de um nó apontar para outro;
@ARGUMENTOS:
-Ponteiros para os nós pai e filho;*/
void aponta_direita(NO *pai, NO *filho){
	if(pai != NULL && filho != NULL){
		pai->direita = filho;
	}
}

/*FUNÇÃO unario(): Confere se um nó possui um operador unário;
@ARGUMENTOS:
-Ponteiro para o nó;
@RETORNO:
-Retorna um caso seja um operador unário e 0 caso contrário;*/
int no_unario(NO *no){
	if(no != NULL && tipo_no(no) == 2){
		if(operador(no) == 'e' || operador(no) == 'l' || operador(no) == 's') return 1;
	}
	return 0;
}

/*FUNÇÃO resolve_no(): Resolve, recursivamente, um nó e seus filhos;
@ARGUMENTOS:
-Ponteiro para o nó e endereço para um inteiro que identifica se há algo incorreto;
@RETORNO:
-Vai retornando as soluções dos nós da árvore;*/
double resolve_no(NO *no, int *incorreta){
	if(no != NULL){
		double A, B;
		if(tipo_no(no) == 1)
			return operando(no);
		A = resolve_no(no->esquerda, incorreta);
		B = resolve_no(no->direita, incorreta);
		return calcular_no(A, B, no, incorreta); /*É um operador*/
	}
	return 0;	
}

/*FUNÇÃO calcular_no(): Resolve um nó folha com um operador e operando(os);
@ARGUMENTOS:
-Ponteiro para o nó e endereço para um inteiro que identifica se há algo incorreto, além de reais A e B;
@RETORNO:
-O resultado;*/
double calcular_no(double A, double B, NO *no, int *incorreta){
	double resultado;
	if(no_unario(no)){ /*Resolve só o A*/
		switch(operador(no)){
			case 'e': return exp(A);
			case 'l':
				resultado = log(A) / log(2);
				if(A <= 0) (*incorreta) = 1;
				//printf("res=%lf\n",resultado);
				return resultado;
			case 's':
				resultado = sqrt(A);	
				if(A < 0) (*incorreta) = 1; 
				//printf("res=%lf\n",resultado);
				return resultado;
		}
	}
	switch(operador(no)){
		case '+': return A + B;
		case '-': return A - B;
		case '*': return A * B;
		case '/': return A / B;
		case 'p': return pow(A, B);
	}
}

/*FUNÇÃO apagar_recursivamente(): apaga, recursivamente, os nós de uma árvore;
@ARGUMENTOS:
-Ponteiro para o nó;*/
void apaga_recursivamente(NO *no){
	if(no != NULL){
		apaga_recursivamente(no->esquerda);
		apaga_recursivamente(no->direita);
		free(no);
	}
}