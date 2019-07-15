#ifndef PILHA_H
#define PILHA_H

#define TIPO char
#define ERRO ' '

typedef struct pilha PILHA;
PILHA *pilha_criar();	
void pilha_apagar(PILHA **P);
int pilha_vazia(PILHA *P);
TIPO pilha_topo(PILHA *P);
int pilha_tamanho(PILHA *P);
void pilha_empilhar(PILHA *P, TIPO n);
TIPO pilha_desempilhar(PILHA *P);		
int pilha_maior(PILHA *P1, PILHA *P2);

#endif