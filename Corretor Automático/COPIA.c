/*	TRABALHO 3 DE ICC 2
-ALUNO: Mateus Prado Santos		
-PROFESSOR: Moacir Ponti
-ICMC - USP			
	Este programa armazena tweets imprimindo palavras "incorretas" do mesmo a partir de uma 
	fonte, que também é armazenada, de um livro, ou seja, as tais palavras "incorretas" são
	palavras do tweet que não aparecem no livro fonte; 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estrutura 'dicionario' possui um vetor de strings e um inteiro que contem a quantidade de strings*/
typedef struct{
	char **palavras;
	int quantidade;	
}dicionario;

/* Definições de maximidade*/
#define MAX_PALAVRAS 100000
#define MAX_LETRAS 46
#define MAX_TWEETS 280

/* Função 'merge: intercala dois vetores ordenando-os gerando um único ordenado;
@ Parâmetros:
- vetor	de strings;
- inteiros que representam as posições de inicio e fim; 
@ Retorno:
- Sendo um procedimento, a função não retorna; 
*/
void merge(char **vet, int ini, int meio, int fim){
	char **aux = (char **)malloc((fim-ini+1) * sizeof(char *));
	for(int n=0; n<(fim-ini+1); n++){
		aux[n] = (char*) malloc(MAX_LETRAS * sizeof(char));
	}
	int i, j, k;	
    for(i=ini, j=meio+1, k=0; i<=meio && j<=fim; k++){	//Ordena os dois 'blocos'
    	if(strcmp(vet[i], vet[j]) < 0)
    		strcpy(aux[k], vet[i++]);
    	else
    		strcpy(aux[k], vet[j++]);
    }
    while(i <= meio){  //Caso ainda haja elementos na primeira metade
    	strcpy(aux[k++], vet[i++]);
    }
    while(j <= fim){   //Caso ainda haja elementos na segunda metade
    	strcpy(aux[k++], vet[j++]);
    }
    for(k = ini; k <= fim; k++){//Move os elementos de volta para o vetor original
        strcpy(vet[k], aux[k-ini]);
    }
    for(int n=0; n<(fim-ini+1); n++){
		free(aux[n]);
	}
    free(aux);
}

/* Função 'merge_sort: ordena, recursivamente, um vetor de palavras;
@ Parâmetros:
- vetor	de strings;
- inteiros que representam as posições de inicio e fim; 
@ Retorno:
- Sendo um procedimento, a função não retorna; 
*/
void merge_sort(char **vet, int ini, int fim){
	if(fim <= ini)	return;
	int meio = (int) (ini+fim)/2;	
	merge_sort(vet, ini, meio);
	merge_sort(vet, meio+1, fim);
	merge(vet, ini, meio, fim);
}

/* Função 'ler_palavra': lê e retorna uma palavra ignorando acentos/caracteres especiais;
@ Parâmetros:
- ponteiro para um arquivo de leitura; && ((i && ((int)p1[i] != ((int)p2[j]+32)) && ((int)p1[i] != ((int)p2[j]-32)) && ((int)p1[i] != ((int)p2[j]+32)) && ((int)p1[i] != ((int)p2[j]-32))nt)p1[i] != ((int)p2[j]+32)) && ((int)p1[i] != ((int)p2[j]-32))
- caractere que indica condição de parada; 
@ Retorno:
- retorna a palavra lida; 
*/
char *ler_palavra(FILE *arq, char PARA){
	char *string = (char *) malloc(MAX_LETRAS * sizeof(char));
	int qtd = 0, ascii;
	int c = fgetc(arq);
	/*conferir se há caractere especial no começo:*/           
	ascii = (int)c;
	while((ascii < 65 || (ascii > 90 && ascii < 97) || ascii > 122) && c != EOF){
		c = fgetc(arq);
		ascii = (int)c;	
	}
	/*agora confere o final da palavra*/
	while(((ascii >= 65 && ascii <= 90) || (ascii >= 97 && ascii <= 122)) && c != PARA){
		//if(ascii <= 90)	c = (char)(ascii + 32);  		
		string[qtd++] = (char)c;
		c = fgetc(arq);
		ascii = (int)c;	
	}
	string[qtd] = '\0';
	return string;		
}

/* Função 'ler_livro: lê, armazena e ordena, em um vetor, todas as palavras de um arquivo, removendo repetições;
@ Parâmetros:
- Ponteiro para a estrutura dicionário;
- Ponteiro para arquivo de leitura; 
@ Retorno:
- Sendo um procedimento, a função não retorna; 
*/
void ler_livro(dicionario *D, FILE *arq){
	char c, **vet_aux = (char **) malloc(MAX_PALAVRAS * sizeof(char*));
	int n=0, i=0;
	/* Lê e armazena todas as palavras:*/
	while((c=fgetc(arq)) != EOF){
		fseek(arq, -1L, SEEK_CUR);
		vet_aux[n++] = ler_palavra(arq, EOF);
	}
	/*Ordena as palavras:*/
	merge_sort(vet_aux, 0, n-1);
	/*Retira as repetições:*/
	while(i != n){
		D->palavras[D->quantidade++] = vet_aux[i++];
		if(i != n){
			while(strcmp(D->palavras[D->quantidade-1], vet_aux[i]) == 0 && i+1 != n){ 
				free(vet_aux[i++]);
			}
		}	
	}
	free(vet_aux);
}

/* Função 'ler_tweets: procura e lê todos os tweets de um arquivo;
@ Parâmetros:
- Ponteiro para arquivo de leitura;
- Ponteiro para inteiro alocado na main para ser modificado com sucesso; 
@ Retorno:
- retorna um vetor de dicionarios, onde cada um deles é um tweet diferente;
*/
dicionario *ler_tweets(FILE *arq, int *n){
	dicionario *twitter = NULL;
	char c;
	//size_t size;
	while((c = fgetc(arq)) != EOF){
		while(c == ' '){
			c = fgetc(arq);
		}
		//printf("C = %c\n", c);
		if(c == '"' && (c = fgetc(arq)) == 't' && (c = fgetc(arq)) == 'e' && (c = fgetc(arq)) == 'x' && (c = fgetc(arq)) == 't'){
			twitter = (dicionario *) realloc(twitter, ++(*n) * sizeof(dicionario));
			twitter[(*n)-1].palavras = (char **) malloc(280 * sizeof(char*));
			twitter[(*n)-1].quantidade = 0;
			c = fgetc(arq); // '"'
			c = fgetc(arq); // ':'
			c = fgetc(arq); // ' '
			c = fgetc(arq); // '"'
			while((c = fgetc(arq)) != '"' && c != '\n'){
				//printf("c = %c\n", c);
				fseek(arq, -1L, SEEK_CUR);
				twitter[(*n)-1].palavras[(twitter[(*n)-1].quantidade)++] = ler_palavra(arq, '\n');
				if(strcmp(twitter[(*n)-1].palavras[(twitter[(*n)-1].quantidade)-1], "truncated\0") == 0){
					free(twitter[(*n)-1].palavras[(twitter[(*n)-1].quantidade)-1]);
					twitter[(*n)-1].quantidade--;
				}	
				//printf("PALAVRA = %s\n", (twitter[(*n)-1].palavras)[(twitter[(*n)-1].quantidade)-1]);
				fseek(arq, -1L, SEEK_CUR);
			}
		}else{
			while(c != '\n' && c != EOF){
				c = fgetc(arq);
			}
		}
	}
	return twitter;
}

/* Função 'maiuscula': se o argumento for uma letra minúscula, retorna ela maiúscula;
@ Parâmetros:
- um char;
@ Retorno:
- char convertido;
*/
char maiuscula(char c){
	int ascii = (int)c;
	if(ascii >= 97 && ascii <= 122) c = (char)(ascii - 32);
	return c; 
}

/* Função 'compara_palavras: funciona como o strcmp, só que ignorando a diferenca entre uma letra maiuscula e minuscula;
@ Parâmetros:
- Duas strings;
@ Retorno:
- retorna 0 se as palavras são iguais, negativo se a primeira vem antes no alfabeto e positivo caso contrário;
*/
int compara_palavras(char *p1, char *p2){
	int s1 = strlen(p1), s2 = strlen(p2);
	for(int i=0, j=0; i<s1 && j<s2; i++, j++){
		if(maiuscula(p1[i]) != maiuscula(p2[j])){
			return (int)p1[i] - (int)p2[j];
		}
	}
	return (s1 == s2 ? 0 : s1 - s2);
}


/* Função 'busca_binaria: busca uma palavra dentre um vetor de palavras ordenado;
@ Parâmetros:
- vetor	de strings;
- string chave a ser procurada; 
@ Retorno:
- A função retorna a posição da palavra no vetor ao encontrá-la. Caso não encontre, retorna negativo; 
*/
int busca_binaria(char **vet, char *chave, int ini, int fim){
	if(ini > fim) return -1;
	int meio = (ini + fim) / 2;
	if(compara_palavras(chave, vet[meio]) == 0) return meio;
	else{
		if(compara_palavras(chave, vet[meio]) < 0) return busca_binaria(vet, chave, ini, meio-1);
		else return busca_binaria(vet, chave, meio+1, fim);
	}
}

/* Função 'conferir_erros: confere os erros nos tweets com base em um livro fonte;
@ Parâmetros:
- um dicionario livro;
- um vetor de dicionarios, um para cada tweet; 
@ Retorno:
- Sendo um procedimento, a função não retorna; 
*/
void conferir_erros(dicionario livro, dicionario *tweets, int n_tweets){
	for(int i=0; i<n_tweets; i++){
		for(int j=0; j<tweets[i].quantidade; j++){
			if(busca_binaria(livro.palavras, tweets[i].palavras[j], 0, livro.quantidade-1) < 0){
				printf("%s ", tweets[i].palavras[j]);
			}
		}
		printf("\n");
	}
}

int main(void){
	/*Processo de abertura dos arquivos:*/
	FILE *arq_livro, *arq_twitter;
	char nome_arq[20];
	int n_tweets = 0;	
	scanf("%s", nome_arq);
	nome_arq[strlen(nome_arq)] = '\0';
	fflush(stdin);
	if((arq_livro = fopen(nome_arq, "r")) == NULL){
		printf("No book to check\n");
		return 0;
	}
	scanf("%s", nome_arq);
	nome_arq[strlen(nome_arq)] = '\0';
	fflush(stdin);
	if((arq_twitter = fopen(nome_arq, "r")) == NULL){
		printf("No tweets to check\n");
		return 0;
	}
	
	/* Processo de leitura e procura de erros:*/
	dicionario livro, *tweets;
	livro.quantidade = 0;
	livro.palavras = (char **) malloc(MAX_PALAVRAS * sizeof(char*));
	ler_livro(&livro, arq_livro);
	tweets = ler_tweets(arq_twitter, &n_tweets);
	conferir_erros(livro, tweets, n_tweets);
	
	/* Liberação de memória e fechamento de arquivos:*/
	fclose(arq_livro);
	for(int i=0; i<n_tweets; i++){
		for(int j=0; j<tweets[i].quantidade; j++){
			free(tweets[i].palavras[j]);
		}
	}
	free(tweets);
	for(int i=0; i<livro.quantidade; i++){
		//printf("%s\n", livro.palavras[i]);
		free(livro.palavras[i]);
	}
	free(livro.palavras);
	return 0;
}