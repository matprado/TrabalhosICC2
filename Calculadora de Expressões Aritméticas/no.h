/*TAD NO:
ATENÇÃO: comentários estão no .c*/
#ifndef NO_H
#define NO_H

typedef struct no NO;

NO *criar_no(void);
void apagar_no(NO *no);
void ler_no(NO *no, char c);
int tipo_no(NO *no);
void imprimir_no(NO *no);
void imprimir_recursivo(NO *no);
char delimitador(NO *no);
int delimitador_oposto(char del1, char del2);
char operador(NO *no);
double operando(NO *no);
void aponta_esquerda(NO *pai, NO *filho);
void aponta_direita(NO *pai, NO *filho);
int no_unario(NO *no);
double resolve_no(NO *no, int *incorreta);
double calcular_no(double A, double B, NO *no, int *incorreta);
void apaga_recursivamente(NO *no);

#endif