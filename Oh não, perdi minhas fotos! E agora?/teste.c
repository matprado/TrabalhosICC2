#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1
 
void salvar_imagem(int n_img, unsigned char *imagem, int n_bytes){
	char nome[sizeof "000.jpg"];
	sprintf(nome, "%03d.jpg", n_img);
	if(DEBUG) printf("%s", nome);
	FILE *fp = fopen(nome, "wb+");
	fwrite(imagem, sizeof(unsigned char), n_bytes * sizeof(unsigned char), fp);
	if(DEBUG) printf("imagem salva");
	fclose(fp);
}

int main(int argc, char *argv[]){
	unsigned char *imagem = (unsigned char*) malloc(4 * sizeof(unsigned char)); 
	unsigned char *aux = (unsigned char*) malloc(4 * sizeof(unsigned char));
	int n_img=0;
	int n_bytes=0;
	for(int i = 0; i < 4; i++){
		imagem[i] = getchar();
	}
	while(!feof(stdin)){
		if(n_bytes == 4){
			if(DEBUG) printf("imagem nula");
			for(int i=4; i<508; i++){
				imagem = (unsigned char*)realloc(imagem, ++n_bytes * sizeof(unsigned char));
				imagem[i] = getchar();
			}
		}else{
			for(int i=0; i<4; i++){
				aux[i] = getchar();
			}
			if(aux[0] == imagem[0] && aux[1] == imagem[1] && aux[2] == imagem[2] && aux[3] == imagem[3]){
				if(DEBUG) printf("ACHOU UMA IMAGEM");
				salvar_imagem(++n_img, imagem, n_bytes);
				free(imagem);
				imagem = (unsigned char*) malloc(4 * sizeof(unsigned char));
				for(int i = 0; i < 4; i++){
					imagem[i] = aux[i];
				}
				n_bytes = 4;
			}else{
				if(DEBUG) printf("continuou");
				for(int i=0; i<508; i++){
					imagem = (unsigned char*)realloc(imagem, ++n_bytes * sizeof(unsigned char));
					imagem[n_bytes+i] = getchar();
				}
			}	
		}	
	}
	salvar_imagem(++n_img, imagem, n_bytes);
	free(imagem);
	free(aux);
	return 0;
 }