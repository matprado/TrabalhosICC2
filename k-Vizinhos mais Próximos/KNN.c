/*	TRABALHO 2 DE ICC II
NOME: Mateus Prado Santos	
Nº USP: 10851707
PROFESSOR: Moacir Ponti
ICMC-USP

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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*Define struct flower que representará cada exemplo dos arquivos de treino e teste.*/
typedef struct flower FLOWER;
struct flower{
	double sl;
	double sw;
	double pl;
	double pw;
	char *specie;
	double dist;
};

/* Função 'read_line': lê e armazena todos os dados de uma linha do arquivo;
@Parâmetros:
-Um ponteiro para um arquivo;
@Retorno:
-Retorna um ponteiro para um tipo flower alocado na heap que contém todos os dados lidos na linha do arquivo; 
*/
FLOWER *read_line(FILE *fp){
	FLOWER *new = NULL;
	new = (FLOWER *) malloc(sizeof(FLOWER));
	new->specie = NULL;
	new->dist = 0;
	fscanf(fp, "%lf", &(new->sl));
	char c = fgetc(fp);	/*fgetc é usado para ignorar os caracteres , e "; */
	fscanf(fp, "%lf", &(new->sw));
	c = fgetc(fp);
	fscanf(fp, "%lf", &(new->pl));
	c = fgetc(fp);
	fscanf(fp, "%lf", &(new->pw));
	c = fgetc(fp);
	size_t size;
	c = fgetc(fp);
	getline(&(new->specie), &size, fp);
	new->specie[strlen(new->specie)-2] = '\0'; /*ATENÇÃO --> DEPOIS LIBERAR A STRING*/
	return new;
}

/* Função 'read_file': lê e armazena todos os dados de todas as linhas de um arquivo;
@Parâmetros:
-Um ponteiro para o endereço de um inteiro declarado na main para que possa ser modificado com sucesso.
 O inteiro representa o número de linhas "úteis" do arquivo;
@Retorno:
-Um vetor de ponteiros para o tipo flower, ou seja, todas as linhas/exemplos do arquivo;
*/
FLOWER **read_file(int *n_lines){
	FLOWER **vet = NULL;	
	/*Leitura do nome e abertura do arquivo:*/
	char file_name[10], c;
	fflush(stdin);
	scanf("%s", file_name);	
	FILE *fp;		
	if((fp = fopen(file_name, "r+")) == NULL){
		printf("Falha ao abrir arquivo para leitura.\n");
		return NULL;
	}
	/*PRIMEIRA LINHA DO ARQUIVO -> leitura dos atributos*/
	while((c=fgetc(fp)) != '\n'); /*pula uma linha*/
	while((c=fgetc(fp)) != EOF){
		fseek(fp, -1L, SEEK_CUR);
		vet = (FLOWER **) realloc(vet, ++(*n_lines) * sizeof(FLOWER *));
		vet[(*n_lines)-1] = read_line(fp);
	}
	/*TEM QUE LIBERAR TUDO DEPOIS EIN, LEMBRA QUE TEM VETOR DE STRINGS*/
	fclose(fp);
	return vet;
}

/* Função 'euclidean_distance': calcula a distância euclidiana entre os atributos de duas variáveis tipo flower;
@Parâmetros:
-Dois ponteiros do tipo flower;
@Retorno:
-Retorna a raiz quadrada da soma dos quadrados das diferenças entre os atributos dos argumentos, ou seja, sua distância euclidiana;
*/
double euclidean_distance(FLOWER *a, FLOWER *b){
	double sum = 0;
	sum += pow((a->sl - b->sl), 2);
	sum += pow((a->sw - b->sw), 2);
	sum += pow((a->pl - b->pl), 2);
	sum += pow((a->pw - b->pw), 2);
	return sqrt(sum);	
}

/* Função 'insertion_sort': ordena de forma crescente as distâncias de um vetor de ponteiros para flower;
@Parâmetros:
-Um vetor de ponteiros para flower;
-Um inteiro representando a quantidade de ponteiros no vetor;
@Retorno:
-Sendo um procedimento, não possui retorno;
*/
void insertion_sort(FLOWER **set, int n){
	int i=1, j; 
	FLOWER *key;
	while(i < n){
		j = i-1;
		key = set[i];
		while(j >= 0 && (key->dist < set[j]->dist)){
			set[j+1] = set[j];
			j--;
		}
		set[j+1] = key;
		i++;
	}	
}

/* Função 'specie_position': verifica a posição da espécie de um tipo flower em um vetor de espécies pré-determinado;
@Parâmetros:
-Um ponteiro para flower;
@Retorno:
-Retorna a posição descoberta;
*/
int specie_position(FLOWER *f){ 
	int pos;
	if(strcmp(f->specie, "setosa\0") == 0)
		pos = 0;
	else if(strcmp(f->specie, "virginica\0") == 0)
		pos = 1;
	else
		pos = 2;
	return pos;
}

/* Função 'biggest_pos': descobre a posição do vetor com o maior valor inteiro;
@Parâmetros:
-Um vetor de inteiros;
@Retorno:
-Retorna a posição descoberta;
*/
int biggest_pos(int *vet){
	int b=0, pos;
	for(int i=0; i<3; i++){
		if(vet[i] > b){
			b = vet[i];
			pos = i;
		}
	}
	return pos;
}


int main(int argc, char *argv[]){
	int n_train=0, n_test=0; 
	FLOWER **train_set = read_file(&n_train);
	FLOWER **test_set = read_file(&n_test);
	int k;
	scanf("%d", &k);
	/*Verifica se o k é válido*/
	if(k < 1 || k > n_train){
		printf("k is invalid\n");
		/*LIBERAÇÃO DE MEMÓRIA ALOCADA*/
		for(int i=0; i<n_test;i++){
			free(test_set[i]->specie);
			free(test_set[i]);
		}
		free(test_set);
		for(int i=0; i<n_train;i++){
			free(train_set[i]->specie);
			free(train_set[i]);
		}
		free(train_set);
		return 0;
	}
	int species_vet[3] = {0};
	/*	IMPORTANTE
	species_vet[0] --> espécie Setosa;
	species_vet[1] --> espécie Virginica;
	species_vet[2] --> espécie Versicolor;	
	*/
	int choosed, correct=0;
	for(int i=0; i<n_test; i++){
		/*Calcula todas as distâncias ordenando-as posteriormente:*/
		for(int j=0; j<n_train; j++){
			(train_set[j])->dist = euclidean_distance(train_set[j], test_set[i]);
		}
		insertion_sort(train_set, n_train);
		/*Faz a contagem das classes dos k vizinhos mais próximos*/
		for(int h=0; h<k; h++){
			species_vet[specie_position(train_set[h])]++;	
		}	
		/*Escolhe a espécie mais recorrente. Se tiver empate, usa a mais próxima:*/
		if(species_vet[0] == species_vet[1] || species_vet[1] == species_vet[2] || species_vet[0] == species_vet[2]){
			choosed = specie_position(train_set[0]);
		}	
		else
			choosed = biggest_pos(species_vet);
		/*Imprime a saída do programa contando o número de acertos*/
		switch(choosed){
			case 0:	
				printf("setosa ");
				printf("%s\n", (test_set[i])->specie);
				if(strcmp((test_set[i])->specie, "setosa\0") == 0)
					correct++;
				break;
			case 1:	
				printf("virginica ");
				printf("%s\n", (test_set[i])->specie);
				if(strcmp((test_set[i])->specie, "virginica\0") == 0)
					correct++;
				break;
			case 2:
				printf("versicolor ");
				printf("%s\n", (test_set[i])->specie);
				if(strcmp((test_set[i])->specie, "versicolor\0") == 0)
					correct++;
				break;
			}
		/*Zera o vetor para o próximo exemplo de teste*/			
		species_vet[0] = 0;
		species_vet[1] = 0;
		species_vet[2] = 0;		
	}
	/*Imprime taxa de acerto:*/
	printf("%.4lf\n", ((double)correct / (double)n_test));
	/*LIBERAÇÃO DE MEMÓRIA ALOCADA*/
	for(int i=0; i<n_test;i++){
		free(test_set[i]->specie);
		free(test_set[i]);
	}
	free(test_set);
	for(int i=0; i<n_train;i++){
		free(train_set[i]->specie);
		free(train_set[i]);
	}
	free(train_set);
	return 0;
}