/*TAD EXPRESSÃO:
ATENÇÃO: comentários estão no .c*/
#ifndef EXPRESSAO_H
#define EXPRESSAO_H
#include "no.h"
#include "pilha.h"

typedef struct expressao EXPRESSAO;

EXPRESSAO *criar_expressao(void);
void apagar_expressao(EXPRESSAO *E);
int ler_expressao(EXPRESSAO *E);
void imprimir_expressao(EXPRESSAO *E);
int expressao_mal_formada(EXPRESSAO *E);
int posicao_menor_prioridade(EXPRESSAO *E, int ini, int fim, char *prioridade);
NO *montar_arvore(EXPRESSAO *E, int ini, int fim, char *prioridade);
int tamanho_expressao(EXPRESSAO *E);
NO *buscar_no(EXPRESSAO *E, int pos);

#endif