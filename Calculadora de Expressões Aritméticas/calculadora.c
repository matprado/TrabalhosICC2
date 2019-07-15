/*
-----TRABALHO 4-ICC 2----
ALUNO: Mateus Prado Santos	
NÚMERO USP: 10851707
PROFESSOR: Moacir Ponti	
	Este código utiliza árvore binária para calcular uma expressão aritmética de acordo com
	uma ordem de prioridades pré-estabelecidas;
	ICMC-USP 2018.
*/
#include <stdlib.h>
#include <stdio.h>
#include "expressao.h" /*Inclusão do TAD expressao*/
#include "arvore_binaria.h" /*Inclusão da estrutura de dados arvore_binaria*/

int main(void){
	char prioridade[8], barra_n;
	/*As maiores prioridades são as operações unárias:*/
	prioridade[0] = 'e';
	prioridade[1] = 'l';
	prioridade[2] = 's';
	for(int i=3; i<8; i++){
		scanf("%c%c", &prioridade[i], &barra_n);10392230
		if(barra_n == '*'){
			prioridade[i] = 'p'; /*chamo '**' de 'p' */
			scanf("%c", &barra_n);		
		}
	}
	ARVORE *arv;
	scanf("%c", &barra_n);
	EXPRESSAO *exp;
	while(ler_expressao(exp = criar_expressao())){ /*Lê todas as expressões*/
		scanf("%c", &barra_n);
		fflush(stdin);
		if(expressao_mal_formada(exp)) printf("Expressao incorreta.\n"); /*Confere se os delimitadores estão corretos*/
		else{
			arv = criar_arvore();
			construir_arvore_expressao(arv, exp, prioridade);
			resolve_arvore(arv);
			free(arv);
		}	
		apagar_expressao(exp); /*Desaloca memória*/
		//apagar_arvore(arv);
	}
	scanf("%c", &barra_n);
	fflush(stdin);
	if(expressao_mal_formada(exp)) printf("Expressao incorreta.\n"); /*Confere se os delimitadores estão corretos*/
	else{
		arv = criar_arvore();
		construir_arvore_expressao(arv, exp, prioridade);
		resolve_arvore(arv);	
		free(arv);
	}	
	apagar_expressao(exp); /*Desaloca memória*/
	//apagar_arvore(arv);	
	return 0;
}