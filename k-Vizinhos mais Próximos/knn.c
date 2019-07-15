/*	TRABALHO 2 DE ICC II
NOME: Mateus Prado Santos	
Nº USP: 10851707
PROFESSOR: Moacir Ponti
ICMC-USP
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Descrição do programa:
	Este programa utiliza o algoritmo de Machine Learning "k Nearest Neighbours"(kNN)
	que indica os k vizinhos mais próximos de um determinado dado. Nesse caso, os dados
	são sobre espécies da flor Íris.

Algoritmo kNN:

Entrada: Conjunto de dados - D, novo exemplo - ex, número de vizinhos - k
Saı́da: Classe para ex

--Calcular a distância de ex para cada exemplo em D;
--Determinar o conjunto Q dos k 0 s exemplos em D mais próximos de ex;
--Verificar a classe que é mais representativa em Q;
--Retornar essa classe como a classe de ex;
*/
char *read_line(FILE *fp);
char **split_string(char *string, char *dont_want, int pieces);
void free_string_vet(char **vet, int n);
FLOWER *read_file(int *n_lines);

typedef struct flor FLOWER;
struct flower{
	double sl;
	double sw;
	double pl;
	double pw;
	char *specie;
};

int main(int argc, char *argv[]){
	int n_lines=0; 
	FLOWER *train = read_file(&n_lines);


	return 0;
}


char *read_line(FILE *fp){
	char* vet = NULL;
	int i = 0;
	char c;
	do{
		vet = (char*)realloc(vet, sizeof(char) * ++i);
		c = fgetc(fp);
		vet[i-1] = c;
	}while(vet[i-1] != '\n' && vet[i-1] != '\r' && vet[i-1] != EOF);
	if(vet[i-1] == '\r') fgetc(fp);
	vet[i-1] = '\0';
	return vet; 
}

char **split_string(char *string, char *dont_want, int pieces){
	char *token;
	char **result = (char **) malloc(pieces * sizeof(char *));
	for(int i=0; i<pieces;i++) result[i] = (char *) malloc(20 * sizeof(char));
	int n=0;
	if(string != NULL && dont_want != NULL){
		token = strtok(string, dont_want);
		while(token != NULL){
			//result = (char**) realloc(result, ++size * sizeof(char*));
			//printf("%s\n", dont_want);
			strcpy(result[n++], token);
			printf("%s\n", result[n-1]);
  		    token = strtok(NULL, dont_want);
   		}
	}
	return result;
}

void free_string_vet(char **vet, int n){
	for(int i=0; i<n; i++){
		//printf("%s\n", vet[i]);
		free(vet[i]);
	}
	free(vet);
}

/*double distancia_euclidiana( , ){


}*/

FLOWER *read_file(int *n_lines){
	FLOWER *vet = NULL;	
	/*Leitura do nome e abertura do arquivo:*/
	char file_name[10];
	scanf("%s", file_name);	
	FILE *fp;		
	if((fp = fopen(file_name, "r+")) == NULL){
		printf("Falha ao abrir arquivo para leitura.\n");
		return 1;
	}
	char **examples, *dont_want;
	dont_want = malloc(2 * sizeof(char));
	strcpy(dont_want, "\",");
	int pieces=5;
	/*PRIMEIRA LINHA DO ARQUIVO -> leitura dos atributos*/
	char *line = read_line(fp);
	//atributes = split_string(line, dont_want, pieces);
	free(line);
	line = NULL;
	while(!feof(fp)){
		line = read_line(fp);
		examples = split_string(line, dont_want, pieces);
		vet = (FLOWER *) realloc(vet, ++(*n_lines) * sizeof(FLOWER));
		for(int i=0; i<pieces; i++){
			vet[(*n_lines)-1]->sl = atodexamples[i];	
		}
		free_string_vet(examples, pieces);
		examples = NULL;	
		free(line);
		line = NULL;
	}
	/*TEM QUE LIBERAR TUDO DEPOIS EIN, LEMBRA QUE TEM VETOR DE STRINGS*/
	free_string_vet(atributes, pieces);
	free(dont_want);
	fclose(fp);


	return 
}
