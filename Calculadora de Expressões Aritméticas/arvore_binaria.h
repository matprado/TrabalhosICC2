#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H
#include "no.h"
#include "expressao.h"

typedef struct arvore ARVORE;

ARVORE *criar_arvore(void);
void apagar_arvore(ARVORE *arv);
NO *montar_arvore(EXPRESSAO *E, int ini, int fim, char *prioridade);
void construir_arvore_expressao(ARVORE *arv, EXPRESSAO *E, char *prioridade);
void imprimir_arvore(ARVORE *arv);
void resolve_arvore(ARVORE *arv);

#endif