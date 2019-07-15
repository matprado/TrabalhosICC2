// Trabalho I de ICC 2
// Aluno: Mateus Prado Santos
// Professor: Moacir Ponti
// Este código recebe de entrada um arquivo e procura por imagens que serão salvadas na pasta de origem;
// ICMC-USP-SC, 2º Semestre, 2018;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

void leitura_inicial(unsigned char *vet){
	//fread(vet, 4 * sizeof(char), sizeof(char), stdin);
	for(int i = 0; i < 4; i++){
		vet[i] = getchar();
	}
}

void copia_bytes(unsigned char *origem, unsigned char *destino, int n_bytes){
	for(int i = 0; i < 4; i++){
		destino[i + n_bytes] = origem[i];
	}
}

void leitura_de_bloco(unsigned char *vet, int n_bytes){
	//fread((vet+(n_bytes * sizeof(char))), 508 * sizeof(char), sizeof(char), stdin);	
	for(int i = n_bytes; i < (508 + n_bytes); i++){
		vet[i] = getchar();
	}
	if(DEBUG) printf("li tudo");
}

void salva_imagem(unsigned char *img, int n_bytes, int n_img){
	char nome[7];
	//strcpy("xxx\0", nome);
	sprintf(nome, "%03d.jpg", n_img);
	FILE *fpw = fopen(nome, "wb+");
	fwrite(img, sizeof(unsigned char), n_bytes * sizeof(unsigned char), fpw);
	fclose(fpw);
}

int verifica(unsigned char *jpg, unsigned char *teste){
	int n = 0;
	for(int i = 0; i < 4; i++){
		if(jpg[i] == teste[i])	n++;
	}
	if(n == 4){
		return 1;
	}else{	
		return 0;
	}	
}

int main(int argc, char *agrv[]){
	unsigned char *jpg = (unsigned char*) malloc(4 * sizeof(unsigned char));
	unsigned char *teste = (unsigned char*) malloc(4 * sizeof(unsigned char));
	unsigned char *img = NULL;
	int nova = 1;
	int n = 0;
	int n_img = 0;
	int n_bytes = 0;
	while(!feof(stdin)){
		
		if(n == 0){
			leitura_inicial(jpg);	
			n++;
		}else if(n == 1){			
			leitura_inicial(teste);
			n++;
		}


		if(nova){
			img = (unsigned char*) realloc(img, 512 * sizeof(unsigned char));
			copia_bytes(jpg, img, 0);
			n_bytes += 4;
			leitura_de_bloco(img, n_bytes);
			n_bytes += 508;
			leitura_inicial(teste);
			if(verifica(jpg, teste)){
				nova = 1;
				salva_imagem(img, n_bytes, ++n_img);
				free(img);
				img = NULL;
				n_bytes = 0;
			}else{
				nova = 0;
			}
		}else{
			printf("continuou");
			img = (unsigned char*) realloc(img, (n_bytes+512) * sizeof(unsigned char));
			copia_bytes(jpg, img, n_bytes);
			n_bytes += 4;
			leitura_de_bloco(img, n_bytes);
			n_bytes += 508;
			leitura_inicial(teste);
			if(verifica(jpg, teste)){
				nova = 1;
				salva_imagem(img, n_bytes, ++n_img);
				free(img);
				img = NULL;
				n_bytes = 0;
			}else{
				nova = 0;
			}
		}
	}

	free(img);
	free(jpg);
	free(teste);
	return 0;
}