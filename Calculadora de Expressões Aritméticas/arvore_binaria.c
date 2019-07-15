#include <stdio.h>
#include <stdlib.h>
#include "arvore_binaria.h"

struct arvore{
	NO *raiz;
};

ARVORE *criar_arvore(void){
	ARVORE *nova = (ARVORE *) malloc(sizeof(ARVORE));
	if(nova != NULL){
		nova->raiz = NULL;
	}
	return nova;
}

void apagar_arvore(ARVORE *arv){
	if(arv != NULL){
		apaga_recursivamente(arv->raiz);
		free(arv);
	}
}

/* PROCESSO PARA PROCURA:*/
NO *montar_arvore(EXPRESSAO *E, int ini, int fim, char *prioridade){
	if(ini==fim) return buscar_no(E, ini);
	if(ini>fim) return NULL;
	int pos = posicao_menor_prioridade(E, ini, fim, prioridade);
	if(tipo_no(buscar_no(E, pos)) == 1){
		return buscar_no(E, pos);
	}else if(tipo_no(buscar_no(E, pos)) == 2){
		if(no_unario(buscar_no(E, pos))){
			aponta_esquerda(buscar_no(E, pos), montar_arvore(E, pos+1, fim, prioridade));
		}else{
			aponta_esquerda(buscar_no(E, pos), montar_arvore(E, ini, pos-1, prioridade));
			aponta_direita(buscar_no(E, pos), montar_arvore(E, pos+1, fim, prioridade));
		}
		return buscar_no(E, pos);
	}
	return NULL;
}	

void construir_arvore_expressao(ARVORE *arv, EXPRESSAO *E, char *prioridade){
	if(arv != NULL && E != NULL){
		arv->raiz = montar_arvore(E, 0, tamanho_expressao(E)-1, prioridade);
	}
}

void imprimir_arvore(ARVORE *arv){	
	imprimir_recursivo(arv->raiz);
	printf("\n");
}

void resolve_arvore(ARVORE *arv){
	double resultado;
	int incorreta = 0;
	resultado = resolve_no(arv->raiz, &incorreta);
	if(incorreta == 1)
		printf("Expressao incorreta.\n");
	else
		printf("%.2lf\n", resultado);	
}