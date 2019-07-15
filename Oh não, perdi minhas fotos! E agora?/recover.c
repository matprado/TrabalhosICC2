/* Trabalho I de ICC 2
 Aluno: Mateus Prado Santos
 Nº USP: 10851707
 Professor: Moacir Ponti
 Este código recebe de entrada uma memória "bagunçada" de uma câmera fotográfica e procura por imagens que serão salvas na pasta de origem;
 ICMC-USP-SC, 2º Semestre, 2018;
*/
#include <stdio.h>
#include <stdlib.h>

/*
Função salvar_imagem:
	recebe um vetor de bytes que serão gravados em arquivo .jpg, ou seja, grava uma nova imagem;
@Argumentos:
	Um vetor de unsigned char(bytes) e dois inteiros que representam o número de bytes no vetor e de imagens, respectivamente;
@Retorno:
	Sendo um procedimento, não tem retorno;
*/
void salvar_imagem(unsigned char *img, int n_bytes, int n_img){
	char nome[7];
	sprintf(nome, "%03d.jpg", n_img);
	FILE *fp = fopen(nome, "wb+");
	fwrite(img, sizeof(unsigned char), n_bytes * sizeof(unsigned char), fp);
	fclose(fp);
}

/*
Função leitura_de_bloco:
	Faz uma leitura de 512 bytes(1 bloco) e armazena em um vetor;
@Argumentos:
	Um vetor de unsigned char(bytes) e um inteiro que representa o número de bytes no vetor;
@Retorno:
	Sendo um procedimento, não tem retorno;
*/
void leitura_de_bloco(unsigned char *img, int n_bytes){
	for(int i = n_bytes; i < (512 + n_bytes); i++){
		img[i] = getchar();
	}
}	

/*
Função copia_bytes:
	Faz a copia de 512 bytes de um vetor(origem) em outro vetor(destino);
@Argumentos:
	Dois vetores de unsigned char(bytes) e um inteiro que representa o número de bytes no vetor de destino;
@Retorno:
	Sendo um procedimento, não tem retorno;
*/
void copia_bytes(unsigned char *origem, unsigned char *destino, int n_bytes){
	for(int i = n_bytes; i < (512 + n_bytes); i++){
		destino[i] = origem[i - n_bytes];
	}
}

int main(int argc, char *argv[]){
	/*
	Declaração de ponteiros para um buffer que receberá os dados lidos e para a imagem que será gravada;
	*/
	unsigned char *buffer = NULL;
	unsigned char *img = NULL;
	int n_img = 0;
	int n_bytes = 0;
	int bytes_lidos;
	buffer = (unsigned char*) malloc(512 * sizeof(unsigned char));
	/*
	Enquanto não for o fim da entrada de dados, lê um bloco de 512B, verifica se caracteriza uma imagem e, a partir disso,
	decide se vai continuar lendo a imagem atual ou vai salvar a atual e começar a ler outra;
	*/
	while(!feof(stdin)){
		bytes_lidos = fread(buffer, sizeof(unsigned char), 512 * sizeof(unsigned char), stdin);
		/*Divide em dois casos: a imagem foi ou não foi criada?*/ 
		if(img != NULL){
			/*Aqui, o buffer possui uma nova imagem, portanto, a atual deve ser salva e uma nova deve ser criada.
			  Caso contrário, continua gravando o buffer na imagem atual;*/
			if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0){
				salvar_imagem(img, n_bytes, n_img++);
				free(img);
				n_bytes = 0;
				img = (unsigned char*) malloc(512 * sizeof(unsigned char));
				copia_bytes(buffer, img, n_bytes);
				n_bytes += bytes_lidos;	
			}else{
				img = (unsigned char*) realloc(img, (512 + n_bytes) * sizeof(unsigned char));
				copia_bytes(buffer, img, n_bytes);
				n_bytes += bytes_lidos;
			}
		}else{
			/*Neste caso, cria uma imagem;*/	
			if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0){
				img = (unsigned char*) malloc(512 * sizeof(unsigned char));
				copia_bytes(buffer, img, n_bytes);
				n_bytes += bytes_lidos;	
			}
		}	
	}
	/*Salva uma possível última imagem. Se img == NULL, significa que nenhuma imagem foi encontrada;*/
	if(img != NULL){
		salvar_imagem(img, n_bytes, n_img++);
	}else{
		printf("Could not find pictures\n");
	}	
	/*Liberação de memória na heap;*/
	free(img);
	free(buffer);
	return 0;
}