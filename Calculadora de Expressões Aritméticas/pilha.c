#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

typedef struct no NO;

struct no{
	NO *anterior;
	TIPO valor;
};

struct pilha{
	NO *topo;
	int quantidade;
};

PILHA *pilha_criar(){
	PILHA *P = (PILHA *) malloc(sizeof(PILHA));
	if(P != NULL){
		P->topo = NULL;
		P->quantidade = 0;
	}else P = NULL;
	return P;
}
	
void pilha_apagar(PILHA **P){
	NO *paux;
	if((*P) != NULL && !pilha_vazia(*P)){
		while((*P)->topo != NULL){
			paux = (*P)->topo;
			(*P)->topo = (*P)->topo->anterior;
			paux->anterior = NULL;
			free(paux);
		}
	}
	free(*P);
	*P = NULL;
}

int pilha_vazia(PILHA *P){
	return ((P != NULL) ? P->quantidade == 0 : ERRO);
}

TIPO pilha_topo(PILHA *P){
	/*TIPO t = P->vet[quantidade-1];*/
	return ((P != NULL && !pilha_vazia(P)) ? P->topo->valor : ERRO);
}

int pilha_tamanho(PILHA *P){
	return ((P != NULL) ? P->quantidade : ERRO);
}

void pilha_empilhar(PILHA *P, TIPO n){
	NO *pnovo = (NO *) malloc(sizeof(NO));
	if(pnovo != NULL && P != NULL){
		pnovo->valor = n;
		pnovo->anterior = P->topo;
		P->topo = pnovo;
		P->quantidade++;
	}
}

TIPO pilha_desempilhar(PILHA *P){
	TIPO n;
	NO *pnovo;
	if(pnovo != NULL && !pilha_vazia(P)){
		n = P->topo->valor;
		pnovo = P->topo;
		P->topo = P->topo->anterior;
		pnovo->anterior = NULL;
		free(pnovo);
		pnovo = NULL;
		P->quantidade--;
	}else n = ERRO;
	return n;
}	

int pilha_maior(PILHA *P1, PILHA *P2){
	return ((P1 != NULL && P2 != NULL) ? (P1->quantidade > P2->quantidade) : 0);
}