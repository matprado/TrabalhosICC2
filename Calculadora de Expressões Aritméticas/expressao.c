#include <stdio.h>
#include <stdlib.h>
#include "expressao.h"

/*ESTRUTURA expressao:
@CAMPOS:
-Vetor de ponteiros para nós;
-Quantidade de ponteiros no vetor;*/
struct expressao{
	NO *exp[1000];
	int quantidade;
};

/*FUNÇÃO criar_expressao(): Cria uma expressão;
@ARGUMENTOS:
-Não possui argumento;
@RETORNO:
-Se existir memória disponível, retorna um ponteiro para a expressão criada;*/
EXPRESSAO *criar_expressao(void){
	EXPRESSAO *nova = (EXPRESSAO *)malloc(sizeof(EXPRESSAO));
	if(nova != NULL){
		nova->quantidade = 0;
		for(int i=0; i<1000; i++){
			nova->exp[i] = NULL;
		}
	}	
	return nova;
}

/*FUNÇÃO apagar_expressao(): Libera memória alocada por uma expressão;
@ARGUMENTOS:
-Ponteiro para a expressão a ser apagada;
@RETORNO:
-Sendo um procedimento, a função não retorna;*/
void apagar_expressao(EXPRESSAO *E){
	if(E != NULL){
		for(int i=0; i<E->quantidade; i++){
			apagar_no(E->exp[i]);
		}
		free(E);
	}	
	E = NULL;
}

/*FUNÇÃO ler_expressao(): Lê e armazena uma expressão;
@ARGUMENTOS:
-Ponteiro para a expressão que armazenará os dados lidos;
@RETORNO:
-Retorna 1 se parar de ler com ',' e 0 se parar de ler com ';';*/
int ler_expressao(EXPRESSAO *E){
	/*PARA QUANDO LÊ ',' OU ';'.*/
	char c;
	int i=0;
	scanf("%c", &c);
	while(c != ',' && c != ';'){
		E->quantidade++;
		E->exp[i] = criar_no();
	    ler_no(E->exp[i], c); 
	    scanf("%c", &c);
	    i++;	
	}
	if(c == ',') return 1;
	return 0;
}

/*FUNÇÃO imprimir_expressao(): Imprime uma expressão;
@ARGUMENTOS:
-Ponteiro para a expressão que será imprimida;
@RETORNO:
-Sendo um procedimento, a função não retorna;*/
void imprimir_expressao(EXPRESSAO *E){
	if(E != NULL){
		for(int i=0; i<E->quantidade; i++){
			imprimir_no(E->exp[i]);
		}
		printf("\n");
	}
}


/*FUNÇÃO expressao_mal_formada(): Verifica se uma expressão é mal-formada;
@ARGUMENTOS:
-Ponteiro para a expressão a ser analisada;
@RETORNO:
-Retorna 1 se a expressão é mal-formada e 0 caso contrário;*/
int expressao_mal_formada(EXPRESSAO *E){
	PILHA *P = pilha_criar();
	char del_atual, del_anterior;
	for(int i=0; i<E->quantidade; i++){
		if(tipo_no(E->exp[i]) == 3){ /*É um delimitador*/
			del_atual = delimitador(E->exp[i]);
			/*Empilha o delimitador de abertura:*/
			if(del_atual == '(' || del_atual == '[' || del_atual == '{') pilha_empilhar(P, del_atual);
			/*Desempilha último delimitador de abertura empilhado e verifica se é igual ao delimitador de encerramento atual:*/
			else{
				if(!pilha_vazia(P)){
					del_anterior = pilha_desempilhar(P);
					if(!delimitador_oposto(del_anterior, del_atual)) /*Confere se não é o delimitador oposto. EX: '{' e ')'.*/
						return 1; /*A expressão é mal-formada!*/
				}
				else return 1;	/*Confere se há mais de encerramento do que de abertura*/
			}
		}
		/*Confere operador duplo:*/
		else if((tipo_no(E->exp[i]) == 2) && (tipo_no(E->exp[i+1]) == 2) && !(no_unario(E->exp[i+1]))){
			return 1; 	
		}
	}
	if(!pilha_vazia(P)) return 1; /*Confere se há mais de abertura do que de encerramento*/		
	pilha_apagar(&P);
	return 0; /*A expressão não é mal-formada*/
}


/*FUNÇÃO posicao_menor_prioridade(): Retorna a posição do elemento de menor prioridade na expressão
(considerando que operadores possuem mais prioridade que operandos);
@ARGUMENTOS:
-Ponteiro para a expressão a ser analisada;
-Posições de inicio e fim da expressão;
-Vetor de prioridade das operações;
@RETORNO:
-Retorna a posição da menor prioridade;*/
int posicao_menor_prioridade(EXPRESSAO *E, int ini, int fim, char *prioridade){
	int pos_del=ini, repete=1, aux;
	while(tipo_no(E->exp[ini]) == 3){
		while(repete != 0 && pos_del <= fim){
			while(!delimitador_oposto(delimitador(E->exp[ini]), delimitador(E->exp[pos_del])) && pos_del <= fim){
				pos_del++; /*encontrando posicao do delimitador oposto*/
				if(delimitador(E->exp[ini]) == delimitador(E->exp[pos_del]))
					repete++;
			}
			repete--;
			pos_del++;
		}
		if(pos_del == fim){/*O delimitador cobre todo o intervalo*/
			ini++;
			fim--;
		}else if(pos_del > fim){
			ini++; /*Nesse caso, pula apenas o delimitador de abertura pois não há oposto;*/
		}
		else{
			aux = pos_del;
			while(tipo_no(E->exp[aux]) == 3 && aux < fim){
				aux++;
			}
			if(aux == fim){
				ini++;
				fim--;
			}	
			else ini = pos_del; /* O início é depois do delimitador*/
		}
		pos_del = ini;
		repete=1;	
	}
	for(int j=7; j>=0; j--){ /*Começa da pior prioridade, lembrando que a ordem(crescente) é: exp, log, sqrt, binários...*/	
		for(int i=ini; i<fim; i++){
			if((tipo_no(E->exp[i])==3) && (delimitador(E->exp[i])=='{' || delimitador(E->exp[i])=='(' || delimitador(E->exp[i])=='[')){ 
			/*Pula delimitador interno(quero MENOR prioridade)*/
				repete = 1;
				while(repete != 0 && i <= fim){
					pos_del = i;
					while(!delimitador_oposto(delimitador(E->exp[pos_del]), delimitador(E->exp[i])) && i <= fim){ 
						i++; /*i=posicao do delimitador oposto*/
						if(delimitador(E->exp[pos_del]) == delimitador(E->exp[i])) repete++;
					}
					repete--;
				}
			}
			if(tipo_no(E->exp[i]) == 1) i++;
			if(tipo_no(E->exp[i]) == 2)
				if(operador(E->exp[i]) == prioridade[j]){
					return i;
				}
		}
	}
	/*Se chegou até aqui, não há mais operadores. Falta retornar o, então, operando*/
	return ini; /* INI == FIM */
}

/*FUNÇÃO tamanho_expressao(): Fornece o tamanho de uma dada expressão;
@ARGUMENTOS:
-Ponteiro para a expressão;
@RETORNO:
-Retorna a quantidade de elementos da expressão;*/
int tamanho_expressao(EXPRESSAO *E){
	return (E != NULL ? E->quantidade : 0);
}

/*FUNÇÃO buscar_no(): Retorna um nó(elemento) da expressão em uma determinada posição;
@ARGUMENTOS:
-Ponteiro para a expressão;
-Posição do nó;
@RETORNO:
-Retorna o nó;*/
NO *buscar_no(EXPRESSAO *E, int pos){
	return ((E != NULL && pos < E->quantidade) ? E->exp[pos] : NULL);
}